#pragma once

#include "napi.h"

class UHIDDevice : public Napi::ObjectWrap< UHIDDevice > {
  public:
    static Napi::Object Init( Napi::Env env, Napi::Object exports );
    UHIDDevice( const Napi::CallbackInfo& info );

  private:

    int fd = -1;

    void Open( const Napi::CallbackInfo& info );
    void Close( const Napi::CallbackInfo& info );
    Napi::Value IsOpen( const Napi::CallbackInfo& info );
    void Write( Napi::Env env, const struct uhid_event* ev );

    void Create( const Napi::CallbackInfo& info );
    void Destroy( const Napi::CallbackInfo& info );
    void Input( const Napi::CallbackInfo& info );
    void GetReportReply( const Napi::CallbackInfo& info );
    void SetReportReply( const Napi::CallbackInfo& info );

    void On( const Napi::CallbackInfo& info );

    Napi::Value GetEventEmitter( const Napi::CallbackInfo& info );
    void SetEventEmitter( const Napi::CallbackInfo& info, const Napi::Value& value );

    void Poll( const Napi::CallbackInfo& info );

    Napi::FunctionReference eventEmitter;
};