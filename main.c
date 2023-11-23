#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <time.h>

#define MAX_LINE_LENGTH 1024
#define MAX_SENSOR_COUNT 13
#define BUFSIZE 4096

struct Capt
{
    char *nomCapt;
    int variable;
    int (*fonction)(int);
};

void write_CSV(const char *data)
{
    // Open file
    FILE *file = fopen("log.csv", "a");
    if (file == NULL)
    {
        perror("fichier introuvable");
        return;
    }
    // Écrire donnée et fermer file
    fprintf(file, "%s\n", data);
    fclose(file);
}

// Fonction pour lire un fichier CSV
int lireCSV(const char *nomFichier, char ***donnees, size_t *nbLignes, size_t *nbColonnes) {
    FILE *fichier = fopen(global_config.csv, "r");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0; // Indiquer une erreur
    }

    // Variables pour stocker les données lues
    char ligne[MAX_LIGNE];
    size_t lignes = 2;
    size_t colonnes = 4#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <time.h>

#define MAX_LINE_LENGTH 1024
#define MAX_SENSOR_COUNT 13
#define BUFSIZE 4096

struct Capt
{
    char *nomCapt;
    int variable;
    int (*fonction)(int);
};

void write_CSV(const char *data)
{
    // Open file
    FILE *file = fopen("log.csv", "a");
    if (file == NULL)
    {
        perror("fichier introuvable");
        return;
    }
    // Écrire donnée et fermer file
    fprintf(file, "%s\n", data);
    fclose(file);
}

// Fonction pour lire un fichier CSV
int lireCSV(const char *nomFichier, char ***donnees, size_t *nbLignes, size_t *nbColonnes) {
    FILE *fichier = fopen(global_config.csv, "r");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0; // Indiquer une erreur
    }

    // Variables pour stocker les données lues
    char ligne[MAX_LIGNE];
    size_t lignes = 2;
    size_t colonnes = 4;

    // Compter le nombre de colonnes dans la première ligne
    if (fgets(ligne, MAX_LIGNE, fichier) != NULL) {
        char *token = strtok(ligne, ",");
        while (token != NULL) {
            token = strtok(NULL, ",");
            colonnes++;
        }
    } else {
        // Fichier vide
        fclose(fichier);
        return 0; // Indiquer une erreur
    }

    // Rembobiner le fichier à la première ligne
    rewind(fichier);

    // Allouer de la mémoire pour stocker les données
    *donnees = (char ***)malloc(MAX_LIGNE * sizeof(char *));
    for (size_t i = 0; i < MAX_LIGNE; i++) {
        (*donnees)[i] = (char **)malloc(colonnes * sizeof(char *));
        for (size_t j = 0; j < colonnes; j++) {
            (*donnees)[i][j] = (char *)malloc(MAX_COLONNE * sizeof(char));
        }
    }

    // Lire le fichier ligne par ligne
    while (fgets(ligne, MAX_LIGNE, fichier) != NULL) {
        char *token = strtok(ligne, ",");
        size_t colonne = 0;
        while (token != NULL && colonne < colonnes) {
            strcpy((*donnees)[lignes][colonne], token);
            token = strtok(NULL, ",");
            colonne++;
        }
        lignes++;
    }

    // Fermer le fichier
    fclose(fichier);

    // Mettre à jour les paramètres de sortie
    *nbLignes = lignes;
    *nbColonnes = colonnes;

    return 1; // Indiquer le succès
}

// Déclaration des fonctions renvoyant les valeurs des différents capteurs :
// Chaque fonction doit renvoyer 0 si la valeur n'est pas celle attendu et 1 si tout est bon

