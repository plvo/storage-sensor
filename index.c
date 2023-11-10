#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_SENSOR_COUNT 13
#define MAX_FRIGO 4

// Déclaration des fonctions renvoyant les valeurs des différents capteurs :
// Chaque fonction doit renvoyer 0 si la valeur n'est pas celle attendu et 1 si tout est bon

//capteur ventilation
int VENTILATION_START(int variable) {
    if (variable==1){
        return 1;
    } else {
        return 0;
    }
}
//capteur du badge
int BADGE_ON(int variable){
    if (variable==1){
        return 1;
    } else {
        return 0;
    }
}
//capteur de l'ouverure de la porte du frigo
int ENTER_DOOR_OPEN(int variable){
    if (variable==1){
        return 1;
    } else {
        return 0;
    }
}

//capteur de la fermeture de la porte du frigo
int ENTER_DOOR_CLOSE(int variable){
    if (variable==1){
        return 1;
    } else {
        return 0;
    }
}
//lancement du chronomètre du frigo
int TIMER_ON(int variable){
    if (variable==1){
        return 1;
    } else {
        return 0;
    }
}
//capteur de la température du frigo avant toute action
int TEMP_START(int variable){
    if (variable==1){
        return 1;
    } else {
        return 0;
    }
}
//vérification du chronomètre
int TIMER_CHECK(int variable){
    if (variable<=10){
        return 1;
    } else {
        return 0;
    }
}
// capteur d'ouverture de porte à la sortie
int EXIT_DOOR_OPEN(int variable){
    if (variable==1){
        return 1;
    } else {
        return 0;
    }
}
//capteur de la fermeture de la porte à la sortie
int EXIT_DOOR_CLOSE(int variable){
    if (variable==1){
        return 1;
    } else {
        return 0;
    }
}
//vérification que le badge est récupéré
int BADGE_OFF(int variable){
    if (variable==1){
        return 1;
    } else {
        return 0;
    }
}
//vérification de la température à la fin de toute action
int TEMP_END(int variable){
    if (variable==1){
        return 1;
    } else {
        return 0;
    }
}
//vérification de l'état de la ventilation à la sortie
int VENTILATION_EXIT(int variable){
    if (variable==1){
        return 1;
    } else {
        return 0;
    }
}

// Définition de la structure d'un capteur
struct Capt {
    char *nomCapt; // nom du capteur
    int variable; // variable associée
    int (*fonction)(int);
};

// Boucle principale :
int main() {
    FILE *fichier;
    // Lecture du fichier de config
    fichier = fopen("./output/./output/config.csv", "r");

    // Vérification de la bonne lecture du fichier config
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    char ligne[MAX_LINE_LENGTH];
    struct Capt capteurs[MAX_SENSOR_COUNT];

    if (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char *token = strtok(ligne, ",");
        struct Capt capteurs[12];
        
        int i = 0;
        while (token != NULL) {
            printf("token actuel : %s\n", token);
            capteurs[i].variable = 0;
            capteurs[i].nomCapt = strdup(token);
            printf("Capteur ajoute : %s\n", capteurs[i].nomCapt);
            token = strtok(NULL, ",");
            i++;
            // int resultat = capteurs[i].fonction(capteurs[i].variable);
            // printf("Resultat pour %s : %d \n\n\n", token, resultat);
        }

        for (int j = 0; j < 13; j++){
            printf("%d) %s\n", j, capteurs[j].nomCapt);
        }
    }

    fclose(fichier);
    return 0;
}

 
// soit tab_de_base le tableau des frigos et leur capteur
// soit x le nombre de lignes dans ce tab
// soit y le nombre de colonnes dans ce tab

// int tab_total[x]
// for (int i = 0; i < x; i++){
//      int tab_frigo[y]
//      for (int j = 0; j < y; j++){
//          data = "récup de data"
//          tab_total[j].append(data)
//   }}

fnbezugfi