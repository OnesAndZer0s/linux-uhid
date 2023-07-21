#include "src/UHIDDevice.h"

#include <charconv>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <linux/input.h>
#include <linux/uhid.h>
#include <napi.h>
#include <poll.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

using namespace Napi;

class UHIDAddon : public Napi::Addon< UHIDAddon > {
  public:
    UHIDAddon( Napi::Env env, Napi::Object exports ) {
      DefineAddon( exports, {
                                // InstanceMethod( "open", &UHIDAddon::Open, napi_enumerable ),
                                // InstanceMethod( "close", &UHIDAddon::Close, napi_enumerable ),
                                // InstanceMethod( "write", &UHIDAddon::Write, napi_enumerable ),

                                // InstanceAccessor< &UHIDAddon::IsOpen >( "isOpen" ),

                                InstanceAccessor< &UHIDAddon::UHID_Event_Type >( "UHIDRequestType" ),
                                InstanceAccessor< &UHIDAddon::UHID_Bus_Type >( "UHIDBusType" ),
                                InstanceAccessor< &UHIDAddon::UHID_Dev_Flags >( "UHIDDevFlags" ),
                                InstanceAccessor< &UHIDAddon::UHID_Report_Type >( "UHIDReportType" ),

                            } );

      UHIDDevice::Init( env, exports );
    }

  private:
    const char* path = "/dev/uhid";
    int fd = -1;

    // void Open( const Napi::CallbackInfo& info ) {
    //   if( fd > 0 )
    //     return;

    //   std::string newPath = ( info.Length() <= 1 && info [ 0 ].IsString() ) ? info [ 0 ].As< Napi::String >().Utf8Value() : path;
    //   fd = open( newPath.c_str(), O_RDWR | O_CLOEXEC );

    //   if( fd < 0 )
    //     Napi::Error::New( info.Env(), std::string( "Cannot open uhid " ) + newPath + ": " + strerror( errno ) + "\n" ).ThrowAsJavaScriptException();
    // }

    // void Close( const Napi::CallbackInfo& info ) {
    //   if( fd < 0 )
    //     return;
    //   close( fd );
    //   fd = -1;
    // }

    // void Write( const Napi::CallbackInfo& info ) {
    //   if( fd < 0 )
    //     return;

    //   // get object
    //   Object obj = info [ 0 ].As< Object >();
    //   UHIDDevice* create = Napi::ObjectWrap< UHIDDevice >::Unwrap( obj );
    //   // UHIDRequest* what = Napi::ObjectWrap< UHIDRequest >::Unwrap( obj );
    //   struct uhid_event ev;
    //   memset( &ev, 0, sizeof( ev ) );
    //   ev = create->GetEvent();

    //   fprintf( stdout, "it work\n" );

    //   // has event
    //   // if( !obj.Has( "event" ) )
    //   // Napi::Error::New( info.Env(), std::string( "event is required" ) + "\n" ).ThrowAsJavaScriptException();
    //   // fprintf( stdout, "event: %d\n", event.Data() );

    //   // get event
    //   // UHIDRequest event = obj.Get( "event" ).As< UHIDRequest >();
    //   // fprintf( stdout, "event: %d\n", event->Data() );
    //   ssize_t ret = write( fd, &ev, sizeof( ev ) );
    //   if( ret < 0 ) {
    //     Napi::Error::New( info.Env(), std::string( "Cannot write to uhid: " ) + strerror( errno ) + "\n" ).ThrowAsJavaScriptException();
    //   } else if( ret != sizeof( ev ) ) {
    //     Napi::Error::New( info.Env(), std::string( "Wrong size written to uhid: " ) + "\n" ).ThrowAsJavaScriptException();

    //     // fprintf( stderr, "Wrong size written to uhid: %zd != %zu\n",
    //     //     ret, sizeof( ev ) );
    //     // return -EFAULT;
    //   }
    // }

    // Napi::Value IsOpen( const Napi::CallbackInfo& info ) {
    //   return Napi::Boolean::New( info.Env(), fd > 0 );
    // }

