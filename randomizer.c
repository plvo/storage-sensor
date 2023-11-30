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
    printf("Ligne ajoutee au fichier CSV avec succes.\n");
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

int ArrayFormatForCSV(){
    int ArrayForCSV[13];
    ArrayForCSV[0] = nombreDeLignesDansCSV("testconfig.csv");
    ArrayForCSV[1] = randomIntGen(0, 1);
    ArrayForCSV[2] = randomIntGen(0, 1);
    ArrayForCSV[3] = randomIntGen(0, 1);
    ArrayForCSV[4] = randomIntGen(0, 1);
    ArrayForCSV[5] = randomIntGen(0, 1);
    ArrayForCSV[6] = randomIntGen(-42, -38);
    ArrayForCSV[7] = randomIntGen(0, 10);
    ArrayForCSV[8] = randomIntGen(0, 1);
    ArrayForCSV[9] = randomIntGen(0, 1);
    ArrayForCSV[10] = randomIntGen(0, 1);
    ArrayForCSV[11] = randomIntGen(-42, -38);
    ArrayForCSV[12] = randomIntGen(0, 1);

    ajouterLigneCSV("testconfig.csv", ArrayForCSV, 13);

}










int main(){
    int NumberOfFrigo = 67; // Put here the number of frigo that you have in your Cave
    for (int i = 0; i < NumberOfFrigo; ++i) {
        ArrayFormatForCSV();
    }
    return 0;
}