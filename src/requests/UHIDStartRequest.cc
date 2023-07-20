#include "UHIDStartRequest.h"

#include <linux/uhid.h>

Napi::Object UHIDStartRequest::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "UHIDStartRequest",
          {
              InstanceAccessor< &UHIDStartRequest::GetDevFlags, &UHIDStartRequest::SetDevFlags >( "devFlags" ),
          } );

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent( func );
  env.SetInstanceData( constructor );

  exports.Set( "UHIDStartRequest", func );
  return exports;
}

Napi::Value UHIDStartRequest::GetDevFlags( const Napi::CallbackInfo& info ) {
  return Napi::Number::New( info.Env(), dev_flags );
}

void UHIDStartRequest::SetDevFlags( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  if( !value.IsNumber() )
    Napi::TypeError::New( info.Env(), "Number expected" ).ThrowAsJavaScriptException();
  else
    dev_flags = value.As< Napi::Number >().Uint32Value();
}

UHIDStartRequest::UHIDStartRequest( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< UHIDStartRequest >( info ) {
  event = Napi::External< uhid_event >::New( info.Env(), new uhid_event );
  ev.type = UHID_START;
}