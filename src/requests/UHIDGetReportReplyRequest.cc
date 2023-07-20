#include "UHIDGetReportReplyRequest.h"

#include <linux/uhid.h>

Napi::Object UHIDGetReportReplyRequest::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "UHIDGetReportReplyRequest",
          {} );

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent( func );
  env.SetInstanceData( constructor );

  exports.Set( "UHIDGetReportReplyRequest", func );
  return exports;
}

UHIDGetReportReplyRequest::UHIDGetReportReplyRequest( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< UHIDGetReportReplyRequest >( info ) {
  event = Napi::External< uhid_event >::New( info.Env(), new uhid_event );
  ev.type = UHID_GET_REPORT_REPLY;
}