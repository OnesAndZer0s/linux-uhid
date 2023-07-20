#pragma once

#include "src/requests/UHIDRequest.h"

#include <linux/uhid.h>
#include <napi.h>

class UHIDDestroyRequest : public Napi::ObjectWrap< UHIDDestroyRequest >, public UHIDRequest {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    UHIDDestroyRequest( const Napi::CallbackInfo& info );
};
