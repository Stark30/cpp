#include <stdio.h>

int array[] = {0,1};

const int getxy(int a) {
    return (array[0]+array[1]) - a;
}

int main() {
    int x,y;
    printf("Input value: ");
    scanf("%d %d",&x,&y);
    array[0]=x;
    array[1]=y;
    printf("%d\n", getxy(x)); 
    printf("%d\n", getxy(y)); 
    return 0;
}
