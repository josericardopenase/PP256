#include <malloc.h>
#include <string.h>

int hexToInt(char hex[]) {
    int result = 0; // Este es el valor decimal resultante
    for (int i = 0; i < 2; i++) {
        char c = hex[i];
        result *= 16;
        if (c >= '0' && c <= '9') {
            result += c - '0';
        } else if (c >= 'A' && c <= 'F') {
            result += 10 + (c - 'A');
        } else if (c >= 'a' && c <= 'f') {
            result += 10 + (c - 'a');
        } else {
            // Carácter no hexadecimal válido, manejar error
            return -1; // Retorna -1 en caso de error
        }
    }
    return result;
}

char* hexToBin(char* hex){
    char* buffer = calloc(32, sizeof(char));
    int final_length= strlen(hex) / 2;
    for(int i = 0; i < final_length; i++){
        char buff[] = {hex[i], hex[i+1]};
        *(buffer+i) = hexToInt(buff);
    }
    return buffer;
}
