// https://nachtimwald.com/2017/11/18/base64-encode-and-decode-in-c/

#include <stdlib.h>
#include "ft_clib.h"

static const char base64_encode_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static size_t b64_encode_size(size_t len) {
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

    char* ret = malloc(b64_encode_size(len) + 1);
    if (ret == NULL) {
        return NULL;
    }

    ret[b64_encode_size(len)] = 0;
    for (size_t i = 0, j = 0; i < len; i += 3, j += 4) {
        size_t chars;
        chars = input[i];
        chars = i + 1 < len ? chars << 8 | input[i + 1] : chars << 8;
        chars = i + 2 < len ? chars << 8 | input[i + 2] : chars << 8;

        // 0x3F is all 6 bits set
        ret[j] = base64_encode_chars[(chars >> 18) & 0x3F];
        ret[j + 1] = base64_encode_chars[(chars >> 12) & 0x3F];

        if (i + 1 < len) {
            ret[j + 2] = base64_encode_chars[(chars >> 6) & 0x3F];
        } else {
            ret[j + 2] = '=';
        }
        if (i + 2 < len) {
            ret[j + 3] = base64_encode_chars[chars & 0x3F];
        } else {
            ret[j + 3] = '=';
        }
    }

    return ret;
}

static const int b64_decode_chars[] = {62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1,
                                       -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                                       21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34,
                                       35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};

// this could involve more checks, like only '=' at the end and max of 2 of them, whitespace checks etc
static bool is_valid_base64(const char* s) {
    size_t len = ft_strlen(s);
    if (len % 4 != 0) {
        return false;
    }
    for (size_t i = 0; i < len; ++i) {
        if (!ft_isalpha(s[i]) && !ft_isnum(s[i]) && s[i] != '+' && s[i] != '/' && s[i] != '=') {
            return false;
        }
    }
    return true;
}

static size_t base64_decode_size(const char* s) {
    if (s == NULL) {
        return 0;
    }

    size_t len = ft_strlen(s);
    size_t ret = len / 4 * 3;
    while (len-- > 0) {
        if (s[len] == '=') {
            --ret;
        } else {
            break;
        }
    }
    return ret;
}

unsigned char* base64_decode_create(const char* input) {
    if (input == NULL || !is_valid_base64(input)) {
        return NULL;
    }

    size_t len = base64_decode_size(input);
    unsigned char* ret = malloc(len + 1);
    if (ret == NULL) {
        return NULL;
    }
    ret[len] = 0;

    for (size_t i = 0, j = 0; i < len; i += 4, j += 3) {
        size_t chars = b64_decode_chars[input[i] - 43];
        chars = (chars << 6) | b64_decode_chars[input[i + 1] - 43];
        chars = input[i + 2] == '=' ? chars << 6 : (chars << 6) | b64_decode_chars[input[i + 2] - 43];
        chars = input[i + 3] == '=' ? chars << 6 : (chars << 6) | b64_decode_chars[input[i + 3] - 43];

        ret[j] = (chars >> 16) & 0xFF;
        if (input[i + 2] != '=') {
            ret[j + 1] = (chars >> 8) & 0xFF;
        }
        if (input[i + 3] != '=') {
            ret[j + 2] = chars & 0xFF;
        }
    }

    return ret;
}
