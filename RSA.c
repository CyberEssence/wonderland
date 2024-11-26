#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/aes.h>
#include <stdint.h>

#define KEY_SIZE 16
#define BLOCK_SIZE 16

// Define AES_KEYLEN_128
#define AES_KEYLEN_128 16

// Structure to hold the state of our PRNG
typedef struct {
    unsigned char key[AES_KEYLEN_128];
    unsigned char counter[BLOCK_SIZE];
    AES_KEY aes_key;
} prng_state;

// Function to initialize the PRNG
prng_state* prng_init(const unsigned char* key) {
    prng_state* state = malloc(sizeof(prng_state));
    if (!state) return NULL;

    // Copy the key
    memcpy(state->key, key, KEY_SIZE);

    // Initialize the counter to 0
    memset(state->counter, 0, BLOCK_SIZE);

    // Set up the AES key
    AES_set_encrypt_key(state->key, KEY_SIZE * 8, &state->aes_key);

    return state;
}

// Function to generate a random byte
unsigned char prng_generate_byte(prng_state* state) {
    // Increment the counter
    *(uint32_t*)state->counter = (*(uint32_t*)state->counter + 1);

    // Encrypt the counter block
    AES_encrypt(state->counter, state->counter, &state->aes_key);

    // Return the first byte of the encrypted counter
    return state->counter[0];
}

// Function to generate n random bytes
void prng_generate_bytes(prng_state* state, unsigned char* buffer, size_t n) {
    for (size_t i = 0; i < n; i++) {
        buffer[i] = prng_generate_byte(state);
    }
}

// Function to free PRNG state
void prng_free(prng_state* state) {
    free(state);
}

int main() {
    unsigned char key[] = "0123456789abcdef"; // Replace with your secret key

    prng_state* prng = prng_init(key);

    if (!prng) {
        fprintf(stderr, "Failed to initialize PRNG\n");
        return EXIT_FAILURE;
    }

    const size_t bytes_to_generate = 32;
    unsigned char random_bytes[bytes_to_generate];

    prng_generate_bytes(prng, random_bytes, bytes_to_generate);

    printf("Generated %zu random bytes:\n", bytes_to_generate);
    for (size_t i = 0; i < bytes_to_generate; i++) {
        printf("%02x ", random_bytes[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }
    printf("\n");

    prng_free(prng);

    return EXIT_SUCCESS;
}
