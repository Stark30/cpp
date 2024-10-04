#include<stdio.h>

int sum(int *arr,int size){
    int tot = 0;
    for (int i=0;i<size;i++) 
        tot+= (*(arr + i)); 
        
    return tot;
}

int main(){
    int n;
    printf("Enter num of elements: ");
    scanf("%d",&n);
    int arr[n];

    printf("Enter the elements of the arr: ");
    for (int i=0;i<n;i++) {
        scanf("%d", &arr[i]);
    }
    printf("Sum: %d\n", sum(arr, n));

    return 0;
}