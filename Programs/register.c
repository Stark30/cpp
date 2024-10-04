#include<stdio.h>

/*Register is 8 bit in size.
Set third bit of that register.
Clear fourth bit of that register.
Test the fifth bit of that register.*/
int main(){
    char reg;
    printf("Enter: ");
    scanf("%c",&reg);

    reg = reg | (1<<2);
    reg = reg & (1<<3);

    if (reg & (1<<2)==1){
        printf("Bit Set");
    }
    else{
        printf("Bit not set");
    }
}