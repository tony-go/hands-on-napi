{
  "targets": [
    {
      "target_name": "hashaddon", 
      "sources": ["hashaddon.cc"],
      "cflags_cc": [ "-fno-exceptions", "-std=c++17", "-Wno-deprecated-declarations" ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
      ],
    },
  ]
}
