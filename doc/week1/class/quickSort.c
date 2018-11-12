#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void exch(int arr[],int l,int r){
  int temp;
  temp = arr[l];
  arr[l] = arr[r];
  arr[r] = temp;
  return;
}

void swap(int *a,int *b){
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
  return;
}

void quickSort(int arr[],int l,int r){
  int pivot, i, j;
  if(l<r){
    i = l; j = r;
    pivot = arr[l];

    do{
      do i++; while(arr[i]<pivot);
      do j--; while(arr[j]>pivot);
      if(i<j) swap(&arr[i],&arr[j]);
    }while(i<j);
    swap(&arr[l],&arr[j]);
    quickSort(arr,l,j-1);
    quickSort(arr,j+1,r);
  }
}

void quickSort3Par(int arr[],int l,int r){
  
}
