/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void swap(int arr[],int a,int b){
    int temp=arr[b];
    arr[b]=arr[a];
    arr[a]=temp;
}
int partition(int arr[],int low,int high){
    int randomindex=low+rand()%(high-low+1);
    swap(arr,randomindex,high);
    int pivot=arr[high];
    int i=low-1;
    for (int j=low;j<high;j++){
        if (arr[j]<=pivot){
            i++;
            swap(arr,i,j);
            
        }
    }
    swap(arr,i+1,high);
    return i+1;
}

void quicksort(int arr[],int low,int high){
    if (low<high){
        int pi=partition(arr,low,high);
        quicksort(arr,low,pi-1);
        quicksort(arr,pi+1,high);
    }
}
int main()
{
    srand(time(0));
    int arr[10]={1,5,2,7,8,2,9,0,15,3};
    quicksort(arr,0,9);
    for (int i=0;i<10;i++){
        cout<<arr[i]<<" ";
    }
    
    return 0;
}