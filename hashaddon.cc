#include <napi.h>
#include <openssl/sha.h>

#include <string>
#include <vector>

#ifdef __clang__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

const char hexLookup[] = "0123456789abcdef";
std::string hashToHex(const unsigned char *hash, size_t length) {
  std::string hexStr;
  hexStr.reserve(length * 2); // Pre-allocate space for the hexadecimal string

  for (size_t i = 0; i < length; ++i) {
    const unsigned char val = hash[i];
    hexStr.push_back(hexLookup[val >> 4]);   // Extract the high nibble (4 bits)
                                             // and find the hex character
    hexStr.push_back(hexLookup[val & 0x0F]); // Extract the low nibble and find
                                             // the hex character
  }

  return hexStr;
}

Napi::String hash(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  assert(info.Length() == 1);
  assert(info[0].IsString());
  std::string data = info[0].As<Napi::String>().Utf8Value();

  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, data.c_str(), data.size());
  SHA256_Final(hash, &sha256);

  return Napi::String::New(env, hashToHex(hash, SHA256_DIGEST_LENGTH));
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("hash", Napi::Function::New(env, hash));
  return exports;
}

NODE_API_MODULE(hashaddon, Init)
