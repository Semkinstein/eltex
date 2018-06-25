#include <stdio.h>
#include "interactions.h"

int main(){
    int num = 0;
    float arg1, arg2;
    while(num != 5){
        printf("1) Addition\n2) Substraction\n3) Multiplication\n4) Division\n5) Quit\n");
        scanf("%d", &num);
        if(num == 5)break;
        printf("\nInput args\n");
        scanf("%f%f", &arg1, &arg2);
        switch(num){
            case 1:
                printf("%f\n", add(arg1, arg2));
                break;
            case 2:
                printf("%f\n", sub(arg1, arg2));
                break;
            case 3:
                printf("%f\n", mul(arg1, arg2));
                break;
            case 4:
                printf("%f\n", div(arg1, arg2));
                break;
            default:
                break;
        }
    }
    return 0;
}