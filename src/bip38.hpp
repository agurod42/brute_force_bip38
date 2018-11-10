#include <string>

#include "../third_party/libwally-core/include/wally_core.h"
#include "../third_party/libwally-core/include/wally_crypto.h"
#include "../third_party/libwally-core/include/wally_bip38.h"

using namespace std;

typedef unsigned char uchar_t;

namespace brute38 {

string bip38_public_key_from_private_key(const string &encripted_private_key, const string &secret) {
    char *output;
    uchar_t *private_key_bytes = new uchar_t[EC_PRIVATE_KEY_LEN];
    uchar_t *public_key_bytes = new uchar_t[EC_PUBLIC_KEY_LEN];
    const char *secret_c_str = secret.c_str();

    int ret = bip38_to_private_key(
        encripted_private_key.c_str(),
        reinterpret_cast<const uchar_t*>(secret_c_str),
        secret.size(),
        0,
        private_key_bytes,
        EC_PRIVATE_KEY_LEN
    );

    if (ret != WALLY_OK) {
        // error
    }

    ret = wally_ec_public_key_from_private_key(
        private_key_bytes,
        EC_PRIVATE_KEY_LEN,
        public_key_bytes,
        EC_PUBLIC_KEY_LEN
    );
    
    if (ret != WALLY_OK) {
        // error
    }

    ret = wally_hex_from_bytes(
        public_key_bytes, 
        EC_PUBLIC_KEY_LEN,
        &output
    );

    if (ret != WALLY_OK) {
        // error
    }

    return string(reinterpret_cast<char*>(output));
}

}