#include <stdio.h>

struct stringStruct{
    char a;
    int b;
};

struct stringStructP{
    char a;
    int b;
}__attribute__((packed));


int main(){
    char str[10]={'A',0,0,0,0,'B',0,0,0,0};
    struct stringStruct *struc1=str;
    struct stringStructP *struc2=str;
    printf("a = %c b = %d unpacked\n", struc1->a, struc1->b);
    printf("a = %c b = %d packed\n", struc2->a, struc2->b);
}