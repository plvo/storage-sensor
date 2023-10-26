#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// config ? tout ce qui va changer en fct du scénario
int TEMP_CHAMBRE = -40;
int TIMER = 600;

#define MAXCHAR 1000

int main()
{

    FILE *fp;
    char str[MAXCHAR];
    char *filename = "config.csv";

    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Pas oujvert");
        return 1;
    }

    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);

    fclose(fp);

    return 0;
}