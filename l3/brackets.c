#include <stdio.h>

int main(){
    FILE *input = fopen("brackets.c", "r");
    //if(!input)printf("ne otkril input");
    FILE *output = fopen("out.txt", "rw");
    //if(!output)printf("e otkril output");
    char cur;
    int counter = 0;
        while(!feof(input)){
            fscanf(input, "%c", &cur);
            if(cur == '{') counter++;
            if(cur == '}') counter--;
        }
    if(!cur){
        fprintf(output, "brackets match");
        printf("brackets match");
    } else {
        fprintf(output, "brackets dont match");
        printf("brackets match");
    }
    return 0;
}