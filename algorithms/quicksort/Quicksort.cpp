#include "Quicksort.h"


template<typename T>
void QuickSort::swap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

template<typename T>
int QuickSort::partition(T* array, int left, int pivot) {
    int low = left - 1;     // Create an empty sub-array
    int high = pivot - 1;   // Compare all numbers before the pivot

    for(int i = left; i <= high; i++) {     // Check all elements in the sub-array
        if(array[i] <= array[pivot]) {      // Does this element go into the <= sub-array?
            low++;                          // Move over marker of sub-array
            swap(&array[low], &array[i]);   // Swap the element into position
        }
    }

    swap(&array[low + 1], &array[pivot]);   // Move the pivot into the correct position
    return low + 1;                         // Return the index of the element in the correct place
}

template<typename T>
void QuickSort::sort(T* array, int left, int pivot) {
    if(left < pivot) {                                  // Recursive until there is a single element left
        int new_pivot = partition(array, left, pivot);  // Partition the array into <= and > sub-arrays

        sort(array, left, new_pivot - 1);               // Sort the <= sub-array
        sort(array, new_pivot + 1, pivot);              // Sort he > sub-array
    }
}