#include "UHIDInputRequest.h"

#include <linux/uhid.h>

Napi::Object UHIDInputRequest::Init( Napi::Env env, Napi::Object exports ) {
  Napi::Function func =
      DefineClass( env,
          "UHIDInputRequest",
          {
              InstanceAccessor< &UHIDInputRequest::GetData, &UHIDInputRequest::SetData >( "data" ),
          } );

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent( func );
  env.SetInstanceData( constructor );

  exports.Set( "UHIDInputRequest", func );
  return exports;
}

UHIDInputRequest::UHIDInputRequest( const Napi::CallbackInfo& info ):
    Napi::ObjectWrap< UHIDInputRequest >( info ) {
  event = Napi::External< uhid_event >::New( info.Env(), new uhid_event );
  ev.type = UHID_INPUT2;
}

Napi::Value UHIDInputRequest::GetData( const Napi::CallbackInfo& info ) {
  return Napi::Buffer< unsigned char >::Copy( info.Env(), data, size );
}

void UHIDInputRequest::SetData( const Napi::CallbackInfo& info, const Napi::Value& value ) {
  if( !value.IsBuffer() )
    Napi::TypeError::New( info.Env(), "Buffer expected" ).ThrowAsJavaScriptException();
  else {
    Napi::Buffer< unsigned char > buffer = value.As< Napi::Buffer< unsigned char > >();
    memcpy( data, buffer.Data(), buffer.Length() );
    size = buffer.Length();
  }
}

// Napi::Value UHIDRequest::GetValue(const Napi::CallbackInfo& info) {
//   double num = this->value_;

//   return Napi::Number::New(info.Env(), num);
// }

// Napi::Value UHIDRequest::PlusOne(const Napi::CallbackInfo& info) {
//   this->value_ = this->value_ + 1;

//   return UHIDRequest::GetValue(info);
// }

// Napi::Value UHIDRequest::Multiply(const Napi::CallbackInfo& info) {
//   Napi::Number multiple;
//   if (info.Length() <= 0 || !info[0].IsNumber()) {
//     multiple = Napi::Number::New(info.Env(), 1);
//   } else {
//     multiple = info[0].As<Napi::Number>();
//   }

//   Napi::Object obj = info.Env().GetInstanceData<Napi::FunctionReference>()->New(
//       {Napi::Number::New(info.Env(), this->value_ * multiple.DoubleValue())});

//   return obj;
// }