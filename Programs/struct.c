#include<stdio.h>
#include<stdint.h>
//16 bit, 8bit, 32 bit boards 

struct board{
    uint8_t bit8;   
    uint16_t bit16;  
    uint32_t bit32;   
};

int main(){
    struct board b;
    printf("%d\n",&b.bit8);
    printf("%d\n",&b.bit16);
    printf("%d\n",&b.bit32);
}