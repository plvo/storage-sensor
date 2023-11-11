#include <stdio.h>
#include <string.h>

int main() {
    FILE * fp;
    fp = fopen("config.csv", "r");
    if (fp == NULL) {
        printf("Erreur fopen\n");
        return 1;
    }

    char str[1000];
    // EOF => END OF FILE
    int i = 0;
    char ligne[1000];
    while (fgets(str,1000,fp) != NULL){
        if (i==5){
            strcpy(ligne, str);
            printf("%s\n", str);
        }
        i++;
    }

    printf("%s \n", ligne);
    char *token = strtok(ligne, ","); // Initialisation du délimiteur
    while (token != NULL) {
        printf("%s\n", token); // Affichez chaque élément
        token = strtok(NULL, ","); // Passez au prochain élément
    }

    return 0;
}