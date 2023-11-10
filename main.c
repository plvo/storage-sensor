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

int main() {
    FILE *fichier;
    fichier = fopen("./config.csv", "r");

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
        nombre_lignes = nombre_lignes - 1;
        printf("Nombre de lignes : %d\n", nombre_lignes);
        printf("Nombre de colonnes : %d\n", nombre_colonnes);
    } else {
        printf("Le fichier est vide ou ne contient pas de données CSV valides.\n");
    }

    int *allFrigo = (int *)malloc(nombre_lignes * sizeof(int));
    if (allFrigo == NULL) {
        printf("Échec de l'allocation de mémoire.\n");
        return 1;
    }

    for (int y = 0; y < nombre_lignes; y++) {
        //création d'un sous tableau
        int *frigo = (int *)malloc(nombre_colonnes * sizeof(int));

        //remplissage du frigo
        for (int w = 0; w < nombre_colonnes; w++){
            //pour chaque rec, créé l'objet associé en utilisant la structure et l'ajouter au frigo
            
        }


        //ajout du sous tableau dans allFrigo
        allFrigo[y] = frigo;
    }

    free(allFrigo);

    return 0;
}
