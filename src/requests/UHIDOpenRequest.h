#pragma once

#include "src/requests/UHIDRequest.h"

#include <linux/uhid.h>
#include <napi.h>

class UHIDOpenRequest : public Napi::ObjectWrap< UHIDOpenRequest >, public UHIDRequest {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    UHIDOpenRequest( const Napi::CallbackInfo& info );
};
