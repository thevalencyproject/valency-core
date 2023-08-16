/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

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