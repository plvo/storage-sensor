#include <stdio.h>
#include <stdlib.h>

int main(){
    float nb1;
    float nb2;
    printf("\nHello\n\n");
    printf("We will make some additions\n");
    printf("Give a number:\t");
    scanf("%f",&nb1);
    printf("Give a second number: \t");
    scanf("%f",&nb2);
    float som = nb1 + nb2;
    printf("The sum of %f and %f is equal to %f", nb1, nb2, som);
    return 0;
}