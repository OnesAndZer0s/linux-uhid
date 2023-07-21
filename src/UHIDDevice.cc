#include "src/UHIDDevice.h"

#include <algorithm>
#include <fcntl.h>
#include <linux/hid.h>
#include <linux/input.h>
#include <linux/uhid.h>
#include <napi.h>
#include <poll.h>

Napi::Object UHIDDevice::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "UHIDDevice",
          { InstanceMethod( "open", &UHIDDevice::Open ),
              InstanceMethod( "close", &UHIDDevice::Close ),
              InstanceAccessor< &UHIDDevice::IsOpen >( "isOpen" ),
              InstanceMethod( "poll", &UHIDDevice::Poll ),

              InstanceMethod( "create", &UHIDDevice::Create ),
              InstanceMethod( "destroy", &UHIDDevice::Destroy ),
              InstanceMethod( "input", &UHIDDevice::Input ),
              InstanceMethod( "getReportReply", &UHIDDevice::GetReportReply ),
              InstanceMethod( "setReportReply", &UHIDDevice::SetReportReply ),

              InstanceAccessor< &UHIDDevice::GetEventEmitter, &UHIDDevice::SetEventEmitter >( "eventEmitter" )

          } );

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent( func );
  env.SetInstanceData( constructor );

  exports.Set( "UHIDDevice", func );
  return exports;
}

