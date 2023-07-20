#include "UHIDOutputRequest.h"

#include <linux/uhid.h>

Napi::Object UHIDOutputRequest::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "UHIDOutputRequest",
          {} );

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent( func );
  env.SetInstanceData( constructor );

  exports.Set( "UHIDOutputRequest", func );
  return exports;
}

UHIDOutputRequest::UHIDOutputRequest( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< UHIDOutputRequest >( info ) {
  event = Napi::External< uhid_event >::New( info.Env(), new uhid_event );
  ev.type = UHID_OUTPUT;
}