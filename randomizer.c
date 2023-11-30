//bibliotheque 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int ClearCSV() {
    const char *nomFichier = "testconfig.csv";

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
        perror("Erreur lors de l'ouverture du fichier en écriture");
        return 1;
    }

    // Écrire la première ligne dans le fichier
    fputs(premiereLigne, fichier);

    // Fermer le fichier en écriture
    fclose(fichier);

    printf("Contenu du fichier CSV (sauf la première ligne) effacé avec succès.\n");

    return 0;
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


// allocation de mémoire pour notre tableau (de valeur aléatoire)
int* arrayValCapt(int min, int max, int taille) {
    // Allouer dynamiquement un tableau de taille "taille"
    int *tableau = malloc(taille * sizeof(int));

    if (tableau == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < taille; ++i) {
        tableau[i] = rand() % (max - min + 1) + min;
    }
    return tableau;
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
    printf("Ligne ajoutée au fichier CSV avec succès.\n");
}

int randomArray(int arrayMin, int arrayMax) {
    const int taille = 13;
    const char *nomFichierCSV = "testconfig.csv";

    // Initialiser le générateur de nombres aléatoires avec une nouvelle graine
    srand((unsigned int)time(NULL));

    // Générer le tableau random
    int *tab1 = arrayValCapt(arrayMin, arrayMax, taille);

    // Afficher le tableau
    printf("Tableau : ");
    for (int i = 0; i < taille; ++i) {
        printf("%d ", tab1[i]);
    }
    printf("\n");

    // Ajouter la ligne dans le CSV 
    ajouterLigneCSV(nomFichierCSV, tab1, taille);

    free(tab1);

    return 0;
}



int main(){
    ClearCSV();
    randomArray(2, 20);
    return 0;
}