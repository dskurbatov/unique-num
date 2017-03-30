#include <node.h>
#include <string>

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Array;
using v8::Number;

void Unique(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  Local<Array> array = Local<Array>::Cast(args[0]);
  Local<Object> unique = Object::New(isolate);
  Local<Object> nonUnique = Object::New(isolate);
  Local<Number> one = Number::New(isolate, 1);
  
  for(unsigned int i = 0, len = array->Length(); i < len; i++)
  {
  	Local<Value> prop = array->Get(i);
   
    if(!unique->Has(prop) && !nonUnique->Has(prop))
    {
      
      unique->Set(prop, one);
    
    } else if(!nonUnique->Has(prop)){
      nonUnique->Set(prop, one);
      unique->Delete(prop);
    } 
  }

  Local<Array> props = unique->GetOwnPropertyNames();
  unsigned int size = props->Length();
  if(size == 0)
  {
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "No unique values"));
  
  } else if(size == 1)
  {
    args.GetReturnValue().Set(props->Get(0));
  
  } else {
  
    args.GetReturnValue().Set(props);
  }  
}

void Init(Local<Object> exports, Local<Object> module) {
  NODE_SET_METHOD(module, "exports", Unique);
}

NODE_MODULE(unique, Init)

} 