// capteur ventilation
int VENTILATION_START(int variable) {
    if (variable==1){
        write_CSV("La ventillation du frigo fonctionne - OK \n");
        return 1;
    } else {
        write_CSV("La ventillation du frigo ne fonctionne pas - STOP (error) \n");
        return 0;
    }
}
//capteur du badge
int BADGE_ON(int variable){
    if (variable==1){
        write_CSV("Le badge a ete depose - OK \n");
        return 1;
    } else {
        write_CSV("Le badge n'a pas ete depose - STOP (error) \n");
        return 0;
    }
}
//capteur de l'ouverure de la porte du frigo
int ENTER_DOOR_OPEN(int variable){
    if (variable==1){
        write_CSV("La porte s'est ouverte - OK \n");
        return 1;
    } else {
        write_CSV("La porte ne s'est pas ouverte - STOP (error) \n");
        return 0;
    }
}

//capteur de la fermeture de la porte du frigo
int ENTER_DOOR_CLOSE(int variable){
    if (variable==1){
        write_CSV("La porte a ete refermee - OK \n");
        return 1;
    } else {
        write_CSV("La porte n'a pas ete refermee - STOP (error) \n");
        return 0;
    }
}
//lancement du chronomètre du frigo
int TIMER_ON(int variable){
    if (variable==1){
        write_CSV("Le chronomètre a ete lance - OK \n");
        return 1;
    } else {
        write_CSV("Le chronomètre ne s'est pas lance - STOP (error) \n");
        return 0;
    }
}
//capteur de la température du frigo avant toute action
int TEMP_START(int variable){
    if (variable==-40){
        write_CSV("La temperature est valide - OK \n");
        return 1;
    } else {
        write_CSV("La temperature n'est pas bonne - STOP (error) \n");
        return 0;
    }
}

//vérification du chronomètre
int TIMER_CHECK(int variable){
    char message[100];

    if (variable<=10){
        sprintf(message, "L'employe est reste %d min dans le frigo - OK\n", variable);
        write_CSV(message);
        return 1;
    } else {
        sprintf(message, "L'employe est reste %d min dans le frigo. Une alerte a ete declenchee - STOP (error) \n", variable);
        write_CSV(message);
        return 0;
    }
}
// capteur d'ouverture de porte a la sortie
int EXIT_DOOR_OPEN(int variable){
    if (variable==1){
        write_CSV("La porte a ete ouverte - OK \n");
        return 1;
    } else {
        write_CSV("La porte n'a pas ete ouverte - STOP (error) \n");
        return 0;
    }
}
//capteur de la fermeture de la porte a la sortie
int EXIT_DOOR_CLOSE(int variable){
    if (variable==1){
        write_CSV("La porte a ete refermee - OK \n");
        return 1;
    } else {
        write_CSV("La porte n'a pas ete refermee - STOP (error) \n");
        return 0;
    }
}
//verification que le badge est recupere
int BADGE_OFF(int variable){
    if (variable==1){
        write_CSV("Le badge a ete recupere - OK \n");
        return 1;
    } else {
        write_CSV("Le badge n'a pas ete recupere - STOP (error) \n");
        return 0;
    }
}
//vérification de la température a la fin de toute action
int TEMP_END(int variable){
    if (variable==-40){
        write_CSV("La temperature est correcte apres passage - OK \n");
        return 1;
    } else {
        write_CSV("La temperature n'est pas correcte apres passage - STOP (error) \n");
        return 0;
    }
}
//vérification de l'état de la ventilation a la sortie
int VENTILATION_EXIT(int variable){
    if (variable==1){
        write_CSV("La ventilation est toujours active apres passage - OK \n");
        return 1;
    } else {
        write_CSV("La ventilation n'est plus active apres passage - STOP (error) \n");
        return 0;
    }
}

