#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

int degreentrop;
int degreenmoins;
int ventil;

struct Var {
    int variable;
    int (*fonction)(int); // Pointeur vers une fonction prenant un int en argument et renvoyant un int
};

int main() {
    FILE *fichier;

    fichier = fopen("config.csv", "r");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }



    return 0;
    // Ignorer la première ligne -> titre 
}