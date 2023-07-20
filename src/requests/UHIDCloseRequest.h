#pragma once

#include "src/requests/UHIDRequest.h"

#include <linux/uhid.h>
#include <napi.h>

class UHIDCloseRequest : public Napi::ObjectWrap< UHIDCloseRequest >, public UHIDRequest {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    UHIDCloseRequest( const Napi::CallbackInfo& info );
};
