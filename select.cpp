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
void swap(int arr[],int a ,int b ){
    int temp=arr[b];
    arr[b]=arr[a];
    arr[a]=temp;
}

int partition(int arr[],int low,int high){
    int ri=low+rand()%(high-low+1);
    swap(arr,ri,high);
    int pivot=arr[high];
    int i=low-1;
    for (int j=low;j<high;j++){
        if (arr[j]<pivot){
            i++;
            swap(arr,i,j);
        }
    }
    swap(arr,i+1,high);
    return i+1;
}
int rand_select(int arr[],int low,int high,int k){
    if (low==high){
        return arr[low];
    }
    int pivotindex=partition(arr,low,high);
    int rank=pivotindex-low+1;
    if (k==rank){
        return arr[pivotindex];
    }
    else if(k<rank){
        return rand_select(arr,low,pivotindex-1,k);
    }
    else{
        return rand_select(arr,pivotindex+1,high,k-rank);
    }
}
int main()
{
    srand(time(0));
    int arr[10]={3,4,7,2,7,4,10,6,8,3};
    cout<<rand_select(arr,0,9,2);
    return 0;
}