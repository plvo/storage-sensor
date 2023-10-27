#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int VENTILATION_START(int variable);
int BADGE_ON(int variable);
int ENTER_DOOR_OPEN(int variable);
int ENTER_DOOR_CLOSE(int variable);
int TIMER_ON(int variable);
int TEMP_START(int variable);
int TIMER_CHECK(int variable);
int EXIT_DOOR_OPEN(int variable);
int EXIT_DOOR_CLOSE(int variable);
int BADGE_OFF(int variable);
int TEMP_END(int variable);
int VENTILATION_EXIT(int variable);



struct Capt {
    int variable;
    int (*fonction)(int);
};

int main() {
    FILE *fichier;
    fichier = fopen("config.csv", "r");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    char ligne[MAX_LINE_LENGTH];
    if (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char *token = strtok(ligne, ",");
        struct Capt capteurs[12];

        int i = 0;
        while (token != NULL) {
            printf("En-tête : %s\n", token);

            capteurs[i].variable = 0;
            if (strcmp(token, "VENTILATION_START")) {
                capteurs[i].fonction = VENTILATION_START;
                printf("%s\n",token);
            }
            else if (strcmp(token, "BADGE_ON") == 0) {
                capteurs[i].fonction = BADGE_ON;
            }
            else if (strcmp(token, "ENTER_DOOR_OPEN") == 0) {
                capteurs[i].fonction = ENTER_DOOR_OPEN;
            }
            else if (strcmp(token, "ENTER_DOOR_CLOSE") == 0) {
                capteurs[i].fonction = ENTER_DOOR_CLOSE;
            }
            else if (strcmp(token, "TIMER_ON") == 0) {
                capteurs[i].fonction = TIMER_ON;
            }
            else if (strcmp(token, "TEMP_START") == 0) {
                capteurs[i].fonction = TEMP_START;
            }
            else if (strcmp(token, "TIMER_CHECK") == 0) {
                capteurs[i].fonction = TIMER_CHECK;
            }
            else if (strcmp(token, "EXIT_DOOR_OPEN") == 0) {
                capteurs[i].fonction = EXIT_DOOR_OPEN;
            }
            else if (strcmp(token, "EXIT_DOOR_CLOSE") == 0) {
                capteurs[i].fonction = EXIT_DOOR_CLOSE;
            }
            else if (strcmp(token, "BADGE_OFF") == 0) {
                capteurs[i].fonction = BADGE_OFF;
            }
            else if (strcmp(token, "TEMP_END") == 0) {
                capteurs[i].fonction = TEMP_END;
            }
            else if (strcmp(token, "VENTILATION_EXIT") == 0) {
                capteurs[i].fonction = VENTILATION_EXIT;
            }

            token = strtok(NULL, ",");
            i++;
        }
        
        for (i = 0; i < 12; i++) {
            int resultat = capteurs[i].fonction(capteurs[i].variable);
            printf("Résultat pour %s : %d\n", token, resultat);
        }
    }

    fclose(fichier);
    return 0;
}


int VENTILATION_START(int variable){
    return variable;
}
int BADGE_ON(int variable){
    return variable;
}
int ENTER_DOOR_OPEN(int variable){
    return variable;
}
int ENTER_DOOR_CLOSE(int variable){
    return variable;
}
int TIMER_ON(int variable){
    return variable;
}
int TEMP_START(int variable){
    return variable;
}
int TIMER_CHECK(int variable){
    return variable;
}
int EXIT_DOOR_OPEN(int variable){
    return variable;
}
int EXIT_DOOR_CLOSE(int variable){
    return variable;
}
int BADGE_OFF(int variable){
    return variable;
}
int TEMP_END(int variable){
    return variable;
}
int VENTILATION_EXIT(int variable){
    return variable;
}