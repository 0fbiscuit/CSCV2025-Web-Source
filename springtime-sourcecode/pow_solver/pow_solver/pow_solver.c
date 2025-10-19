#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void bytes_to_hex(unsigned char *bytes, int len, char *output) {
    for (int i = 0; i < len; i++) {
        sprintf(output + (i * 2), "%02x", bytes[i]);
    }
    output[len * 2] = '\0';
}

int check_leading_zeros(char *hash_hex, int difficulty) {
    for (int i = 0; i < difficulty; i++) {
        if (hash_hex[i] != '0') return 0;
    }
    return 1;
}

char* solve_pow(const char *challenge, int difficulty) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char hash_hex[SHA256_DIGEST_LENGTH * 2 + 1];
    char input[256];
    long long counter = 0;
    
    while (1) {
        // Tạo input = challenge + counter
        sprintf(input, "%s%lld", challenge, counter);
        
        // Tính SHA256
        SHA256((unsigned char*)input, strlen(input), hash);
        
        // Chuyển sang hex
        bytes_to_hex(hash, SHA256_DIGEST_LENGTH, hash_hex);
        
        // Kiểm tra leading zeros
        if (check_leading_zeros(hash_hex, difficulty)) {
            char *result = malloc(32);
            sprintf(result, "%lld", counter);
            return result;
        }
        
        counter++;
        
        // Progress indicator mỗi 1M attempts
        if (counter % 1000000 == 0) {
            fprintf(stderr, "[*] Tried %lld attempts...\n", counter);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <challenge> [difficulty]\n", argv[0]);
        return 1;
    }
    
    const char *challenge = argv[1];
    int difficulty = 6; // Default difficulty
    
    if (argc >= 3) {
        difficulty = atoi(argv[2]);
    }
    
    fprintf(stderr, "[*] Solving PoW for challenge: %s\n", challenge);
    fprintf(stderr, "[*] Difficulty: %d leading zeros\n", difficulty);
    
    char *answer = solve_pow(challenge, difficulty);
    
    fprintf(stderr, "[+] Found answer: %s\n", answer);
    printf("%s\n", answer); // Output only the answer to stdout
    
    free(answer);
    return 0;
}