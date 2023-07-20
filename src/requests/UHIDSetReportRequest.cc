#include "UHIDSetReportRequest.h"

#include <linux/uhid.h>

Napi::Object UHIDSetReportRequest::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "UHIDSetReportRequest",
          {} );

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent( func );
  env.SetInstanceData( constructor );

  exports.Set( "UHIDSetReportRequest", func );
  return exports;
}

UHIDSetReportRequest::UHIDSetReportRequest( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< UHIDSetReportRequest >( info ) {
  event = Napi::External< uhid_event >::New( info.Env(), new uhid_event );
  ev.type = UHID_SET_REPORT;
}