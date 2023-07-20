#pragma once

#include "src/requests/UHIDRequest.h"

#include <linux/uhid.h>
#include <napi.h>

class UHIDInputRequest : public Napi::ObjectWrap< UHIDInputRequest >, private uhid_input2_req, public UHIDRequest {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    UHIDInputRequest( const Napi::CallbackInfo& info );

  private:

    Napi::Value GetData( const Napi::CallbackInfo& info );
    void SetData( const Napi::CallbackInfo& info, const Napi::Value& value );
};
