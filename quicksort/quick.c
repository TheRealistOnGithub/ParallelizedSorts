// Quick sort in C

#include <stdio.h>
#include <time.h>
#include <omp.h>
#define getClock() ((double)clock()/CLOCKS_PER_SEC)
double begin,end;
// function to swap elements
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int partition(int array[], int low, int high) {
  
  // select the rightmost element as pivot
  int pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  #pragma omp parallel for schedule(static,1)
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
    
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);
    
    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);
    
    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}

// function to print array elements
void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}

// main function
int main() {
FILE *myFile;
	myFile = fopen("dataset.txt","r");
	int data[100000];
	int i;
	for (i=0;i<100000;i++){
		
		fscanf(myFile,"%d",&data[i]);
	}
	

    int n = sizeof(data)/sizeof(data[0]);
  
  // perform quicksort on data
  begin = getClock();
  quickSort(data, 0, n - 1);
  end = getClock();
  printf("Sorted array in ascending order: \n");
  printArray(data, n);
  printf("The quicksort took %f seconds to complete\t",end-begin);
}