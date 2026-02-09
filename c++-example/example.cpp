#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/hmac.h>
#include <openssl/evp.h>

// Function to encode base64
char *base64_encode(
    const unsigned char *data,
    size_t input_length,
    size_t *output_length
) {
    BIO *bio;
    BIO *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    BIO_write(bio, data, input_length);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    *output_length = bufferPtr->length;

    char *b64text = malloc(*output_length + 1);
    memcpy(b64text, bufferPtr->data, *output_length);
    b64text[*output_length] = '\0';

    BUF_MEM_free(bufferPtr);
    return b64text;
}

int main(void)
{
    const char *payload =
        "{\"user\":\"Alice\",\"action\":\"transfer\",\"amount\":100}";

    const char *secret_key =
        "UHaelt3kZcGLsnQRCPwmFUnyRchj9rV9pk1JKhxH";

    unsigned char *result;
    unsigned int result_len;

    // Generate HMAC-SHA256 signature    
    result = HMAC(
        EVP_sha256(),
        secret_key,
        strlen(secret_key),
        (unsigned char *)payload,
        strlen(payload),
        NULL,
        &result_len
    );

    // Encode to Base64
    size_t b64_len;
    char *signature_base64 = base64_encode(
        result,
        result_len,
        &b64_len
    );

    printf("Signature: %s\n", signature_base64);

    free(signature_base64);
    return 0;
}
