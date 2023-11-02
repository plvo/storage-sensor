# include <stdio.h>
# include <stdlib.h>
# include <string.h>


int main(){
    FILE *fp;
    char str[1000];
    char *filename = "config.csv";

    int BADGE_ON, ENTER_DOOR_OPEN, ENTER_DOOR_CLOSE, TIMER_ON, TEMP_START, TIMER_CHECK, EXIT_DOOR_OPEN, EXIT_DOOR_CLOSE;

    fp = fopen(filename, "r");
    
    if (fp == NULL){
        printf("Pas ouvert");
        return 1;
    }

    while (fgets(str, 1000, fp) != NULL)
        printf("%s", str);

    fclose(fp);

    return 0;
}