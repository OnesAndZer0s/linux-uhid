#pragma once

#include "src/requests/UHIDRequest.h"

#include <linux/uhid.h>
#include <napi.h>

class UHIDOutputRequest : public Napi::ObjectWrap< UHIDOutputRequest >, private uhid_output_req, public UHIDRequest {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    UHIDOutputRequest( const Napi::CallbackInfo& info );
};
