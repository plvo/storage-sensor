#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_SENSOR_COUNT 13
#define MAX_FRIGO 4

int VENTILATION_START(int variable) {
    return variable;
}

int BADGE_ON(int variable) {
    return variable;
}

int ENTER_DOOR_OPEN(int variable) {
    return variable;
}

int ENTER_DOOR_CLOSE(int variable) {
    return variable;
}

int TIMER_ON(int variable) {
    return variable;
}

int TEMP_START(int variable) {
    return variable;
}

int TIMER_CHECK(int variable) {
    return variable;
}

int EXIT_DOOR_OPEN(int variable) {
    return variable;
}

int EXIT_DOOR_CLOSE(int variable) {
    return variable;
}

int BADGE_OFF(int variable) {
    return variable;
}

int TEMP_END(int variable) {
    return variable;
}

int VENTILATION_EXIT(int variable) {
    return variable;
}

struct Capt {
    char *nomCapt;
    int variable;
    int (*fonction)(int);
};

int main() {
    FILE *fichier;
    fichier = fopen("./output/config.csv", "r");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    char ligne[MAX_LINE_LENGTH];
    struct Capt capteurs[MAX_SENSOR_COUNT];

    if (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char *token = strtok(ligne, ",");
        int i = 0;

        while (token != NULL && i < MAX_SENSOR_COUNT) {
            capteurs[i].variable = 0;
            capteurs[i].nomCapt = strdup(token);
            // capteurs[i].fonction = capteurs[i].nomCapt;
            printf("Capteur ajoute : %s\n", capteurs[i].nomCapt);
            token = strtok(NULL, ",");
            i++;
        }

        int k=0;
        while (fgets(ligne, sizeof(ligne), fichier) != NULL && k < MAX_FRIGO) {
            token = strtok(ligne, ",");
            for (int j = 0; j < i; j++) {
                if (token != NULL) {
                    int valeur = atoi(token);
                    capteurs[j].variable = valeur;
                    printf("%s : %d\n", capteurs[j].nomCapt, capteurs[j].variable, capteurs[j].fonction);
                    token = strtok(NULL, ",");
                }
            }
            k++;
        }
    }

    return 0;
}
