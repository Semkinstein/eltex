#include <stdio.h>
#include "interactions.h"
#include <dlfcn.h>

int interface(int addt, int subt, int mult, int divt){
    int index=1;
    if(!addt){
        printf("%d) Addition\n", index);
        index++;
    }
    if(!subt){
        printf("%d) Substraction\n", index);
        index++;
    }
    if(!mult){
        printf("%d) Multiplication\n", index);
        index++;
    }
    if(!divt){
        printf("%d) Division\n", index);
        index++;
    }
    return 0;
}

int main(){
    void *lib = dlopen("libcalc.so", RLTD_LAZY);
    float (*fnm)(float, float), (*fnd)(float, float)
    float (*fns)(float, float), (*fna)(float, float);
    int mult = subt = divt = addt = 1;
    mult = dlerror(fnm = dlsym(lib, "mul"));
    subt = dlerror(fns = dlsym(lib, "sub"));
    divt = dlerror(fnd = dlsym(lib, "div"));
    addt = dlerror(fna = dlsym(lib, "add"));
// 
    int num = 0;
    float arg1, arg2;
    while(num != 5){
        interface(addt, subt, mult, divt);
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