int main()
{
    FILE *fichier;
    fichier = fopen("config.csv", "r");

    // Vérification de la bonne lecture du fichier config
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    int nombre_lignes = 0;
    int nombre_colonnes = 0;
    char ligne[MAX_LINE_LENGTH];

    // Lire le fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        nombre_lignes++;

        // La première ligne est supposée contenir les en-têtes des colonnes
        if (nombre_lignes == 1)
        {
            char *token = strtok(ligne, ",");
            while (token != NULL)
            {
                nombre_colonnes++;
                token = strtok(NULL, ",");
            }
        }
    }

    fclose(fichier);

    if (nombre_lignes > 0 && nombre_colonnes > 0)
    {
        nombre_lignes -= 1;
        printf("Nombre de lignes : %d\n", nombre_lignes);
        printf("Nombre de colonnes : %d\n", nombre_colonnes);

        // Initialisation du tableau global avec sa memoire
        struct Capt ***allFrigo = (struct Capt ***)malloc(nombre_lignes * sizeof(struct Capt **));
        if (allFrigo == NULL)
        {
            printf("Échec de l'allocation de mémoire.\n");
            return 1;
        }

        rewind(fichier);

        FILE *fp;
        fp = fopen("config.csv", "r");
        if (fp == NULL)
        {
            printf("Erreur fopen\n");
            return 1;
        }

        for (int y = 1; y <= nombre_lignes; y++)
        {
            struct Capt **frigo = (struct Capt **)malloc(nombre_colonnes * sizeof(struct Capt *)); // frigo est un tableau de capteur

            for (int i = 0; i < nombre_colonnes; i++)
            {
                frigo[i] = (struct Capt *)malloc(sizeof(struct Capt));
                if (frigo[i] == NULL)
                {
                    printf("Échec de l'allocation de mémoire pour frigo[i].\n");
                    return 1;
                }
            }

            char str[BUFSIZE];
            int i = 0;
            char ligne[1000];

            while (fgets(str, BUFSIZE, fp) != NULL)
            { // Parcours des lignes de fichier
                if (i == y)
                {                       // Si l'index parcouru = index de la ligne rechercher
                    strcpy(ligne, str); // ligne contient les valeurs
                    printf("Contenu de la ligne : %s\n", str);
                }
                i++;
            }

            char *token = strtok(ligne, ","); // Initialisation du délimiteur
            int captCount = 0;
            while (token != NULL)
            {
                // printf("Element %d : %s\n", captCount + 1, token);

                // Créer une variable structure Capt
                struct Capt nouveauCapteur;

                // Générer un nom de capteur unique
                char nom[100];
                snprintf(nom, sizeof(nom), "capteur_%d", captCount);
                nouveauCapteur.nomCapt = strdup(nom);

                // Conditions de mise en place des fonctions :
                if (strcmp(nouveauCapteur.nomCapt, "capteur_1") == 0){
                    printf("capteur_2\n");
                    nouveauCapteur.fonction = VENTILATION_START;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_2") == 0){
                    printf("capteur_3\n");
                    nouveauCapteur.fonction = BADGE_ON;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_3") == 0){
                    printf("capteur_4\n");
                    nouveauCapteur.fonction = ENTER_DOOR_OPEN;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_4") == 0){
                    nouveauCapteur.fonction = ENTER_DOOR_CLOSE;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_5") == 0){
                    nouveauCapteur.fonction = TIMER_ON;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_6") == 0){
                    nouveauCapteur.fonction = TEMP_START;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_7") == 0){
                    nouveauCapteur.fonction = TIMER_CHECK;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_8") == 0){
                    nouveauCapteur.fonction = EXIT_DOOR_OPEN;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_9") == 0){
                    nouveauCapteur.fonction = EXIT_DOOR_CLOSE;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_10") == 0){
                    nouveauCapteur.fonction = BADGE_OFF;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_11") == 0){
                    nouveauCapteur.fonction = TEMP_END;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_12") == 0){
                    nouveauCapteur.fonction = VENTILATION_EXIT;
                }               
// nouveauCapteur.fonction = VENTILATION_START;
                //

                // Convertir la valeur en entier
                nouveauCapteur.variable = atoi(token);
                // printf("Capt : %d \n", nouveauCapteur.variable);


                // Affecter le nouveau capteur au tableau frigo
                *frigo[captCount] = nouveauCapteur;

                token = strtok(NULL, ",");
                captCount++;

                // printf("Nom : %s \n",nouveauCapteur.nomCapt);
            }

            rewind(fp); // Réinitialiser le curseur

            allFrigo[y] = frigo;
            // fclose(fp);
        }

        // Affichage des valeurs de tous les frigo
        for (int p = 1; p <= nombre_lignes; p++) {
            
            char message[100];
            sprintf(message, "# FRIGO %d #", p);
            write_CSV("###########");
            write_CSV(message);
            write_CSV("###########\n");

            for (int o = 1; o < nombre_colonnes; o++) {
                int resultat = allFrigo[p][o]->fonction(allFrigo[p][o]->variable);
                                printf("Le resultat est : %d\n", resultat);

                // printf("Valeur de %s : %d \n", allFrigo[p][o]->nomCapt,allFrigo[p][o]->variable);
            }
            printf("\n");
        }

        // Libération de la mémoire
        for (int i = 1; i <= nombre_lignes; i++) {
            for (int j = 0; j < nombre_colonnes; j++) {
                free(allFrigo[i][j]);
            }
            free(allFrigo[i]);
        }
        free(allFrigo);
    }
    else
    {
        printf("Le fichier est vide ou ne contient pas de données CSV valides.\n");
    }

    return 0;
}
;

    // Compter le nombre de colonnes dans la première ligne
    if (fgets(ligne, MAX_LIGNE, fichier) != NULL) {
        char *token = strtok(ligne, ",");
        while (token != NULL) {
            token = strtok(NULL, ",");
            colonnes++;
        }
    } else {
        // Fichier vide
        fclose(fichier);
        return 0; // Indiquer une erreur
    }

    // Rembobiner le fichier à la première ligne
    rewind(fichier);

    // Allouer de la mémoire pour stocker les données
    *donnees = (char ***)malloc(MAX_LIGNE * sizeof(char *));
    for (size_t i = 0; i < MAX_LIGNE; i++) {
        (*donnees)[i] = (char **)malloc(colonnes * sizeof(char *));
        for (size_t j = 0; j < colonnes; j++) {
            (*donnees)[i][j] = (char *)malloc(MAX_COLONNE * sizeof(char));
        }
    }

    // Lire le fichier ligne par ligne
    while (fgets(ligne, MAX_LIGNE, fichier) != NULL) {
        char *token = strtok(ligne, ",");
        size_t colonne = 0;
        while (token != NULL && colonne < colonnes) {
            strcpy((*donnees)[lignes][colonne], token);
            token = strtok(NULL, ",");
            colonne++;
        }
        lignes++;
    }

    // Fermer le fichier
    fclose(fichier);

    // Mettre à jour les paramètres de sortie
    *nbLignes = lignes;
    *nbColonnes = colonnes;

    return 1; // Indiquer le succès
}

