#include "UHIDSetReportReplyRequest.h"

#include <linux/uhid.h>

Napi::Object UHIDSetReportReplyRequest::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "UHIDSetReportReplyRequest",
          {} );

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent( func );
  env.SetInstanceData( constructor );

  exports.Set( "UHIDSetReportReplyRequest", func );
  return exports;
}

UHIDSetReportReplyRequest::UHIDSetReportReplyRequest( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< UHIDSetReportReplyRequest >( info ) {
  event = Napi::External< uhid_event >::New( info.Env(), new uhid_event );
  ev.type = UHID_SET_REPORT_REPLY;
}