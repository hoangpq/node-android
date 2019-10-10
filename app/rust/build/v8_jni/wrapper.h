#ifndef JNI_WRAPPER_H_
#define JNI_WRAPPER_H_

#include <iostream>
#include <jni.h>

#include "object_wrap.h"
#include "v8.h"

using namespace v8;

typedef struct {
  const uint8_t *ptr;
  uint32_t len;
} string_t;

extern "C" {
jobject new_instance(string_t);
jvalue instance_call(jobject, string_t, uint32_t, const jvalue *);
void adb_debug(const char *);
}

class JavaWrapper : public rust::ObjectWrap {

public:
  static void Init(Isolate *isolate_, Local<ObjectTemplate> exports);

private:
  explicit JavaWrapper(std::string packageName)
      : package_(std::move(packageName)){};
  ~JavaWrapper() override = default;

  static void New(const FunctionCallbackInfo<Value> &args);

  static void Getter(Local<String> property,
                     const PropertyCallbackInfo<Value> &info);

  static void Setter(Local<String> property, Local<Value> value,
                     const PropertyCallbackInfo<Value> &info);

  static void ToStringAccessor(Local<String> property,
                               const PropertyCallbackInfo<Value> &info);

  static void Call(const FunctionCallbackInfo<Value> &args);

  std::string package_;
  std::string method_;
  jvalue value_;

  static Persistent<FunctionTemplate> constructor_;
};

#endif // JNI_WRAPPER_H_