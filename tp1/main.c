#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


//*************** Binairy heap structure ******************

typedef struct Heap {
    int *array;
    int length; // max size
    int size;
} Heap;



//*************** Given Functions ******************

//**** Function for the execution time ****
clock_t ti, tf;
double duree_ms;

void startMeasuringTime() {
    ti = clock();
}

void stopMeasuringTime() {
    tf = clock() - ti;
    duree_ms = tf / (double) CLOCKS_PER_SEC * 1000;
}

void showElapsedTime() {
    printf("duree (ms): ~%f\n", duree_ms);
}

//**** Read data ****
void read_data(FILE *datain, int **dataout, int *n, int *k) {
    int *data;

    fscanf(datain, "%d", n);
    fscanf(datain, "%d", k);
    *dataout = (int *) malloc((*n) * sizeof(int));
    data = *dataout;

    for (int i = 0; i < *n; ++i, ++data)
        fscanf(datain, "%d", data);
}


//**** Show data ****
void print_array(int *array, int length) {
    for (int i = 0; i < length; ++i)
        printf("%d ", array[i]);
    printf("\n");
}

//**** Permutation ****
void permut(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//**** Permutation between two indices of a binary heap ****
void permut_heap(Heap heap, int ind1, int ind2) {
    permut(&heap.array[ind1], &heap.array[ind2]);
}


//*************** Exercise 1 ******************


void bubble_sort(int *array, int n, int k) {
    int swapped;
    do {
        swapped = 0;
        for (int i = 1; i < n; i++) {
            if (array[i - 1] > array[i]) {
                permut(&array[i - 1], &array[i]);
                swapped = 1;
            }
        }
    } while (swapped);
//    printf("The %dth greater elements of the array are :\n", k);
//    print_array(&array[n - k], k);
}

//*************** Exercise 2 ******************

int parent(int i) {
    return i / 2;
}

int left(int i) {
    return 2 * i;
}

int right(int i) {
    return 2 * i + 1;
}

int percolate_down(Heap heap, int i, int swap) {
    int l = left(i);
    int r = right(i);
    int m;
    if (l <= heap.size && heap.array[i] < heap.array[l]) {
        m = l;
    } else m = i;
    if (r < heap.size && heap.array[m] < heap.array[r])
        m = r;
    if (m != i) {
        permut_heap(heap, i, m);
        swap++;
        percolate_down(heap, m, swap);
    }
    return swap;
}

int build_heap(Heap heap) {
    heap.size = heap.length;
    int swap = 0;
    for (int i = heap.size / 2; i > -1; i--) {
        swap = percolate_down(heap, i, swap);
    }
    return swap;
}

int percolate_up(Heap heap, int i, int swap) {
    int j = parent(i);
    while (j > -1 && (heap.array[j] < heap.array[i])) {
        permut_heap(heap, i, j);
        swap++;
        i = j;
        j = parent(i);
    }
    return swap;
}

__unused int add(Heap *heap, int element) {
    if (heap->size < heap->length) {
        int swap = 0;
        heap->size++;
        heap->array[heap->size - 1] = element;
        return percolate_up(*heap, heap->size - 1, swap);
    } else printf("Tree is full");
    return 0;
}


int remove_max(Heap *heap) {
    int swap = 0;
    int m = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    percolate_down(*heap, 0, swap);
    return m;
}

void remove_k(Heap *heap, int k) {
    printf("The %dth greatest elements of the heap are :\n", k);
    for (int i = 0; i < k; i++) {
        printf("%d ", remove_max(heap));
    }
    printf("\n");
}




//*************** Exercise 3 ******************

void remove_bis(Heap *heap) {
    int swap = 0;
    permut_heap(*heap, 0, heap->size);
    percolate_down(*heap,0,swap);
    heap->size--;
}

Heap heap_sort(int *array, int length) {
    Heap heap = {array, length, length};
    build_heap(heap);
//    printf("before \n");
//    print_array(heap.array,heap.size);
    for (int i=0;i<heap.length;i++){
        remove_bis(&heap);
    }
//    printf("after\n");
//    print_array(heap.array,heap.length);
    return heap;
}

// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}



/* Main Program*/

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Depending on the exercise to be done, modifies the main program
// (each sort must be performed on the initial data)
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int main(int argc, char **argv) {
    int *data;

    const int n, k;
    FILE *f_in;

    if (argc > 1)
        f_in = fopen(argv[1], "r");
    else
        f_in = stdin;

    /* read the data from the file given in arg or from stdin */
    read_data(f_in, &data, &n, &k);
    fclose(f_in);


    Heap heap = {data, n, n};
//
//    printf("Initiales data:\n");
//    print_array(data, n);


//    // ***** Exercise 1 *****
//    startMeasuringTime();
//    bubble_sort(data, n, k);
////    print_array(data, n);
//
//    stopMeasuringTime();
//
//    showElapsedTime();


////     ***** Exercise 2 *****
//
//    startMeasuringTime();
//    int array[n];
//    int swapMain = 0;
//    Heap heap2 = {array, n, 0};
//    for (int i = 0; i < heap2.length; i++) {
//        swapMain += add(&heap2, data[i]);
//    }
////    print_array(heap2.array, heap2.size);
//    printf("swap nb with add: %d\n", swapMain);
//    stopMeasuringTime();
//    showElapsedTime();
//
//
//    startMeasuringTime();
//    printf("swap nb with buildHeap: %d\n", build_heap(heap));
//    stopMeasuringTime();
//    showElapsedTime();
////    remove_k(&heap2, k);


//    // ***** Exercise 3 *****
    Heap heap3 = heap_sort(data, n);
    print_array(&heap3.array[n-k],k);

//
//    int firstIndex, lastIndex;
//
//    quick_sort(data, firstIndex, lastIndex);


    // ******** Show the execution time ********
//
//    stopMeasuringTime();
//
//    showElapsedTime();

    /* end of the program*/
    free(data);
    return 0;
}
