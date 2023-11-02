#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

int degreentrop;
int degreenmoins;
int ventil;

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

    // Ignorer la première ligne
    fgets(ligne, sizeof(ligne), fichier);

    int i = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int num_frigo;      
        int temperature_frigo;
        int tempmin;      
        int tempmax;
        int nbr_ouverture_porte;

        if (sscanf(ligne, "%d,%d,%d,%d,%d", &num_frigo, &temperature_frigo, &tempmin, &tempmax, &nbr_ouverture_porte) == 5) {
            info[i].num_frigo = num_frigo;
            info[i].temperature_frigo = temperature_frigo;
            info[i].tempmin = tempmin;
            info[i].tempmax = tempmax;
            info[i].nbr_ouverture_porte = nbr_ouverture_porte;
            i++;
        } else {
            printf("Erreur de lecture de la ligne %d.\n", i + 2); // +2 car la première ligne est l'en-tête
        }
    }

    fclose(fichier);


    for (int j = 0; j < i; j++) {
        printf("Num Frigo: %d, Temperature frigo : %d, Temp min : %d, Temp max : %d, nombre de  ouverture de porte : %d\n", info[j].num_frigo, info[j].temperature_frigo, info[j].tempmin, info[j].tempmax, info[j].nbr_ouverture_porte);
    }


    for (int k = 0; k < i; k++) {
        if (info[k].temperature_frigo > info[k].tempmax){
            degreentrop = info[k].temperature_frigo - info[k].tempmax;
            ventil = degreentrop*2;
            printf("frigo numero %d trop froid de %d degre, arret de ventilation pendant %d minutes\n", info[k].num_frigo, degreentrop, ventil);
        }
    }
    
    for (int k = 0; k < i; k++) {
        if (info[k].temperature_frigo < info[k].tempmin){
            degreenmoins = info[k].tempmin - info[k].temperature_frigo;
            ventil = degreenmoins*2;
            printf("frigo numero %d trop chaud de %d degre, ventilation booster pendant %d minutes\n", info[k].num_frigo, degreentrop, ventil);
        }
    }
    return 0;
}