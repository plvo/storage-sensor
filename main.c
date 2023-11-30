#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <time.h>

#define MAX_LINE_LENGTH 1024
#define MAX_SENSOR_COUNT 13
#define MAX_FRIGO 5

#define MAX_LINE_SIZE 1024
#define MAX_FIELD_SIZE 50

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
    FILE *file = fopen("log.txt", "a");
    if (file == NULL)
    {
        perror("fichier introuvable");
        return;
    }
    // Écrire donnée et fermer file
    fprintf(file, "%s\n", data);
    fclose(file);
}

void viderFichier(const char *nomFichier) {
    // Ouvrir le fichier en mode écriture
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    // Fermer le fichier pour le vider
    fclose(fichier);
    printf("Le fichier %s a ete vide avec succes.\n", nomFichier);
}

//Récuperer les variables de configuration
char* globalConfig(const char* find) {
    FILE *fp;
    fp = fopen("./config/global_config.csv", "r");
    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return NULL;
    }

    char str[BUFSIZE];
    int i = 0;
    char ligne[1000];
    int index = 0;
    int variant = 0;

    while (fgets(str, BUFSIZE, fp) != NULL)
    { // Parcours des lignes de fichier
        if (i == 0)
        {                       // Si l'index parcouru = index de la ligne rechercher
            strcpy(ligne, str); // ligne contient les valeurs

            char *token = strtok(ligne, ",");
            while (token != NULL){
                if (strcmp(token, find) == 0){
                    index=variant;
                }
                variant++;
                token = strtok(NULL, ",");
            }
        }

        if (i == 1)
        {                       // Si l'index parcouru = index de la ligne rechercher
            strcpy(ligne, str); // ligne contient les valeurs

            char *token = strtok(ligne, ",");
            int y = 0;
            while (token != NULL){
                if (index == y){
                    fclose(fp);
                    return strdup(token);
                }
                token = strtok(NULL, ",");

                y++;
            }
        }
        i++;
    }

    fclose(fp);
    return 0; // Configuration non trouvée
}
//

// Déclaration des fonctions renvoyant les valeurs des différents capteurs :
// Chaque fonction doit renvoyer 0 si la valeur n'est pas celle attendu et 1 si tout est bon

int SAS_OPEN(int variable){
    if (variable==1){
        write_CSV("Le SAS s'ouvre - OK\n");
        return 1;
    } else {
        write_CSV("Le SAS se ferme - STOP (error) \n");
        return 0;
    }
}

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
    int tempLow = atoi(globalConfig("TEMP_LOW"));
    int tempMax = atoi(globalConfig("TEMP_HIGH"));

    if (variable >= tempLow && variable <= tempMax) {
        write_CSV("La temperature est valide - OK \n");
        return 1;
    } else {
        write_CSV("La temperature n'est pas bonne - STOP (erreur) \n");
        return 0;
    }
}

//vérification du chronomètre
int TIMER_CHECK(int variable){
    char message[100];
    int limit = atoi(globalConfig("ALARM_TIME"));

    if (variable<=limit){
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

int SAS_CLOSE(int variable){
    if (variable==1){
        write_CSV("Le SAS s'ouvre - OK\n");
        return 1;
    } else {
        write_CSV("Le SAS ne s'ouvre pas - STOP (error) \n");
        return 0;
    }
}

////////////////////////////////////////////RANDOMIZER///////////////////////////////////////////
int ClearCSV() {
    const char *nomFichier = "./config/config.csv";
    // Ouvrir le fichier en mode lecture
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        return 1;
    }
    // Lire et stocker la première ligne
    char premiereLigne[1024];  // Taille maximale de la ligne (ajuster si nécessaire)
    if (fgets(premiereLigne, sizeof(premiereLigne), fichier) == NULL) {
        perror("Erreur lors de la lecture de la première ligne");
        fclose(fichier);
        return 1;
    }
    // Fermer le fichier en lecture
    fclose(fichier);
    // Ouvrir le fichier en mode écriture (efface le contenu existant)
    fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier en ecriture");
        return 1;
    }
    // Écrire la première ligne dans le fichier
    fputs(premiereLigne, fichier);

    // Fermer le fichier en écriture
    fclose(fichier);
    printf("Contenu du fichier CSV (sauf la première ligne) efface avec succès.\n");
    return 0;
}

