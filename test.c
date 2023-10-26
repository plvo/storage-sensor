#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

typedef struct {
    int tempmin;
    int tempmax;
    int num_frigo;
    int temperature_frigo;
    int nbr_ouverture_porte;
} Info;

int main() {
    FILE *fichier;
    char ligne[MAX_LINE_LENGTH];
    Info info[20]; // il y a 20 frigo

    fichier = fopen("azer.csv", "r");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    // Ignorer la première ligne -> titre 
    fgets(ligne, sizeof(ligne), fichier);

    int i = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int tempmin;
        int tempmax;
        int num_frigo;
        int temperature_frigo;
        int nbr_ouverture_porte;

        if (sscanf(ligne, "%d,%d,%d,%d,%d", &tempmin, &tempmax, &num_frigo, &temperature_frigo, &nbr_ouverture_porte) == 3) {
            info[i].tempmin = tempmin;
            info[i].tempmax = tempmax;
            info[i].num_frigo = num_frigo;
            info[i].temperature_frigo = temperature_frigo;
            info[i].nbr_ouverture_porte = nbr_ouverture_porte;
            i++;
        } else {
            printf("Erreur de lecture de la ligne %d.\n", i + 2); // +2 car la première ligne est l'en-tête
        }
    }

    fclose(fichier);


    for (int j = 0; j < i; j++) {
        printf("Num Frigo: %d, Temperature frigo : %d, Temp min : %d, Temp min : %d, Temp min : %d, Temp min : %d\n\n", info[j].num_frigo, info[j].temperature_frigo, info[j].tempmin, info[j].tempmax, info[j].nbr_ouverture_porte);
    }

    return 0;
}