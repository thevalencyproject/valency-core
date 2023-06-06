#ifndef QUICKSORT_H
#define QUICKSORT_H


/* Quicksort works with an array of any numerical type - i.e. int, float, double */
struct QuickSort {
    template<typename T>
    void swap(T* a, T* b);
    template<typename T>
    int partition(T* array, int left, int pivot);

    template<typename T>
    void sort(T* array, int left, int pivot);
};

#endif