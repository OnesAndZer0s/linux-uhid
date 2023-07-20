#include "UHIDCreateRequest.h"

#include <iostream>
#include <linux/uhid.h>
#include <string>

Napi::Object UHIDCreateRequest::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "UHIDCreateRequest",
          {
              InstanceAccessor< &UHIDCreateRequest::GetName, &UHIDCreateRequest::SetName >( "name" ),
              InstanceAccessor< &UHIDCreateRequest::GetPhys, &UHIDCreateRequest::SetPhys >( "phys" ),
              InstanceAccessor< &UHIDCreateRequest::GetUniq, &UHIDCreateRequest::SetUniq >( "uniq" ),
              InstanceAccessor< &UHIDCreateRequest::GetBus, &UHIDCreateRequest::SetBus >( "bus" ),
              InstanceAccessor< &UHIDCreateRequest::GetVendor, &UHIDCreateRequest::SetVendor >( "vendor" ),
              InstanceAccessor< &UHIDCreateRequest::GetProduct, &UHIDCreateRequest::SetProduct >( "product" ),
              InstanceAccessor< &UHIDCreateRequest::GetVersion, &UHIDCreateRequest::SetVersion >( "version" ),
              InstanceAccessor< &UHIDCreateRequest::GetCountry, &UHIDCreateRequest::SetCountry >( "country" ),
              InstanceAccessor< &UHIDCreateRequest::GetData, &UHIDCreateRequest::SetData >( "data" ),
          } );

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent( func );
  env.SetInstanceData( constructor );

  exports.Set( "UHIDCreateRequest", func );
  return exports;
}

UHIDCreateRequest::UHIDCreateRequest( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< UHIDCreateRequest >( info ) {
  memset( &ev, 0, sizeof( ev ) );

  event = Napi::External< uhid_event >::New( info.Env(), &ev );
  ev.type = UHID_CREATE2;
  ev.u.create2.bus = 0x03;
}

Napi::Value UHIDCreateRequest::GetName( const Napi::CallbackInfo& info ) {
  int strLen = strlen( (char*) ev.u.create2.name );
  return Napi::String::New( info.Env(), std::string( (char*) ev.u.create2.name, strLen ) );
}

void UHIDCreateRequest::SetName( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  std::string name = value.As< Napi::String >().Utf8Value();
  if( name.size() > 128 )
    Napi::Error::New( info.Env(), std::string( "string length is greater than 128 " ) + "\n" ).ThrowAsJavaScriptException();

  // memset( ev.u.create2.name, 0, name.size() );
  strcpy( (char*) ev.u.create2.name, name.c_str() );
}

Napi::Value UHIDCreateRequest::GetPhys( const Napi::CallbackInfo& info ) {
  int strLen = strlen( (char*) ev.u.create2.phys );
  return Napi::String::New( info.Env(), std::string( (char*) ev.u.create2.phys, strLen ) );
}

void UHIDCreateRequest::SetPhys( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  std::string phys = value.As< Napi::String >().Utf8Value();
  if( phys.length() > 64 )
    Napi::Error::New( info.Env(), std::string( "string length is greater than 64 " ) + "\n" ).ThrowAsJavaScriptException();

  memset( ev.u.create2.phys, 0, phys.length() );
  memcpy( ev.u.create2.phys, phys.c_str(), phys.length() );
}

Napi::Value UHIDCreateRequest::GetUniq( const Napi::CallbackInfo& info ) {
  int strLen = strlen( (char*) ev.u.create2.uniq );
  return Napi::String::New( info.Env(), std::string( (char*) ev.u.create2.uniq, strLen ) );
}

void UHIDCreateRequest::SetUniq( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  std::string uniq = value.As< Napi::String >().Utf8Value();
  if( uniq.length() > 64 )
    Napi::Error::New( info.Env(), std::string( "string length is greater than 64 " ) + "\n" ).ThrowAsJavaScriptException();

  memset( ev.u.create2.uniq, 0, uniq.length() );
  memcpy( ev.u.create2.uniq, uniq.c_str(), uniq.length() );
}

Napi::Value UHIDCreateRequest::GetBus( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ev.u.create2.bus );
}

void UHIDCreateRequest::SetBus( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  ev.u.create2.bus = value.As< Napi::Number >().Uint32Value();
}

Napi::Value UHIDCreateRequest::GetVendor( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ev.u.create2.vendor );
}

void UHIDCreateRequest::SetVendor( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  ev.u.create2.vendor = value.As< Napi::Number >().Uint32Value();
}

Napi::Value UHIDCreateRequest::GetProduct( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ev.u.create2.product );
}

void UHIDCreateRequest::SetProduct( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  ev.u.create2.product = value.As< Napi::Number >().Uint32Value();
}

Napi::Value UHIDCreateRequest::GetVersion( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ev.u.create2.version );
}

void UHIDCreateRequest::SetVersion( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  ev.u.create2.version = value.As< Napi::Number >().Uint32Value();
}

Napi::Value UHIDCreateRequest::GetCountry( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), ev.u.create2.country );
}

void UHIDCreateRequest::SetCountry( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  ev.u.create2.country = value.As< Napi::Number >().Uint32Value();
}

Napi::Value UHIDCreateRequest::GetData( const Napi::CallbackInfo& info ) {
  return Napi::Buffer< unsigned char >::Copy( info.Env(), ev.u.create2.rd_data, ev.u.create2.rd_size );
}

void UHIDCreateRequest::SetData( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  if( !value.IsBuffer() )
    Napi::TypeError::New( info.Env(), "Buffer expected" ).ThrowAsJavaScriptException();
  else if( value.As< Napi::Buffer< unsigned char > >().Length() > 4096 )
    Napi::Error::New( info.Env(), std::string( "Buffer length is greater than 4096 " ) + "\n" ).ThrowAsJavaScriptException();
  else {
    Napi::Buffer< unsigned char > buffer = value.As< Napi::Buffer< unsigned char > >();
    memcpy( ev.u.create2.rd_data, buffer.Data(), buffer.Length() );
    ev.u.create2.rd_size = buffer.Length();
  }
}