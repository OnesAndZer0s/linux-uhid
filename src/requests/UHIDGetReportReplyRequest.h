#pragma once

#include "src/requests/UHIDRequest.h"

#include <linux/uhid.h>
#include <napi.h>

class UHIDGetReportReplyRequest : public Napi::ObjectWrap< UHIDGetReportReplyRequest >, private uhid_get_report_reply_req, public UHIDRequest {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    UHIDGetReportReplyRequest( const Napi::CallbackInfo& info );
};
