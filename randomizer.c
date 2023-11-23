#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randomIntGen(int min, int max) {
    if (min >= max) {
        fprintf(stderr, "Erreur : Les bornes ne sont pas valides.\n");
        exit(EXIT_FAILURE);
    }
    srand((unsigned int)time(NULL));
    int plage = max - min + 1;
    int nombre = rand() % plage + min;
    return nombre;
}

int* arrayValCapt(int min, int max) {
    // Allouer dynamiquement un tableau de taille 13
    int *tableau = malloc(13 * sizeof(int));

    if (tableau == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 13; ++i) {
        tableau[i] = rand() % (max - min + 1) + min;
    }

    return tableau;
}

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

int main() {
    const int taille = 13;
    const char *nomFichierCSV = "testconfig.csv";
    int *tab1 = arrayValCapt(2, 20);

    // Afficher le contenu du tableau
    printf("Tableau : ");
    for (int i = 0; i < taille; ++i) {
        printf("%d ", tab1[i]);
    }
    printf("\n");

    // Ajouter la ligne CSV avec le contenu du tableau
    ajouterLigneCSV(nomFichierCSV, tab1, taille);

    // Libérer la mémoire allouée dynamiquement
    free(tab1);

    return 0;
}
