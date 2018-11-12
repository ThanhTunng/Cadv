
void swap(int *a,int *b){
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
  return;
}

void exch(int a[],int l,int r){
  int temp;
  temp = a[l];
  a[l] = a[r];
  a[r] = temp;
  return;
}

void quickSort2w(int arr[],int l,int r){
  int pivot,i,j;
  if(l>=r) return;
  i=l;j=r+1;
  pivot = arr[l];

  do{
    do i++; while(arr[i]>pivot);
    do j--; while(arr[j]<pivot);
    if(i<j) swap(&arr[i],&arr[j]);
  }while(i<j);
  swap(&arr[l],&arr[j]);
  sort2w(arr,l,j-1);
  sort2w(arr,j+1,r);
}

void quickSort3w(int a[],int l,int r){
  if(r<=l) return;
  int i=l-1, j=r;
  int p=l-1, q=r;

  while(1){
    while(a[++i]>a[r]);
    while(a[r]>a[--j]){
      if(j==l) break;
    }

    if(i>=j) break;
    exch(a,i,j);
    if(a[i]==a[r]) exch(a,++p,i);
    if(a[j]==a[r]) exch(a,--q,j);
  }

  exch(a,i,r);
  j=i-1;
  i=i+1;
  for(int k=l;k<=p;k++) exch(a,k,j--);
  for(int k=r-1;k>=q;k--) exch(a,k,i++);
  sort3w(a,l,j);
  sort3w(a,i,r);
}
