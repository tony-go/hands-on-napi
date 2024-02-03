#include <napi.h>
#include <openssl/sha.h>

#include <string>
#include <vector>

#ifdef __clang__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

void hash(const Napi::CallbackInfo &info) {
  assert(info.Length() == 2);

  assert(info[0].IsString());
  std::string data = info[0].As<Napi::String>().Utf8Value();

  assert(info[1].IsBuffer());
  Napi::Buffer<unsigned char> buffer =
      info[1].As<Napi::Buffer<unsigned char>>();

  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, data.c_str(), data.size());
  SHA256_Final(hash, &sha256);

  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    buffer[i] = hash[i];
  }
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("hash", Napi::Function::New(env, hash));
  return exports;
}

NODE_API_MODULE(hashaddon, Init)
