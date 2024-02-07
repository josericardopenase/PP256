#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base64.h"
#include <getopt.h>
#include "encrypt.h"
#include "sha256.h"
#define DEFAULT_ENCRYPTION_METHOD xor
#define DEFAULT_DIGEST_METHOD SHA256
#define BUFFER_SIZE 1024

char* readInputFromStdin() {
    char *input = malloc(BUFFER_SIZE);
    if (!input) {
        fprintf(stderr, "Error al asignar memoria para la entrada.\n");
        return NULL;
    }
    if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error al leer la entrada.\n");
        free(input);
        return NULL;
    }
    input[strcspn(input, "\n")] = 0;
    return input;
}


int main(int argc, char *argv[]) {
    char *password = NULL;
    char *input = NULL;
    char *encryption = DEFAULT_ENCRYPTION_METHOD;
    char *digest = DEFAULT_DIGEST_METHOD;

    int option;
    // Definir las opciones largas
    struct option long_options[] = {
            {"password", required_argument, 0, 'p'},
            {"input", required_argument, 0, 'i'},
            {"encryption", required_argument, 0, 'e'},
            {"digest", required_argument, 0, 'd'},
            {"base64", no_argument, 0, 'b'},
            {0, 0, 0, 0}
    };

    int base64 = 0;
    while ((option = getopt_long(argc, argv, "p:i:e:d:b", long_options, NULL)) != -1) {
        switch (option) {
            case 'p':
                password = optarg;
                break;
            case 'i':
                input = optarg;
                break;
            case 'b':
                base64 = 1;
                break;
            case 'e':
                encryption = optarg;
                break;
            case 'd':
                digest = optarg;
                break;
            default:
                printf("Uso: %s[-b --base64] [-p --password] [-i --input] [-e --encryption] [-d --digest]\n", argv[0]);
                return EXIT_FAILURE;
        }
    }
    if (!input) {
        input = readInputFromStdin();
        if (!input) return EXIT_FAILURE; // Si falla la lectura de stdin, terminar
    } else {
        input = strdup(input);
    }

    if (!password || !input) {
        printf("Error: La contraseña y la entrada son requeridas.\n");
        printf("Uso: %s [-p --password] [-i --input] [-e --encryption] [-d --digest]\n", argv[0]);
        return EXIT_FAILURE;
    }

    EncryptionSettings* settings = create_encryption_settings(digest, encryption, 32);
    if (!settings) {
        printf("Error al crear los ajustes de cifrado.\n");
        return EXIT_FAILURE;
    }

    if (base64){
        size_t size;
        input = base64_decode(input, strlen(input), &size);
    }

    char* encrypted = encrypt(input, password, settings);
    if (!encrypted) {
        printf("Error al cifrar el mensaje.\n");
        return EXIT_FAILURE;
    }

    size_t size;
    char* output = encrypted;
    if(base64 == 0){
        output = base64_encode(encrypted, strlen(encrypted), &size);
    }

    printf("%s", output);

    free(encrypted);
    free(output);

    return EXIT_SUCCESS;
}