// Déclaration des fonctions renvoyant les valeurs des différents capteurs :
// Chaque fonction doit renvoyer 0 si la valeur n'est pas celle attendu et 1 si tout est bon

// capteur ventilation
int VENTILATION_START(int variable) {
    if (variable==1){
        write_CSV("La ventillation du frigo fonctionne - OK \n");
        return 1;
    } else {
        write_CSV("La ventillation du frigo ne fonctionne pas - STOP (error) \n");
        return 0;
    }
}
//capteur du badge
int BADGE_ON(int variable){
    if (variable==1){
        write_CSV("Le badge a ete depose - OK \n");
        return 1;
    } else {
        write_CSV("Le badge n'a pas ete depose - STOP (error) \n");
        return 0;
    }
}
//capteur de l'ouverure de la porte du frigo
int ENTER_DOOR_OPEN(int variable){
    if (variable==1){
        write_CSV("La porte s'est ouverte - OK \n");
        return 1;
    } else {
        write_CSV("La porte ne s'est pas ouverte - STOP (error) \n");
        return 0;
    }
}

//capteur de la fermeture de la porte du frigo
int ENTER_DOOR_CLOSE(int variable){
    if (variable==1){
        write_CSV("La porte a ete refermee - OK \n");
        return 1;
    } else {
        write_CSV("La porte n'a pas ete refermee - STOP (error) \n");
        return 0;
    }
}
//lancement du chronomètre du frigo
int TIMER_ON(int variable){
    if (variable==1){
        write_CSV("Le chronomètre a ete lance - OK \n");
        return 1;
    } else {
        write_CSV("Le chronomètre ne s'est pas lance - STOP (error) \n");
        return 0;
    }
}
//capteur de la température du frigo avant toute action
int TEMP_START(int variable){
    if (variable==-40){
        write_CSV("La temperature est valide - OK \n");
        return 1;
    } else {
        write_CSV("La temperature n'est pas bonne - STOP (error) \n");
        return 0;
    }
}

