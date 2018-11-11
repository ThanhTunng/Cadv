void inSort(int list[], int n)
{
  int i, j;
  int next;
  for (i=1; i<n; i++) {
    next= list[i];
    for (j=i-1;j>=0 && next< list[j];j--)
      list[j+1] = list[j];
    list[j+1] = next;
  }
}
void secSort(int arr[],int n){
  for(int i = 0;i<n;i++){
    int min = i;
    for(int j = i+1;j<n-1;j++){
      if(arr[j] < arr[min]){
	min = j;
      }
      int tmp = arr[i];
      arr[i] = arr[min];
      arr[min] = tmp;
    }
  }
}

void adjust(int list[], int root, int n){
  int child;
  int temp;
  temp=list[root];
  
  child=2*root;
  while (child <= n) {
    if ((child < n) &&(list[child] < list[child+1]))
      child++;
    if (temp > list[child]) break;
    else {
      list[child/2] = list[child];
      child *= 2;
    }
  }
  list[child/2] = temp;
}
void heapSort(int list[], int n){
  int i;
  int temp;
  for (i=n/2; i>0; i--) adjust(list, i, n);
  for (i=n-2; i>0; i--){
    temp = list[1];
    list[1] = list[i+1];
    list[i+1] = temp;
    adjust(list, 1, i);
  }
}

void bubbleSort(int arr[], int n){
  int temp,i,j;
  int check ;
  for(i=0;i<n-1;i++){

    check =0;

    for(j=0;j<n-1-i;j++){

      if(arr[j] > arr[j+1]){

	temp = arr[j];
	arr[j] = arr[j+1];
	arr[j+1] = temp;

	check = 1;
      }
    }
    if(check == 0) break;
  }
  return;
}


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
