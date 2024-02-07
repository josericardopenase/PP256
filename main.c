#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sha256.h"
#include "hexutils.h"

char* addPadding(char* text, int blockSize){
    char* buffer = calloc(32,sizeof(char));
    for (int i = 0; i < strlen(text); ++i) *(buffer+i) = *(text+i);
    for (int i = strlen(text); i < blockSize ; ++i) *(buffer + i) = 0x20;
    return buffer;
}

char* xor(char* input, char* key){
    char* operation = malloc(strlen(input));
    for (int i = 0; i < strlen(input); ++i) {
        *(operation + i) = *(input + i) ^ *(key + i);
    }
    *(operation + 32) = '\0';
    return operation;
}

struct {
    char* (*digestFunction)(char*);
    char* (*encrypt)(char*, char*);
    int blockSize;
} typedef EncryptionSettings;

double getNumberOfBlocks(const char *input, const char *digest_bin);

char* sliceArray(char* array, int init, int finish) {
    if (init > finish) return NULL;
    int sliceLength = finish - init + 1;
    char* slice = (char*)malloc((sliceLength + 1) * sizeof(char));
    if (slice == NULL) return NULL;
    for (int i = 0; i < sliceLength; i++) slice[i] = array[init + i];
    slice[sliceLength] = '\0';
    return slice;
}

char* encrypt(
        char* input,
        char* password,
        EncryptionSettings* settings
){
    char* digest = settings->digestFunction(password);
    char* digest_bin = hexToBin(digest);

    double numberOfBlocks = getNumberOfBlocks(input, digest_bin);
    if(strlen(input) < strlen(digest_bin)) input = addPadding(input, settings->blockSize);
    int sizeOfFinalBuffer = settings->blockSize * numberOfBlocks;
    char* finalBuffer = malloc(sizeOfFinalBuffer);

    for (int i = 0; i < numberOfBlocks; ++i) {
        int current_offset = (i * (settings->blockSize));
        char *slice = sliceArray(input, current_offset, current_offset + settings->blockSize);
        if(strlen(slice) < strlen(digest_bin)) slice = addPadding(slice, settings->blockSize);
        char* result = settings->encrypt(slice, digest_bin);
        for (int j = 0; j < settings->blockSize; ++j) {
            finalBuffer[(i*(settings->blockSize))+j] = result[j];
        }
    }
    *(finalBuffer+sizeOfFinalBuffer)='\0';
    return finalBuffer;
}

double getNumberOfBlocks(const char *input, const char *digest_bin) { return ceil((float) strlen(input) / (float)strlen(digest_bin)); }

EncryptionSettings* create_encryption_settings(char* (*digestFunction)(char*), char* (*encrypt)(char*, char*), int blockSize){
    EncryptionSettings* settings = malloc(sizeof(settings));
    settings->encrypt = encrypt;
    settings->digestFunction = digestFunction;
    settings->blockSize = blockSize;
    return settings;
}

int main(){
    EncryptionSettings* settings = create_encryption_settings(SHA256, xor, 32);
    char* plaintext="soy el puto amo";
    char* password = "password";
    char* encripted = encrypt(plaintext, password,  settings);
    printf("%s\n", encripted);
    printf("%s\n", encrypt(encripted, password, settings));
    return 0;
}