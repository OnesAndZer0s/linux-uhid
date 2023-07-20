#pragma once

#include "src/requests/UHIDRequest.h"

#include <linux/uhid.h>
#include <napi.h>

class UHIDSetReportReplyRequest : public Napi::ObjectWrap< UHIDSetReportReplyRequest >, private uhid_set_report_reply_req, public UHIDRequest {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    UHIDSetReportReplyRequest( const Napi::CallbackInfo& info );
};
