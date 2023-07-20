#pragma once

#include "src/requests/UHIDRequest.h"

#include <linux/uhid.h>
#include <napi.h>

class UHIDStartRequest : public Napi::ObjectWrap< UHIDStartRequest >, private uhid_start_req, public UHIDRequest {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    UHIDStartRequest( const Napi::CallbackInfo& info );

    Napi::Value GetDevFlags( const Napi::CallbackInfo& info );
    void SetDevFlags( const Napi::CallbackInfo& info, const Napi::Value& value );
};
