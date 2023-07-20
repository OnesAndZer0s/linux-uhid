#pragma once

#include "src/requests/UHIDRequest.h"

#include <linux/uhid.h>
#include <napi.h>

class UHIDStopRequest : public Napi::ObjectWrap< UHIDStopRequest >, public UHIDRequest {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    UHIDStopRequest( const Napi::CallbackInfo& info );
};
