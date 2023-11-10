#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_SENSOR_COUNT 13
#define MAX_FRIGO 4


void write_CSV(const char *data) {
    // Open file
    FILE *file = fopen("log.csv", "a"); 
    if (file == NULL) {
        perror("fichier introuvable");
        return;
    }
    // Écrire donnée et fermer file
    fprintf(file, "%s\n", data);
    fclose(file);
}


// Déclaration des fonctions renvoyant les valeurs des différents capteurs :
// Chaque fonction doit renvoyer 0 si la valeur n'est pas celle attendu et 1 si tout est bon

//capteur ventilation
int VENTILATION_START(int variable) {
    if (variable==1){
        write_CSV("La ventillation du frigo fonctionne - OK \n")
        return 1;
    } else {
        write_CSV("La ventillation du frigo ne fonctionne pas - STOP (error) \n")
        return 0;
    }
}
//capteur du badge
int BADGE_ON(int variable){
    if (variable==1){
        write_CSV("Le badge a ete depose - OK \n")
        return 1;
    } else {
        write_CSV("Le badge n'a pas ete depose - STOP (error) \n")
        return 0;
    }
}
//capteur de l'ouverure de la porte du frigo
int ENTER_DOOR_OPEN(int variable){
    if (variable==1){
        write_CSV("La porte s'est ouverte - OK \n")
        return 1;
    } else {
        write_CSV("La porte ne s'est pas ouverte - STOP (error) \n")
        return 0;
    }
}

//capteur de la fermeture de la porte du frigo
int ENTER_DOOR_CLOSE(int variable){
    if (variable==1){
        write_CSV("La porte a ete refermee - OK \n")
        return 1;
    } else {
        write_CSV("La porte n'a pas ete refermee - STOP (error) \n")
        return 0;
    }
}
//lancement du chronomètre du frigo
int TIMER_ON(int variable){
    if (variable==1){
        write_CSV("Le chronomètre a ete lance - OK \n")
        return 1;
    } else {
        write_CSV("Le chronomètre ne s'est pas lance - STOP (error) \n")
        return 0;
    }
}
//capteur de la température du frigo avant toute action
int TEMP_START(int variable){
    if (variable==-40){
        write_CSV("La temperature est valide - OK \n")
        return 1;
    } else {
        write_CSV("La temperature n'est pas bonne - STOP (error) \n")
        return 0;
    }
}

//vérification du chronomètre
int TIMER_CHECK(int variable){
    if (variable<=10){
        write_CSV("L'employe est reste %d min dans le frigo - OK \n",variable)
        return 1;
    } else {
        write_CSV("L'employe est reste %d min dans le frigo. Une alerte a ete declenchee - STOP (error) \n", variable)
        return 0;
    }
}
// capteur d'ouverture de porte a la sortie
int EXIT_DOOR_OPEN(int variable){
    if (variable==1){
        write_CSV("La porte a ete ouverte - OK \n")
        return 1;
    } else {
        write_CSV("La porte n'a pas ete ouverte - STOP (error) \n")
        return 0;
    }
}
//capteur de la fermeture de la porte a la sortie
int EXIT_DOOR_CLOSE(int variable){
    if (variable==1){
        write_CSV("La porte a ete refermee - OK \n")
        return 1;
    } else {
        write_CSV("La porte n'a pas ete refermee - STOP (error) \n")
        return 0;
    }
}
//verification que le badge est recupere
int BADGE_OFF(int variable){
    if (variable==1){
        write_CSV("Le badge a ete recupere - OK \n")
        return 1;
    } else {
        write_CSV("Le badge n'a pas ete recupere - STOP (error) \n")
        return 0;
    }
}
//vérification de la température a la fin de toute action
int TEMP_END(int variable){
    if (variable==-40){
        write_CSV("La temperature est correcte apres passage - OK \n")
        return 1;
    } else {
        write_CSV("La temperature n'est pas correcte apres passage - STOP (error) \n")
        return 0;
    }
}
//vérification de l'état de la ventilation a la sortie
int VENTILATION_EXIT(int variable){
    if (variable==1){
        write_CSV("La ventilation est toujours active apres passage - OK \n")
        return 1;
    } else {
        write_CSV("La ventilation n'est plus active apres passage - STOP (error) \n")
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

