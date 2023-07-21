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
                                InstanceAccessor< &UHIDAddon::UHID_Bus_Type >( "UHIDBusType" ),
                                InstanceAccessor< &UHIDAddon::UHID_Dev_Flags >( "UHIDDevFlags" ),
                                InstanceAccessor< &UHIDAddon::UHID_Report_Type >( "UHIDReportType" ),
                            } );

      UHIDDevice::Init( env, exports );
    }

  private:

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