// ajouter notre tableau a notre CSV de config 
void ajouterLigneCSV(const char *nomFichier, int tableau[], int taille) {
    // Ouvrir le fichier en mode ajout (a) pour ajouter du contenu à la fin
    FILE *fichier = fopen(nomFichier, "a");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    // Écrire la ligne dans le fichier
    for (int i = 0; i < taille; ++i) {
        fprintf(fichier, "%d", tableau[i]);
        // Ajouter une virgule si ce n'est pas la dernière valeur
        if (i < taille - 1) {
            fprintf(fichier, ",");
        }
    }
    fprintf(fichier, "\n");
    // Fermer le fichier
    fclose(fichier);
}

int nombreDeLignesDansCSV(const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        return -1;  // Code d'erreur pour indiquer une erreur d'ouverture
    }
    int nombreDeLignes = 0;
    char ligne[1024];  // Taille maximale de la ligne
    // Lire chaque ligne du fichier
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        nombreDeLignes++;
    }
    fclose(fichier);
    return nombreDeLignes;
}


//générer un nopmbre aléatoire entre 2 nombre 
int randomIntGen(int min, int max) {
    if (min >= max) {
        fprintf(stderr, "Erreur : Les bornes ne sont pas valides.\n");
        exit(EXIT_FAILURE);
    }
    int plage = max - min + 1;
    int nombre = rand() % plage + min;
    return nombre;
}

void ArrayFormatForCSV(){
    int ArrayForCSV[15];
    ArrayForCSV[0] = nombreDeLignesDansCSV("./config/config.csv");
    ArrayForCSV[1] = randomIntGen(0, 1);
    ArrayForCSV[2] = randomIntGen(0, 1);
    ArrayForCSV[3] = randomIntGen(0, 1);
    ArrayForCSV[4] = randomIntGen(0, 1);
    ArrayForCSV[5] = randomIntGen(0, 1);
    ArrayForCSV[6] = randomIntGen(0, 1);
    ArrayForCSV[7] = randomIntGen(-42, -38);
    ArrayForCSV[8] = randomIntGen(0, 10);
    ArrayForCSV[9] = randomIntGen(0, 1);
    ArrayForCSV[10] = randomIntGen(0, 1);
    ArrayForCSV[11] = randomIntGen(0, 1);
    ArrayForCSV[12] = randomIntGen(-42, -38);
    ArrayForCSV[13] = randomIntGen(0, 1);
    ArrayForCSV[14] = randomIntGen(0, 1);

    ajouterLigneCSV("./config/config.csv", ArrayForCSV, 15);
}

////////////////////////////////////////////end RANDOMIZER///////////////////////////////////////////


int main()
{
    ClearCSV();
    int NumberOfFrigo = 11; // Put here the number of frigo that you have in your Cave
    for (int i = 0; i < NumberOfFrigo; ++i) {
        ArrayFormatForCSV();
    }

    viderFichier("log.txt");
    FILE *fichier;
    fichier = fopen("./config/config.csv", "r");

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
        // Initialisation du tableau global avec sa memoire
        struct Capt ***allFrigo = (struct Capt ***)malloc(nombre_lignes * sizeof(struct Capt **));
        if (allFrigo == NULL)
        {
            printf("Echec de l'allocation de memoire.\n");
            return 1;
        }

        rewind(fichier);

        FILE *fp;
        fp = fopen("./config/config.csv", "r");
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
                    printf("Echec de l'allocation de memoire pour frigo[i].\n");
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
                    nouveauCapteur.fonction = SAS_OPEN;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_2") == 0){
                    nouveauCapteur.fonction = VENTILATION_START;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_3") == 0){
                    nouveauCapteur.fonction = BADGE_ON;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_4") == 0){
                    nouveauCapteur.fonction = ENTER_DOOR_OPEN;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_5") == 0){
                    nouveauCapteur.fonction = ENTER_DOOR_CLOSE;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_6") == 0){
                    nouveauCapteur.fonction = TIMER_ON;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_7") == 0){
                    nouveauCapteur.fonction = TEMP_START;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_8") == 0){
                    nouveauCapteur.fonction = TIMER_CHECK;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_9") == 0){
                    nouveauCapteur.fonction = EXIT_DOOR_OPEN;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_10") == 0){
                    nouveauCapteur.fonction = EXIT_DOOR_CLOSE;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_11") == 0){
                    nouveauCapteur.fonction = BADGE_OFF;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_12") == 0){
                    nouveauCapteur.fonction = TEMP_END;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_13") == 0){
                    nouveauCapteur.fonction = VENTILATION_EXIT;
                } else if (strcmp(nouveauCapteur.nomCapt, "capteur_14") == 0){
                    nouveauCapteur.fonction = SAS_CLOSE;
                };
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
                printf("%d", resultat);

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
        printf("Le fichier est vide ou ne contient pas de donnees CSV valides.\n");
    }

    return 0;
}