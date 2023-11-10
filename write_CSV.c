#include <stdio.h>

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
int main() {
    write_CSV("la tu met ce que tu veut marquer pelouz");
    write_CSV("la tu nique tes mor ya zobbi");

    return 0;
}