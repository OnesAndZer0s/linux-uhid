#pragma once

#include "src/requests/UHIDRequest.h"

#include <linux/uhid.h>
#include <napi.h>

class UHIDGetReportRequest : public Napi::ObjectWrap< UHIDGetReportRequest >, private uhid_get_report_req, public UHIDRequest {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    UHIDGetReportRequest( const Napi::CallbackInfo& info );
};
