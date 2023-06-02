//
// Created by Jonas Bennink bolt on 6/2/23.
//

/* https://nachtimwald.com/2017/11/18/base64-encode-and-decode-in-c/ */

#include <stdlib.h>
#include "ft_clib.h"

static const char base64_encode_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

size_t b64_encoded_size(size_t len) {
    size_t ret = len;

    if (len % 3 != 0) {
        ret += 3 - (len % 3);
    }
    ret /= 3;
    ret *= 4;
    return ret;
}

char* base64_encode_create(const unsigned char* input, size_t len) {
    if (input == NULL || len == 0) {
        return NULL;
    }

    char* ret = malloc(b64_encoded_size(len) + 1);
    if (ret == NULL) {
        return NULL;
    }

    ret[b64_encoded_size(len)] = 0;
    size_t i, j;
    for (i = 0, j = 0; i < len; i += 3, j += 4) {
        size_t chr;
        chr = input[i];
        chr = i + 1 < len ? chr << 8 | input[i + 1] : chr << 8;
        chr = i + 2 < len ? chr << 8 | input[i + 2] : chr << 8;

        // 0x3F is all 6 bits set
        ret[j] = base64_encode_chars[(chr >> 18) & 0x3F];
        ret[j + 1] = base64_encode_chars[(chr >> 12) & 0x3F];

        if (i + 1 < len) {
            ret[j + 2] = base64_encode_chars[(chr >> 6) & 0x3F];
        } else {
            ret[j + 2] = '=';
        }
        if (i + 2 < len) {
            ret[j + 3] = base64_encode_chars[chr & 0x3F];
        } else {
            ret[j + 3] = '=';
        }
    }

    return ret;
}
