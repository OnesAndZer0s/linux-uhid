#include "UHIDOpenRequest.h"

#include <linux/uhid.h>

Napi::Object UHIDOpenRequest::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "UHIDOpenRequest",
          {} );

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent( func );
  env.SetInstanceData( constructor );

  exports.Set( "UHIDOpenRequest", func );
  return exports;
}

UHIDOpenRequest::UHIDOpenRequest( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< UHIDOpenRequest >( info ) {
  event = Napi::External< uhid_event >::New( info.Env(), new uhid_event );
  ev.type = UHID_OPEN;
}