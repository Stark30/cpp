#include<stdio.h>
#include "sum.h"
#include "multiply.h"
int sum(int a,int b);

int main(){
    int a,b;
    printf("Enter 2 numbers: ");
    scanf("%d %d",&a,&b);
    printf("Sum: %d\n",sum(a,b));
    printf("Product: %d",prod(a,b));
    return 0;
}
