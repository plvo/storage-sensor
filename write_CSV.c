#include <stdio.h>

void write_CSV(const char *data) {
    // Open file
    FILE *file = fopen("log.txt", "a"); 
    if (file == NULL) {
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

int main() {
    viderFichier("log.txt");
    write_CSV("la tu met ce que tu veut marquer pelouz");
    write_CSV("la tu nique tes mor ya zobbi");

    return 0;
}