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
char duree_s;

void startMeasuringTime() {
    ti = clock();
}

void stopMeasuringTime() {
    tf = clock() - ti;
    duree_ms = tf / (double) CLOCKS_PER_SEC * 1000;
}

void showElapsedTime() {
    sprintf(&duree_s, "%f\n", duree_ms);
//    printf("%s\n", &duree_s);
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
    int heapArray1 = heap.array[ind1];
    int heapArray2 = heap.array[ind2];
    permut(&heap.array[ind1], &heap.array[ind2]);
}

//*************** Exercise 1 ******************

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int *array, int n, int k) {
    // 0  1  2  3 4 5 6
    // 30 23 12 9 1 2 50

    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
}

//*************** Exercise 2 ******************


int left(int i) {
    return (2 * i) + 1;
}

int right(int i) {
    return (2 * i) + 2;
}

int percolate_down(Heap heap, int i, int numSwaps) {
    // i : index of node
    int l = left(i);
    int r = right(i);
    int m; //max
    if (l < heap.size && heap.array[i] < heap.array[l]) {
        m = l;
    } else {
        m = i;
    }
    if (r < heap.size && heap.array[m] < heap.array[r]) {
        m = r;
    }
    if (m != i) {
        permut_heap(heap, i, m);
        numSwaps++;
        percolate_down(heap, m, numSwaps);
    }
    return numSwaps;
}

int percolate_down_min(Heap heap, int i, int numSwaps) {
    // i : index of node
    int l = left(i);
    int r = right(i);
    int m; //max
    if (l < heap.size && heap.array[i] > heap.array[l]) {
        m = l;
    } else {
        m = i;
    }
    if (r < heap.size && heap.array[m] >heap.array[r]) {
        m = r;
    }
    if (m != i) {
        permut_heap(heap, i, m);
        numSwaps++;
        percolate_down(heap, m, numSwaps);
    }
    return numSwaps;
}

int build_heap(Heap heap) {
    int numSwaps = 0;
    heap.size = heap.length;
    for (int i = heap.size / 2; i > -1; i--) {
        numSwaps = percolate_down(heap, i, numSwaps);
    }
    return numSwaps;
}


int parent(int i) {
    return i / 2;
}

int percolate_up(Heap heap, int i, int numSwaps) {
    // i = index
    int j = parent(i);
    while (j > -1 && heap.array[j] < heap.array[i]) {
        permut_heap(heap, i, j);
        numSwaps++;
        i = j;
        j = parent(i);
    }
    return numSwaps;

}

int add(Heap *heap, int element) {
    if (heap->size < heap->length) {
        int numSwaps = 0;
        heap->size++;
        heap->array[heap->size - 1] = element;
        numSwaps = percolate_up(*heap, heap->size - 1, numSwaps);
        return numSwaps;
    } else {
        printf("tree is full");
        return 0;
    }
}


int remove_max(Heap *heap) {
    int numSwaps = 0;
    int m;
    if (heap->size > 0) {
        m = heap->array[0];
        heap->array[0] = heap->array[heap->size - 1];
        heap->size--;
        percolate_down(*heap, 0, numSwaps);
    } else {
        printf("tree is empty");
    }
    return m;
}

void remove_k(Heap *heap, int k) {
    for (int i = 0; i < k; i++) {
        printf("%d ", remove_max(heap));
    }
    printf("\n");
}

//*************** Exercise 3 ******************

int remove_bis(Heap *heap) {
    int m = 0;
    //heap, start index, end index
    permut_heap(*heap, 0, heap->size - 1);
    heap->size--;

    percolate_down(*heap, 0, m);
    return 0;
    /*
     
    int numSwaps = 0;
    int m;
    if (heap->size > 0) {
        m = heap->array[0];
        heap->array[0] = heap->array[heap->size-1];
        heap->size--;
        percolate_down(*heap, 0, numSwaps);
    }
    else {
        printf("tree is empty");
    }
    */
}
int remove_bis_min(Heap *heap) {
    int m = 0;
    //heap, start index, end index
    permut_heap(*heap, 0, heap->size - 1);
    heap->size--;

    percolate_down_min(*heap, 0, m);
    return 0;
    /*

    int numSwaps = 0;
    int m;
    if (heap->size > 0) {
        m = heap->array[0];
        heap->array[0] = heap->array[heap->size-1];
        heap->size--;
        percolate_down(*heap, 0, numSwaps);
    }
    else {
        printf("tree is empty");
    }
    */
}

Heap heap_sort(int *array, int length) {
    Heap heap = {array, length, length};
    build_heap(heap);
    for (int i = 0; i < length; i++) {
        remove_bis(&heap);
    }
    return heap;
}

Heap heap_sort_bis(int *array, int length, int k) {
    Heap heap = {array, length, length};
    build_heap(heap);
    for (int i = 0; i < k; i++) {
        remove_bis(&heap);
    }
    return heap;
}
Heap heap_sort_bis_min(int *array, int length, int k) {
    Heap heap = {array, length, length};
    build_heap(heap);
    for (int i = 0; i < k; i++) {
        remove_bis_min(&heap);
    }
    return heap;
}

/*
 * my shitty try at quick sort
 *
 *
int partition (int * array, int firstIndex, int lastIndex) {
    int piv = array[lastIndex];
    
    int i = firstIndex - 1;
    for (int j = firstIndex; j <= lastIndex - 1; j++) {
        if (array[j] < piv) {
            i++;
            permut(&array[i], &array[j]);
        }
    }
    permut(&array[i + 1], &array[lastIndex]);
    return i + 1;
    
}

void quick_sort(int * array, int firstIndex, int lastIndex) {
    
    if ( firstIndex < lastIndex) {
        int piv = partition(array, firstIndex, lastIndex);

        quick_sort(array, firstIndex, piv-1);
        quick_sort(array, piv +1, lastIndex);
    }
    
}
*/

