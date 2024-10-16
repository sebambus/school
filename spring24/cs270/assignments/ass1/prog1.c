// prog1.c
// Sebastian Nuxoll
// CS 270
// counts tokens in a string

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// splits s into tokens and stores each of them in *args
// returns the number of tokens
int makearg(char* s, char*** args) {
    // Count the tokens in the string
    int tokencount = 1;
    int slength = 1;
    for (char* c = s; *c != '\0'; c++) {
        if (*c == ' ')
            tokencount++;
        slength++;
    }

    // Set up the array of tokens
    char** tokens = (char**)malloc(tokencount * sizeof(char*));
    if (tokens == NULL) {
        return -1;
    }
    for (int i = 0; i < tokencount; i++)
        tokens[i] = (char*)malloc(slength * sizeof(char));
    if (tokens == NULL) {
        for (int i = 0; i < tokencount; i++)
            free(tokens[i]);
        free(tokens);
        return -1;
    }

    // Copy data over to the token array
    int itoken = 0;
    int ichar = 0;
    for (char* c = s; *c != '\0'; c++) {
        if (*c == ' ') {
            tokens[itoken][ichar] = '\0';
            itoken++;
            ichar = 0;
        } else {
            tokens[itoken][ichar] = *c;
            ichar++;
        }
    }
    tokens[itoken][ichar] = '\0'; 

    *args = tokens;
    return tokencount;
}

// tests out makearg on a console input, then frees memory
int main() {
    size_t n = 0;
    char* s;
    char** args;
    printf("string of args: ");
    getline(&s, &n, stdin);
    int tc = makearg(s, &args);
    if (tc > 0) {
        printf("Token count: %d\n", tc);
        for (int i = 0; i < tc; i++) {
            printf("%s\n", args[i]);
            free(args[i]);
        }
        free(args);
    } else {
        printf("makearg failed\n");
    }
    return 0;
}