UHIDDevice::UHIDDevice( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< UHIDDevice >( info ) {}

void UHIDDevice::Open( const Napi::CallbackInfo& info ) {
  if( fd > 0 )
    return;

  std::string newPath = ( info.Length() <= 1 && info [ 0 ].IsString() ) ? info [ 0 ].As< Napi::String >().Utf8Value() : "/dev/uhid";
  fd = open( newPath.c_str(), O_RDWR | O_CLOEXEC );

  if( fd < 0 )
    Napi::Error::New( info.Env(), std::string( "Cannot open uhid " ) + newPath + ": " + strerror( errno ) + "\n" ).ThrowAsJavaScriptException();
}

void UHIDDevice::Close( const Napi::CallbackInfo& info ) {
  if( fd < 0 )
    return;
  close( fd );
  fd = -1;
}

Napi::Value UHIDDevice::IsOpen( const Napi::CallbackInfo& info ) {
  return Napi::Boolean::New( info.Env(), fd > 0 );
}

void UHIDDevice::Write( Napi::Env env, const struct uhid_event* ev ) {
  if( fd < 0 )
    return;

  int ret = write( fd, ev, sizeof( *ev ) );
  if( ret < 0 )
    Napi::Error::New( env, "Cannot write uhid: " + std::string( strerror( errno ) ) + "\n" ).ThrowAsJavaScriptException();

  else if( ret != sizeof( *ev ) )
    Napi::Error::New( env, "Wrong size written to uhid: " + std::to_string( ret ) + " != " + std::to_string( sizeof( *ev ) ) + "\n" ).ThrowAsJavaScriptException();
}

void UHIDDevice::Create( const Napi::CallbackInfo& info ) {
  if( fd < 0 )
    return;

  if( info.Length() < 1 || !info [ 0 ].IsObject() )
    return;

  Napi::Object obj = info [ 0 ].As< Napi::Object >();

  struct uhid_event ev;

  ev.type = UHID_CREATE2;

  if( obj.Has( "name" ) && obj.Get( "name" ).IsString() ) {
    std::string name = obj.Get( "name" ).As< Napi::String >().Utf8Value();
    name = name.substr( 0, 128 );
    strncpy( (char*) ev.u.create2.name, name.c_str(), sizeof( ev.u.create2.name ) );
  }

  if( obj.Has( "phys" ) && obj.Get( "phys" ).IsString() ) {
    std::string phys = obj.Get( "phys" ).As< Napi::String >().Utf8Value();
    phys = phys.substr( 0, 64 );
    strncpy( (char*) ev.u.create2.phys, phys.c_str(), sizeof( ev.u.create2.phys ) );
  }

  if( obj.Has( "uniq" ) && obj.Get( "uniq" ).IsString() ) {
    std::string uniq = obj.Get( "uniq" ).As< Napi::String >().Utf8Value();
    uniq = uniq.substr( 0, 64 );
    strncpy( (char*) ev.u.create2.uniq, uniq.c_str(), sizeof( ev.u.create2.uniq ) );
  }

  if( obj.Has( "bus" ) && obj.Get( "bus" ).IsNumber() )
    ev.u.create2.bus = obj.Get( "bus" ).As< Napi::Number >().Uint32Value();

  if( obj.Has( "vendor" ) && obj.Get( "vendor" ).IsNumber() )
    ev.u.create2.vendor = obj.Get( "vendor" ).As< Napi::Number >().Uint32Value();

  if( obj.Has( "product" ) && obj.Get( "product" ).IsNumber() )
    ev.u.create2.product = obj.Get( "product" ).As< Napi::Number >().Uint32Value();

  if( obj.Has( "version" ) && obj.Get( "version" ).IsNumber() )
    ev.u.create2.version = obj.Get( "version" ).As< Napi::Number >().Uint32Value();

  if( obj.Has( "country" ) && obj.Get( "country" ).IsNumber() )
    ev.u.create2.country = obj.Get( "country" ).As< Napi::Number >().Uint32Value();

  if( obj.Has( "data" ) && obj.Get( "data" ).IsBuffer() ) {
    Napi::Buffer< uint8_t > rd_data = obj.Get( "data" ).As< Napi::Buffer< uint8_t > >();
    size_t len = std::min< size_t >( rd_data.Length(), HID_MAX_DESCRIPTOR_SIZE );
    memcpy( ev.u.create2.rd_data, rd_data.Data(), len );
    ev.u.create2.rd_size = len;
  }

  Write( info.Env(), &ev );
}

void UHIDDevice::Destroy( const Napi::CallbackInfo& info ) {
  if( fd < 0 )
    return;

  struct uhid_event ev;

  ev.type = UHID_DESTROY;
  Write( info.Env(), &ev );
  fd = -1;
}

void UHIDDevice::Input( const Napi::CallbackInfo& info ) {
  if( fd < 0 )
    return;

  if( info.Length() < 1 || !info [ 0 ].IsBuffer() )
    return;

  Napi::Buffer< uint8_t > data = info [ 0 ].As< Napi::Buffer< uint8_t > >();
  size_t len = std::min< size_t >( data.Length(), UHID_DATA_MAX );
  struct uhid_event ev;

  ev.type = UHID_INPUT2;
  memcpy( ev.u.input2.data, data.Data(), len );
  ev.u.input2.size = len;

  Write( info.Env(), &ev );
}

void UHIDDevice::GetReportReply( const Napi::CallbackInfo& info ) {
  if( fd < 0 )
    return;

  if( info.Length() < 1 || !info [ 0 ].IsObject() )
    return;

  Napi::Object obj = info [ 0 ].As< Napi::Object >();

  struct uhid_event ev;

  ev.type = UHID_GET_REPORT_REPLY;

  if( obj.Has( "data" ) && obj.Get( "data" ).IsBuffer() ) {
    Napi::Buffer< uint8_t > data = obj.Get( "data" ).As< Napi::Buffer< uint8_t > >();
    size_t len = std::min< size_t >( data.Length(), UHID_DATA_MAX );
    memcpy( ev.u.get_report_reply.data, data.Data(), len );
    ev.u.get_report_reply.size = len;
  }

  if( obj.Has( "err" ) && obj.Get( "err" ).IsNumber() )
    ev.u.get_report_reply.err = obj.Get( "err" ).As< Napi::Number >().Uint32Value();

  if( obj.Has( "id" ) && obj.Get( "id" ).IsNumber() )
    ev.u.get_report_reply.id = obj.Get( "id" ).As< Napi::Number >().Uint32Value();

  Write( info.Env(), &ev );
}

void UHIDDevice::SetReportReply( const Napi::CallbackInfo& info ) {
  if( fd < 0 )
    return;

  if( info.Length() < 1 || !info [ 0 ].IsObject() )
    return;

  Napi::Object obj = info [ 0 ].As< Napi::Object >();

  struct uhid_event ev;

  ev.type = UHID_SET_REPORT_REPLY;

  if( obj.Has( "err" ) && obj.Get( "err" ).IsNumber() )
    ev.u.set_report_reply.err = obj.Get( "err" ).As< Napi::Number >().Uint32Value();

  if( obj.Has( "id" ) && obj.Get( "id" ).IsNumber() )
    ev.u.set_report_reply.id = obj.Get( "id" ).As< Napi::Number >().Uint32Value();

  Write( info.Env(), &ev );
}

void UHIDDevice::SetEventEmitter( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  this->eventEmitter = Napi::Persistent( value.As< Napi::Function >() );
}

Napi::Value UHIDDevice::GetEventEmitter( const Napi::CallbackInfo& info ) {
  return this->eventEmitter.Value();
}

void UHIDDevice::Poll( const Napi::CallbackInfo& info ) {
  if( fd < 0 )
    return;

  struct pollfd* pfds;
  pfds->fd = fd;
  pfds->events = POLLIN;

  int ret = poll( pfds, 2, -1 );
  if( ret < 0 ) {
    Napi::Error::New( info.Env(), "Cannot poll for fds: " + std::string( strerror( errno ) ) + "\n" ).ThrowAsJavaScriptException();
    perror( "poll" );
    return;
  }

  if( pfds->revents & POLLIN ) {
    struct uhid_event ev;
    ssize_t ret;

    memset( &ev, 0, sizeof( ev ) );
    ret = read( fd, &ev, sizeof( ev ) );
    if( ret == 0 )
      fprintf( stderr, "Read HUP on uhid-cdev\n" );
    else if( ret < 0 )
      Napi::Error::New( info.Env(), "Cannot read uhid-cdev: " + std::string( strerror( errno ) ) + "\n" ).ThrowAsJavaScriptException();
    else if( ret != sizeof( ev ) )
      Napi::Error::New( info.Env(), "Invalid size read from uhid-dev: " + std::to_string( ret ) + " != " + std::to_string( sizeof( ev ) ) + "\n" ).ThrowAsJavaScriptException();

    switch( ev.type ) {
      case UHID_START:
        {
          Napi::Object retVal = Napi::Object::New( info.Env() );
          retVal.Set( "devFlags", ev.u.start.dev_flags );
          eventEmitter.Call( { Napi::String::New( info.Env(), "start" ), retVal } );
          break;
        }
      case UHID_STOP:
        eventEmitter.Call( { Napi::String::New( info.Env(), "stop" ) } );
        break;
      case UHID_OPEN:
        eventEmitter.Call( { Napi::String::New( info.Env(), "open" ) } );
        break;
      case UHID_CLOSE:
        eventEmitter.Call( { Napi::String::New( info.Env(), "close" ) } );
        break;
      case UHID_OUTPUT:
        {
          Napi::Object retVal = Napi::Object::New( info.Env() );
          retVal.Set( "data", Napi::Buffer< uint8_t >::Copy( info.Env(), ev.u.output.data, ev.u.output.size ) );
          retVal.Set( "rtype", ev.u.output.rtype );
          eventEmitter.Call( { Napi::String::New( info.Env(), "output" ), retVal } );
          break;
        }
      case UHID_GET_REPORT:
        {
          Napi::Object retVal = Napi::Object::New( info.Env() );
          retVal.Set( "id", ev.u.get_report.id );
          retVal.Set( "rnum", ev.u.get_report.rnum );
          retVal.Set( "rtype", ev.u.get_report.rtype );
          eventEmitter.Call( { Napi::String::New( info.Env(), "getReport" ), retVal } );
          break;
        }

      case UHID_SET_REPORT:
        {
          Napi::Object retVal = Napi::Object::New( info.Env() );
          retVal.Set( "id", ev.u.set_report.id );
          retVal.Set( "rnum", ev.u.set_report.rnum );
          retVal.Set( "rtype", ev.u.set_report.rtype );
          retVal.Set( "data", Napi::Buffer< uint8_t >::Copy( info.Env(), ev.u.set_report.data, ev.u.set_report.size ) );
          eventEmitter.Call( { Napi::String::New( info.Env(), "setReport" ), retVal } );
          break;
        }
      default:
        Napi::Error::New( info.Env(), "Invalid event from uhid-dev: " + std::to_string( ev.type ) + "\n" ).ThrowAsJavaScriptException();
    }
  }
}