/*
 * geeks4geeks try at quick sort
 */

int partition(int arr[], int low, int high) {
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
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
void quickSort(int arr[], int low, int high) {
    if (low < high) {
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
    int n, k;
    FILE *f_in;

    if (argc > 1)
        f_in = fopen(argv[1], "r");
    else
        f_in = stdin;

    /* read the data from the file given in arg or from stdin */
    read_data(f_in, &data, &n, &k);
    fclose(f_in);

    int *data_bis;
    data_bis = malloc(sizeof(int) * n);

//    printf("Initiales data:\n");
//    print_array(data, n);

    ////////////////////////////
    /* ***** Exercise 1 ***** */
    ////////////////////////////

    memcpy(data_bis, data, n * sizeof(int));
    startMeasuringTime();
    bubble_sort(data_bis, n, k);
    stopMeasuringTime();
    showElapsedTime();

    printf("[I.]\nTime to sort the whole array by bubblesort : %f\n", atof(&duree_s));


    ////////////////////////////
    /* ***** Exercise 2 ***** */
    ////////////////////////////

    //
    // creating a heap by the buildheap method
    memcpy(data_bis, data, n * sizeof(int));
    Heap heap = {data_bis, n, n};
//    print_array(data_bis, n);
    startMeasuringTime();
//    print_array(heap.array, heap.length);
//    printf("now we buildheap");
    int numSwapsBuild = build_heap(heap);
    stopMeasuringTime();
    showElapsedTime();

    printf("##########test##########\nq2 : %d\n##########test##########\n\n\n", heap.array[66]);
    float buildtime = atof(&duree_s);

    printf("\n[II.2]\nThe %d greatest elements of the array, sorted by buildHeap, are : \n", k);
    print_array(heap.array, k);


    //
    // creating a heap by the add method
    memcpy(data_bis, data, n * sizeof(int));
    startMeasuringTime();
    int array[n];
    Heap heap2 = {array, n, 0};
    int numSwapsAdd = 0;
    for (int i = 0; i < n; i++) {
        numSwapsAdd += add(&heap2, data_bis[i]);
    }
    stopMeasuringTime();
    showElapsedTime();
    float addtime = atof(&duree_s);
    printf("##########test##########\nq3: %d\n##########test##########\n", heap2.array[66]);

    // réponse aux questions



    printf("\n[II.4]\nThe %d greatest elements of the array, sorted by add "
           "and extracted with remove, are :\n", k);
    remove_k(&heap2, 67);

    printf("\n[II.5] \nadd_heap time :    %f\nbuildheap time :   %f\n", addtime, buildtime);

    printf("\n[II.6]\n# of swaps by buildheap: %d\n"
           "# of swaps by ADD:       %d\n", numSwapsBuild, numSwapsAdd);

    ////////////////////////////
    /* ***** Exercise 3 ***** */
    ////////////////////////////


    int firstIndex = 0;
    int lastIndex = n - 1;

    //quicksort the full dataset once
    memcpy(data_bis, data, n * sizeof(int));
    startMeasuringTime();
    quickSort(data_bis, firstIndex, lastIndex);
    stopMeasuringTime();
    showElapsedTime();
    float quicktime = atof(&duree_s);
    printf("q1 : %d\n", data_bis[n - 67]);

    int step = -1;
    for (int i = 0; i < n; i++) {
        // détrie le tableau data
        memcpy(data_bis, data, n * sizeof(int));

        // bubblesort le tableau détrié
        startMeasuringTime();
        bubble_sort(data_bis, n, i);
        stopMeasuringTime();
        showElapsedTime();
        // detecte le step où bubblesort devient plus lent que quicksort
        if (atof(&duree_s) > quicktime) {
            step = i;
            break;
        }
    }

    memcpy(data_bis, data, n * sizeof(int));
//    startMeasuringTime();
    Heap heap3 = heap_sort(data_bis, n);

    int *data_ter;
    data_ter = malloc(sizeof(int) * n);
    memcpy(data_ter, data, n * sizeof(int));
    Heap heap4 = heap_sort_bis(data_ter, n, k);

    int *data_quad;
    data_quad = malloc(sizeof(int) * n);
    memcpy(data_quad, data, n * sizeof(int));
    Heap heap5 = heap_sort_bis_min(data_quad, n, k);
//    stopMeasuringTime();
//    showElapsedTime();
    float heaptime = atof(&duree_s);
    printf("##########test##########\n%d\n", heap3.array[66]);
    printf("%d\n", heap4.array[66]);
    printf("%d\n\n", heap5.array[66]);
    printf("%d\n", heap3.array[n-67]);
    printf("%d\n", heap4.array[n-67]);
    printf("%d\n##########test##########\n", heap5.array[n-67]);

    // reponses aux questions
    /* 3.2 */
//    print_array(heap3.array, heap3.length);
    printf("\n[III.2] \nThe %d greatest elements of the array, given by heapsort, are :\n", k);
//    print_array(&heap3.array[n - k], k);

    /* 3.4 */
    printf("\n[III.4] \npartial bubblesort becomes slower than full quicksort in %d steps.\n", step);

    /* 3.5 */
    printf("\n[III.5] \nquicksort time :    %f\nheapsort time :     %f\n", quicktime, heaptime);

    /* end of the program*/
    free(data);
    free(data_bis);
    return 0;
}