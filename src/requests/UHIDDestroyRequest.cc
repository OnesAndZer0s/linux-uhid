#include "UHIDDestroyRequest.h"

#include <linux/uhid.h>

Napi::Object UHIDDestroyRequest::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "UHIDDestroyRequest",
          {} );

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent( func );
  env.SetInstanceData( constructor );

  exports.Set( "UHIDDestroyRequest", func );
  return exports;
}

UHIDDestroyRequest::UHIDDestroyRequest( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< UHIDDestroyRequest >( info ) {
  event = Napi::External< uhid_event >::New( info.Env(), new uhid_event );
  ev.type = UHID_DESTROY;
}