#include "UHIDCloseRequest.h"

#include "napi.h"

#include <linux/uhid.h>

Napi::Object UHIDCloseRequest::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "UHIDCloseRequest",
          {} );

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent( func );
  env.SetInstanceData( constructor );

  exports.Set( "UHIDCloseRequest", func );

  return exports;
}

UHIDCloseRequest::UHIDCloseRequest( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< UHIDCloseRequest >( info ) {
  event = Napi::External< uhid_event >::New( info.Env(), new uhid_event );
  ev.type = UHID_CLOSE;
}