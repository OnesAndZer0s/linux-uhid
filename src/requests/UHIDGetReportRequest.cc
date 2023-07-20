#include "UHIDGetReportRequest.h"

#include <linux/uhid.h>

Napi::Object UHIDGetReportRequest::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "UHIDGetReportRequest",
          {} );

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent( func );
  env.SetInstanceData( constructor );

  exports.Set( "UHIDGetReportRequest", func );
  return exports;
}

UHIDGetReportRequest::UHIDGetReportRequest( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< UHIDGetReportRequest >( info ) {
  event = Napi::External< uhid_event >::New( info.Env(), new uhid_event );
  ev.type = UHID_GET_REPORT;
}