#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// Déclaration des fonctions renvoyant les valeurs des différents capteurs :

//capteur ventilation
int VENTILATION_START(int variable){
    return variable;
}
//capteur du badge
int BADGE_ON(int variable){
    return variable;
}
//capteur de l'ouverure de la porte du frigo
int ENTER_DOOR_OPEN(int variable){
    return variable;
}

//capteur de la fermeture de la porte du frigo
int ENTER_DOOR_CLOSE(int variable){
    return variable;
}
//lancement du chronomètre du frigo
int TIMER_ON(int variable){
    return variable;
}
//capteur de la température du frigo avant toute action
int TEMP_START(int variable){
    return variable;
}
//vérification du chronomètre
int TIMER_CHECK(int variable){
    return variable;
}
// capteur d'ouverture de porte à la sortie
int EXIT_DOOR_OPEN(int variable){
    return variable;
}
//capteur de la fermeture de la porte à la sortie
int EXIT_DOOR_CLOSE(int variable){
    return variable;
}
//vérification que le badge est récupéré
int BADGE_OFF(int variable){
    return variable;
}
//vérification de la température à la fin de toute action
int TEMP_END(int variable){
    return variable;
}
//vérification de l'état de la ventilation à la sortie
int VENTILATION_EXIT(int variable){
    return variable;
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
    fichier = fopen("./output/config.csv", "r");

    // Vérification de la bonne lecture du fichier config
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    char ligne[MAX_LINE_LENGTH];

    if (fgets(ligne, sizeof(ligne), fichier) != NULL) { // lecture d'une ligne du fichier de config et Stocke cette ligne  
        char *token = strtok(ligne, ","); // Diviser la ligne lue en tokens en utilisant la virgule comme séparateur et stocke la donnée au premier rang
        struct Capt capteurs[12];
        
        int i = 0;

        while (token != NULL) { // Parcours des tokens correspondant au frigo 
            printf("token actuel : %s\n", token);

            capteurs[i].variable = 0;
            capteurs[i].nomCapt = token; // Ajout de la donnée du token dans la variable 'capteurs'

            printf("token actuel 222 : %s\n\n", capteurs[i].nomCapt);

            token = strtok(NULL, ","); // Token se réfère à la donnée suivante

            i++;
            // int resultat = capteurs[i].fonction(capteurs[i].variable);
            // printf("Resultat pour %s : %d \n\n\n", token, resultat);
        }

        for (int i = 0; i < 13; i++){
            printf("%d) %s\n", i, capteurs[i].nomCapt);
        }
        
        // for (i = 0; i < 12; i++) {
        //     int resultat = capteurs[i].fonction(capteurs[i].variable);
        //     printf("Resultat pour %s : %d \n", token, resultat);
        // }
    }

    fclose(fichier);
    return 0;
}
