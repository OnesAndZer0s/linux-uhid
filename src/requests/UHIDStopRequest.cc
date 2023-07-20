#include "UHIDStopRequest.h"

#include <linux/uhid.h>

Napi::Object UHIDStopRequest::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "UHIDStopRequest",
          {} );

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent( func );
  env.SetInstanceData( constructor );

  exports.Set( "UHIDStopRequest", func );
  return exports;
}

UHIDStopRequest::UHIDStopRequest( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< UHIDStopRequest >( info ) {
  event = Napi::External< uhid_event >::New( info.Env(), new uhid_event );
  ev.type = UHID_STOP;
}