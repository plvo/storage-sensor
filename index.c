#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

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

    if (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char *token = strtok(ligne, ",");
        struct Capt capteurs[12];
        
        int i = 0;

        while (token != NULL) {
            capteurs[i].variable = 0;
            capteurs[i].nomCapt = strdup(token);

            printf("%d) token actuel : %s\n\n",i, capteurs[i].nomCapt);

            token = strtok(NULL, ",");

            i++;
            // int resultat = capteurs[i].fonction(capteurs[i].variable);
            // printf("Resultat pour %s : %d \n\n\n", token, resultat);
        }

        for (int j = 0; i < 13; j++){
            printf("%d) %s = %d\n", i, capteurs[j].nomCapt, capteurs[j].variable);
        }
        
        // for (i = 0; i < 12; i++) {
        //     int resultat = capteurs[i].fonction(capteurs[i].variable);
        //     printf("Resultat pour %s : %d \n", token, resultat);
        // }
    }

    fclose(fichier);
    return 0;
}
