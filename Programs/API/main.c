#include<stdio.h>
#include "sum.c"
#include "multiply.c"

int main(){
    int a,b;
    printf("Enter 2 numbers: ");
    scanf("%d %d",&a,&b);
    printf("Sum: %d\n",sum(a,b));
    printf("Product: %d",prod(a,b));
    return 0;
}