//vérification du chronomètre
int TIMER_CHECK(int variable){
    char message[100];

    if (variable<=10){
        sprintf(message, "L'employe est reste %d min dans le frigo - OK\n", variable);
        write_CSV(message);
        return 1;
    } else {
        sprintf(message, "L'employe est reste %d min dans le frigo. Une alerte a ete declenchee - STOP (error) \n", variable);
        write_CSV(message);
        return 0;
    }
}
// capteur d'ouverture de porte a la sortie
int EXIT_DOOR_OPEN(int variable){
    if (variable==1){
        write_CSV("La porte a ete ouverte - OK \n");
        return 1;
    } else {
        write_CSV("La porte n'a pas ete ouverte - STOP (error) \n");
        return 0;
    }
}
//capteur de la fermeture de la porte a la sortie
int EXIT_DOOR_CLOSE(int variable){
    if (variable==1){
        write_CSV("La porte a ete refermee - OK \n");
        return 1;
    } else {
        write_CSV("La porte n'a pas ete refermee - STOP (error) \n");
        return 0;
    }
}
//verification que le badge est recupere
int BADGE_OFF(int variable){
    if (variable==1){
        write_CSV("Le badge a ete recupere - OK \n");
        return 1;
    } else {
        write_CSV("Le badge n'a pas ete recupere - STOP (error) \n");
        return 0;
    }
}
//vérification de la température a la fin de toute action
int TEMP_END(int variable){
    if (variable==-40){
        write_CSV("La temperature est correcte apres passage - OK \n");
        return 1;
    } else {
        write_CSV("La temperature n'est pas correcte apres passage - STOP (error) \n");
        return 0;
    }
}
//vérification de l'état de la ventilation a la sortie
int VENTILATION_EXIT(int variable){
    if (variable==1){
        write_CSV("La ventilation est toujours active apres passage - OK \n");
        return 1;
    } else {
        write_CSV("La ventilation n'est plus active apres passage - STOP (error) \n");
        return 0;
    }
}