    Napi::Value UHID_Bus_Type( const Napi::CallbackInfo& info ) {
      Object obj = Object::New( info.Env() );

      obj.Set( "PCI", Number::New( info.Env(), BUS_PCI ) );
      obj.Set( "ISAPNP", Number::New( info.Env(), BUS_ISAPNP ) );
      obj.Set( "USB", Number::New( info.Env(), BUS_USB ) );
      obj.Set( "HIL", Number::New( info.Env(), BUS_HIL ) );
      obj.Set( "BLUETOOTH", Number::New( info.Env(), BUS_BLUETOOTH ) );
      obj.Set( "VIRTUAL", Number::New( info.Env(), BUS_VIRTUAL ) );

      obj.Set( "ISA", Number::New( info.Env(), BUS_ISA ) );
      obj.Set( "I8042", Number::New( info.Env(), BUS_I8042 ) );
      obj.Set( "XTKBD", Number::New( info.Env(), BUS_XTKBD ) );
      obj.Set( "RS232", Number::New( info.Env(), BUS_RS232 ) );
      obj.Set( "GAMEPORT", Number::New( info.Env(), BUS_GAMEPORT ) );
      obj.Set( "PARPORT", Number::New( info.Env(), BUS_PARPORT ) );
      obj.Set( "AMIGA", Number::New( info.Env(), BUS_AMIGA ) );
      obj.Set( "ADB", Number::New( info.Env(), BUS_ADB ) );
      obj.Set( "I2C", Number::New( info.Env(), BUS_I2C ) );
      obj.Set( "HOST", Number::New( info.Env(), BUS_HOST ) );
      obj.Set( "GSC", Number::New( info.Env(), BUS_GSC ) );
      obj.Set( "ATARI", Number::New( info.Env(), BUS_ATARI ) );
      obj.Set( "SPI", Number::New( info.Env(), BUS_SPI ) );
      obj.Set( "RMI", Number::New( info.Env(), BUS_RMI ) );
      obj.Set( "CEC", Number::New( info.Env(), BUS_CEC ) );
      obj.Set( "INTEL_ISHTP", Number::New( info.Env(), BUS_INTEL_ISHTP ) );
      return obj;
    }

    Napi::Value UHID_Event_Type( const Napi::CallbackInfo& info ) {
      Object obj = Object::New( info.Env() );

      obj.Set( "DESTROY", Number::New( info.Env(), UHID_DESTROY ) );
      obj.Set( "START", Number::New( info.Env(), UHID_START ) );
      obj.Set( "STOP", Number::New( info.Env(), UHID_STOP ) );
      obj.Set( "OPEN", Number::New( info.Env(), UHID_OPEN ) );
      obj.Set( "CLOSE", Number::New( info.Env(), UHID_CLOSE ) );
      obj.Set( "OUTPUT", Number::New( info.Env(), UHID_OUTPUT ) );
      obj.Set( "GET_REPORT", Number::New( info.Env(), UHID_GET_REPORT ) );
      obj.Set( "GET_REPORT_REPLY", Number::New( info.Env(), UHID_GET_REPORT_REPLY ) );
      obj.Set( "CREATE", Number::New( info.Env(), UHID_CREATE2 ) );
      obj.Set( "INPUT", Number::New( info.Env(), UHID_INPUT2 ) );
      obj.Set( "SET_REPORT", Number::New( info.Env(), UHID_SET_REPORT ) );
      obj.Set( "SET_REPORT_REPLY", Number::New( info.Env(), UHID_SET_REPORT_REPLY ) );
      return obj;
    }

    Napi::Value UHID_Dev_Flags( const Napi::CallbackInfo& info ) {
      Object obj = Object::New( info.Env() );

      obj.Set( "NUMBERED_FEATURE_REPORTS", Number::New( info.Env(), UHID_DEV_NUMBERED_FEATURE_REPORTS ) );
      obj.Set( "NUMBERED_OUTPUT_REPORTS", Number::New( info.Env(), UHID_DEV_NUMBERED_OUTPUT_REPORTS ) );
      obj.Set( "NUMBERED_INPUT_REPORTS", Number::New( info.Env(), UHID_DEV_NUMBERED_INPUT_REPORTS ) );
      return obj;
    }

    Napi::Value UHID_Report_Type( const Napi::CallbackInfo& info ) {
      Object obj = Object::New( info.Env() );

      obj.Set( "FEATURE_REPORT", Number::New( info.Env(), UHID_FEATURE_REPORT ) );
      obj.Set( "OUTPUT_REPORT", Number::New( info.Env(), UHID_OUTPUT_REPORT ) );
      obj.Set( "INPUT_REPORT", Number::New( info.Env(), UHID_INPUT_REPORT ) );
      return obj;
    }
};

NODE_API_ADDON( UHIDAddon )
