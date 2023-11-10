#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 1024
#define MAX_SENSOR_COUNT 13
#define MAX_FRIGO 5

struct Capt {
    char *nomCapt;
    int variable;
    int (*fonction)(int);
};

int main() {
    FILE *fichier;
    fichier = fopen("./config.csv", "r");

    // Vérification de la bonne lecture du fichier config
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    int nombre_lignes = 0;
    int nombre_colonnes = 0;
    char ligne[MAX_LINE_LENGTH];

    // Lire le fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        nombre_lignes++;

        // La première ligne est supposée contenir les en-têtes des colonnes
        if (nombre_lignes == 1) {
            char *token = strtok(ligne, ",");
            while (token != NULL) {
                nombre_colonnes++;
                token = strtok(NULL, ",");
            }
        }
    }

    fclose(fichier);

    if (nombre_lignes > 0 && nombre_colonnes > 0) {
        nombre_lignes = nombre_lignes - 1;
        printf("Nombre de lignes : %d\n", nombre_lignes);
        printf("Nombre de colonnes : %d\n", nombre_colonnes);
    } else {
        printf("Le fichier est vide ou ne contient pas de données CSV valides.\n");
    }

    int *tab_total = (int *)malloc(nombre_lignes * sizeof(int));
    if (tab_total == NULL) {
        printf("Échec de l'allocation de mémoire.\n");
        return 1;
    }

    for (int y = 0; y < nombre_lignes; y++) {
        tab_total[y] = 1;
        printf("%d ", tab_total[y]);
    }

    free(tab_total);

    return 0;
}