int main()
{
    FILE *fichier;
    fichier = fopen("config.csv", "r");

    // Vérification de la bonne lecture du fichier config
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    int nombre_lignes = 0;
    int nombre_colonnes = 0;
    char ligne[MAX_LINE_LENGTH];

    // Lire le fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        nombre_lignes++;

        // La première ligne est supposée contenir les en-têtes des colonnes
        if (nombre_lignes == 1)
        {
            char *token = strtok(ligne, ",");
            while (token != NULL)
            {
                nombre_colonnes++;
                token = strtok(NULL, ",");
            }
        }
    }

    fclose(fichier);

    if (nombre_lignes > 0 && nombre_colonnes > 0)
    {
        nombre_lignes -= 1;
        printf("Nombre de lignes : %d\n", nombre_lignes);
        printf("Nombre de colonnes : %d\n", nombre_colonnes);

        // Initialisation du tableau global avec sa memoire
        struct Capt ***allFrigo = (struct Capt ***)malloc(nombre_lignes * sizeof(struct Capt **));
        if (allFrigo == NULL)
        {
            printf("Échec de l'allocation de mémoire.\n");
            return 1;
        }

        rewind(fichier);

        FILE *fp;
        fp = fopen("config.csv", "r");
        if (fp == NULL)
        {
            printf("Erreur fopen\n");
            return 1;
        }

        for (int y = 1; y <= nombre_lignes; y++)
        {
            struct Capt **frigo = (struct Capt **)malloc(nombre_colonnes * sizeof(struct Capt *)); // frigo est un tableau de capteur

            for (int i = 0; i < nombre_colonnes; i++)
            {
                frigo[i] = (struct Capt *)malloc(sizeof(struct Capt));
                if (frigo[i] == NULL)
                {
                    printf("Échec de l'allocation de mémoire pour frigo[i].\n");
                    return 1;
                }
            }

            char str[BUFSIZE];
            int i = 0;
            char ligne[1000];

            while (fgets(str, BUFSIZE, fp) != NULL)
            { // Parcours des lignes de fichier
                if (i == y)
                {                       // Si l'index parcouru = index de la ligne rechercher
                    strcpy(ligne, str); // ligne contient les valeurs
                    printf("Contenu de la ligne : %s\n", str);
                }
                i++;
            }

            char *token = strtok(ligne, ","); // Initialisation du délimiteur
            int captCount = 0;
            while (token != NULL)
            {
                // printf("Element %d : %s\n", captCount + 1, token);

                // Créer une variable structure Capt
                struct Capt nouveauCapteur;

                // Générer un nom de capteur unique
                char nom[100];
                snprintf(nom, sizeof(nom), "capteur_%d", captCount);
                nouveauCapteur.nomCapt = strdup(nom);

                // Conditions de mise en place des fonctions :
                if (strcmp(nouveauCapteur.nomCapt, "capteur_1") == 0){
                    printf("capteur_2\n");
                    nouveauCapteur.fonction = VENTILATION_START;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_2") == 0){
                    printf("capteur_3\n");
                    nouveauCapteur.fonction = BADGE_ON;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_3") == 0){
                    printf("capteur_4\n");
                    nouveauCapteur.fonction = ENTER_DOOR_OPEN;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_4") == 0){
                    nouveauCapteur.fonction = ENTER_DOOR_CLOSE;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_5") == 0){
                    nouveauCapteur.fonction = TIMER_ON;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_6") == 0){
                    nouveauCapteur.fonction = TEMP_START;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_7") == 0){
                    nouveauCapteur.fonction = TIMER_CHECK;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_8") == 0){
                    nouveauCapteur.fonction = EXIT_DOOR_OPEN;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_9") == 0){
                    nouveauCapteur.fonction = EXIT_DOOR_CLOSE;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_10") == 0){
                    nouveauCapteur.fonction = BADGE_OFF;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_11") == 0){
                    nouveauCapteur.fonction = TEMP_END;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_12") == 0){
                    nouveauCapteur.fonction = VENTILATION_EXIT;
                }               
// nouveauCapteur.fonction = VENTILATION_START;
                //

                // Convertir la valeur en entier
                nouveauCapteur.variable = atoi(token);
                // printf("Capt : %d \n", nouveauCapteur.variable);


                // Affecter le nouveau capteur au tableau frigo
                *frigo[captCount] = nouveauCapteur;

                token = strtok(NULL, ",");
                captCount++;

                // printf("Nom : %s \n",nouveauCapteur.nomCapt);
            }

            rewind(fp); // Réinitialiser le curseur

            allFrigo[y] = frigo;
            // fclose(fp);
        }

        // Affichage des valeurs de tous les frigo
        for (int p = 1; p <= nombre_lignes; p++) {
            
            char message[100];
            sprintf(message, "# FRIGO %d #", p);
            write_CSV("###########");
            write_CSV(message);
            write_CSV("###########\n");

            for (int o = 1; o < nombre_colonnes; o++) {
                int resultat = allFrigo[p][o]->fonction(allFrigo[p][o]->variable);
                                printf("Le resultat est : %d\n", resultat);

                // printf("Valeur de %s : %d \n", allFrigo[p][o]->nomCapt,allFrigo[p][o]->variable);
            }
            printf("\n");
        }

        // Libération de la mémoire
        for (int i = 1; i <= nombre_lignes; i++) {
            for (int j = 0; j < nombre_colonnes; j++) {
                free(allFrigo[i][j]);
            }
            free(allFrigo[i]);
        }
        free(allFrigo);
    }
    else
    {
        printf("Le fichier est vide ou ne contient pas de données CSV valides.\n");
    }

    return 0;
}
