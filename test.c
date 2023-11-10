#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

// int degreentrop;
// int degreenmoins;
// int ventil;

typedef struct {
    int NUM_FRIGO;
    int VENTILATION_START;
    int BADGE_ON;
    int ENTER_DOOR_OPEN;
    int ENTER_DOOR_CLOSE;
    int TIMER_ON;
    int TEMP_START;
    int TIMER_CHECK;
    int EXIT_DOOR_OPEN;
    int EXIT_DOOR_CLOSE;
    int BADGE_OFF;
    int TEMP_END;
    int VENTILATION_EXIT;
    } Info;

int main() {
    FILE *fichier;
    char ligne[MAX_LINE_LENGTH];
    Info info[20]; // il y a 20 frigo

    fichier = fopen("config.csv", "r");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    // Ignorer la première ligne
    fgets(ligne, sizeof(ligne), fichier);

    int i = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int NUM_FRIGO_v;
        int VENTILATION_START_v;
        int BADGE_ON_v;
        int ENTER_DOOR_OPEN_v;
        int ENTER_DOOR_CLOSE_v;
        int TIMER_ON_v;
        int TEMP_START_v;
        int TIMER_CHECK_v;
        int EXIT_DOOR_OPEN_v;
        int EXIT_DOOR_CLOSE_v;
        int BADGE_OFF_v;
        int TEMP_END_v;
        int VENTILATION_EXIT_v;

        if (sscanf(ligne, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &NUM_FRIGO_v, &VENTILATION_START_v, &BADGE_ON_v, &ENTER_DOOR_OPEN_v, &ENTER_DOOR_CLOSE_v, &TIMER_ON_v, &TEMP_START_v, &TIMER_CHECK_v, &EXIT_DOOR_OPEN_v, &EXIT_DOOR_CLOSE_v, &BADGE_OFF_v, &TEMP_END_v, &VENTILATION_EXIT_v ) == 13) {
            info[i].NUM_FRIGO = NUM_FRIGO_v;
            info[i].VENTILATION_START = VENTILATION_START_v;
            info[i].BADGE_ON = BADGE_ON_v;
            info[i].ENTER_DOOR_OPEN = ENTER_DOOR_OPEN_v;
            info[i].ENTER_DOOR_CLOSE = ENTER_DOOR_CLOSE_v;
            info[i].TIMER_ON = TEMP_START_v;
            info[i].TEMP_START = TIMER_CHECK_v;
            info[i].TIMER_CHECK = TIMER_CHECK_v;
            info[i].EXIT_DOOR_OPEN = EXIT_DOOR_OPEN_v;
            info[i].EXIT_DOOR_CLOSE = EXIT_DOOR_CLOSE_v;
            info[i].BADGE_OFF = BADGE_OFF_v;
            info[i].TEMP_END = TEMP_END_v;
            info[i].VENTILATION_EXIT = VENTILATION_EXIT_v;
            i++;
        } else {
            printf("Erreur de lecture de la ligne %d.\n", i + 2); // +2 car la première ligne est l'en-tête
        }
    }
    fclose(fichier);


    for (int j = 0; j < i; j++) {
        // printf("Num Frigo: %d, Temperature frigo : %d, Temp min : %d, Temp max : %d, nombre de  ouverture de porte : %d\n",
        //  info[j].num_frigo, info[j].temperature_frigo, info[j].tempmin, info[j].tempmax, info[j].nbr_ouverture_porte);
        int test = info[j].TEMP_END;
        printf(test);
    }


    // for (int k = 0; k < i; k++) {
    //     if (info[k].temperature_frigo > info[k].tempmax){
    //         degreentrop = info[k].temperature_frigo - info[k].tempmax;
    //         ventil = degreentrop*2;
    //         printf("frigo numero %d trop froid de %d degre, arret de ventilation pendant %d minutes\n", info[k].num_frigo, degreentrop, ventil);
    //     }
    // }
    
    // for (int k = 0; k < i; k++) {
    //     if (info[k].temperature_frigo < info[k].tempmin){
    //         degreenmoins = info[k].tempmin - info[k].temperature_frigo;
    //         ventil = degreenmoins*2;
    //         printf("frigo numero %d trop chaud de %d degre, ventilation booster pendant %d minutes\n", info[k].num_frigo, degreentrop, ventil);
    //     }
    // }
    return 0;
}