#include <napi.h>
#include <openssl/sha.h>

#include <string>

#ifdef __clang__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

Napi::Array hash(const Napi::CallbackInfo &info) {}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("hash", Napi::Function::New(env, hash));
  return exports;
}

NODE_API_MODULE(hashaddon, Init)

// unsigned char hash[SHA256_DIGEST_LENGTH];
// SHA256_CTX sha256;
// SHA256_Init(&sha256);
// SHA256_Update(&sha256, data.c_str(), data.size());
// SHA256_Final(hash, &sha256);
