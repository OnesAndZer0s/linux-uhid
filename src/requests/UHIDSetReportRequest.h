#pragma once

#include "src/requests/UHIDRequest.h"

#include <linux/uhid.h>
#include <napi.h>

class UHIDSetReportRequest : public Napi::ObjectWrap< UHIDSetReportRequest >, private uhid_set_report_req, public UHIDRequest {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    UHIDSetReportRequest( const Napi::CallbackInfo& info );
};
