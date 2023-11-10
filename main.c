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
    fichier = fopen("./output/config.csv", "r");

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
        nombre_lignes -= 1;
        printf("Nombre de lignes : %d\n", nombre_lignes);
        printf("Nombre de colonnes : %d\n", nombre_colonnes);

        // Initialisation du tableau global avec sa memoire 
        int **allFrigo = (int **)malloc(nombre_lignes * sizeof(int *));
        if (allFrigo == NULL) {
            printf("Échec de l'allocation de mémoire.\n");
            return 1;
        }

        for (int y = 0; y < nombre_lignes; y++) {
            int *frigo = (int *)malloc(nombre_colonnes * sizeof(int));

            // Lire le fichier ligne par ligne pour obtenir les valeurs de chaque colonne
            fichier = fopen("./config.csv", "r"); // Ré-ouvrir le fichier pour le lire à nouveau
            for (int x = 0; x <= y; x++) {
                fgets(ligne, sizeof(ligne), fichier); // Lire les lignes jusqu'à atteindre la ligne y
                printf("%d - ligne : %d\n",x, ligne);
            }
            fclose(fichier);

            // // Utiliser strtok pour séparer les valeurs de chaque colonne
            // char *token = strtok(ligne, ",");
            // int i = 0;
            // // for(int z=0; z<nombre_colonnes; z++){
            // //     struct Capt scoubidou;
            // //     frigo[z] = scoubidou;
            // //     frigo[z]
            // // }

            // while (token != NULL) {
            //     frigo[i++] = atoi(token); // Convertir la chaîne en entier et stocker dans le tableau
            //     printf("%d,", atoi(token));
            //     token = strtok(NULL, ",");
            // }

            // for(int z=0; z>nombre_colonnes;z++){
            //     printf('%d', frigo[z]);
            // }
            

            free(frigo);
            allFrigo[y] = frigo;
        }
        free(allFrigo);
    } else {
        printf("Le fichier est vide ou ne contient pas de données CSV valides.\n");
    }

    // if (nombre_lignes > 0 && nombre_colonnes > 0) {
    //     nombre_lignes = nombre_lignes - 1;
    //     printf("Nombre de lignes : %d\n", nombre_lignes);
    //     printf("Nombre de colonnes : %d\n", nombre_colonnes);
    // } else {
    //     printf("Le fichier est vide ou ne contient pas de données CSV valides.\n");
    // }

    // int *allFrigo = (int *)malloc(nombre_lignes * sizeof(int));
    // if (allFrigo == NULL) {
    //     printf("Échec de l'allocation de mémoire.\n");
    //     return 1;
    // }

    // for (int y = 0; y < nombre_lignes; y++) {
    //     //création d'un sous tableau
    //     int *frigo = (int *)malloc(nombre_colonnes * sizeof(int));

    //     fichier = fopen("./output/config.csv", "r");
    //     for (int x = 0; x <= y; x++) {
    //         fgets(ligne, sizeof(ligne), fichier);
    //     }
    //     fclose(fichier);

    //     // Utiliser strtok pour séparer les valeurs de chaque colonne
    //     char *token = strtok(ligne, ",");
    //     int i = 0;
    //     while (token != NULL) {
    //         allFrigo[y][i++] = atoi(token); // Convertir la chaîne en entier et stocker dans le tableau
    //         token = strtok(NULL, ",");
    //     }
    //     //ajout du sous tableau dans allFrigo
    //     // allFrigo[y] = frigo;
    // }

    // free(allFrigo);

    return 0;
}
