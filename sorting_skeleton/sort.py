# Michal Sciubisz, 406285

from typing import List, Tuple

def quicksort(array: List[int]):

    def quicksort_inplace(array: [int], start: int, stop: int):
        pivot = int((start+stop)/2)
        pivot_value = array[pivot]
        i = start
        j = stop
        while i < j:
            while array[i] < pivot_value:
                i += 1
            while array[j] > pivot_value:
                j -= 1
            if i <= j:
                array[i], array[j] = array[j], array[i]
                i += 1
                j -= 1

        if start < j:
            quicksort_inplace(array, start, j)
        if i < stop:
            quicksort_inplace(array, i, stop)
        return array

    sorted_array = array[:]

    sorted_array = quicksort_inplace(sorted_array, 0, len(array) - 1)

    return sorted_array




def bubblesort(list: [int]):
    n = len(list)
    nmr_comparisons = 0
    lst2 = list[:]
    while n > 1:
        lst_check = lst2[:]
        for i in range(1, n):
            if lst2[i-1] > lst2[i]:
                lst2[i-1], lst2[i] = lst2[i], lst2[i-1]
            nmr_comparisons += 1
        if lst_check == lst2:
            return lst2, nmr_comparisons
        n -= 1
    return lst2, nmr_comparisons
