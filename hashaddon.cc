#include <napi.h>
#include <openssl/sha.h>

#include <string>
#include <vector>

#ifdef __clang__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

Napi::Number do_crypto_work(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  assert(info.Length() == 2);

  assert(info[0].IsString());
  std::string data = info[0].As<Napi::String>().Utf8Value();

  assert(info[1].IsNumber());
  int32_t rounds = info[1].As<Napi::Number>().Int32Value();

  auto hashes = std::vector<unsigned char *>();
  for (int i = 0; i < rounds; i++) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.c_str(), data.size());
    SHA256_Final(hash, &sha256);

    hashes.push_back(hash);
  }

  return Napi::Number::New(env, hashes.size());
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("doNativeCryptoWork", Napi::Function::New(env, do_crypto_work));
  return exports;
}

NODE_API_MODULE(hashaddon, Init)
