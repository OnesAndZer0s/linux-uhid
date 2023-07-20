#pragma once

#include "src/requests/UHIDRequest.h"

#include <linux/uhid.h>
#include <napi.h>

class UHIDCreateRequest : public Napi::ObjectWrap< UHIDCreateRequest >, private uhid_create2_req, public UHIDRequest {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    UHIDCreateRequest( const Napi::CallbackInfo& info );

    Napi::Value GetName( const Napi::CallbackInfo& info );
    void SetName( const Napi::CallbackInfo& info, const Napi::Value& value );

    Napi::Value GetPhys( const Napi::CallbackInfo& info );
    void SetPhys( const Napi::CallbackInfo& info, const Napi::Value& value );

    Napi::Value GetUniq( const Napi::CallbackInfo& info );
    void SetUniq( const Napi::CallbackInfo& info, const Napi::Value& value );

    Napi::Value GetBus( const Napi::CallbackInfo& info );
    void SetBus( const Napi::CallbackInfo& info, const Napi::Value& value );

    Napi::Value GetVendor( const Napi::CallbackInfo& info );
    void SetVendor( const Napi::CallbackInfo& info, const Napi::Value& value );

    Napi::Value GetProduct( const Napi::CallbackInfo& info );
    void SetProduct( const Napi::CallbackInfo& info, const Napi::Value& value );

    Napi::Value GetVersion( const Napi::CallbackInfo& info );
    void SetVersion( const Napi::CallbackInfo& info, const Napi::Value& value );

    Napi::Value GetCountry( const Napi::CallbackInfo& info );
    void SetCountry( const Napi::CallbackInfo& info, const Napi::Value& value );

    Napi::Value GetData( const Napi::CallbackInfo& info );
    void SetData( const Napi::CallbackInfo& info, const Napi::Value& value );
};
