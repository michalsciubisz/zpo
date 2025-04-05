# -*- coding: utf-8 -*-
"""
Created on Sat Oct 27 13:43:52 2018

@author: XTreme.ws
"""

from typing import List
from timeit import timeit
import random
 
 
def quicksort(I: List[int], start_inx: int, stop_inx: int) -> None:
    """Posortuj zakres tablicy metodą quicksort.
 
    :param I: tablica do posortowania
    :param start_inx: indeks początku zakresu do posortowania (włącznie)
    :param stop_inx: indeks końca zakresu do posortowania (włącznie)
    """
    i = start_inx
    j = stop_inx
    # Jako element środkowy wybierz element leżący na środku zakresu.
    # (Operator `a // b` zwraca część całkowitą z dzielenia a przez b.)
    pivot_inx = (stop_inx + start_inx) // 2
 
    while i < j:
        while I[i] < I[pivot_inx]:
            i += 1
        while I[j] > I[pivot_inx]:
            j -= 1
 
        if i <= j:
            I[i], I[j] = I[j], I[i]
            i += 1
            j -= 1
 
    if start_inx < j:
        quicksort(I, start_inx, j)
    if i < stop_inx:
        quicksort(I, i, stop_inx)
 
 
def bubble_sort(I: List[int]) -> None:
    """Posortuj tablicę metodą bąbelkową.
 
    :param I: tablica do posortowania
    """
    n = len(I)
    # Flaga określająca, czy podczas przeglądania listy dokonaliśmy zamiany.
    was_swap = True
 
    while (n > 1) and was_swap:
        # Na początku każdego cyklu należy "wyzerować" flagę zamiany.
        was_swap = False
        for i in range(1, n):
            if I[i-1] > I[i]:
                I[i-1], I[i] = I[i], I[i-1]
                was_swap = True
        n -= 1
 
 
N_ELEMENTS = 9
test_lists = {
    'sorted_list': list(range(N_ELEMENTS)),
    'reversed_list': list(range(N_ELEMENTS))[::-1],
    'unsorted_list': random.sample(range(N_ELEMENTS), N_ELEMENTS),
    'uniform_list': [1] * N_ELEMENTS
}
 
N_REPETITIONS = 5
print('\n== Average execution times for N={n} repetitions ==\n'.format(n=N_REPETITIONS))
for test_list_id in test_lists:
    for algorithm_id in ['quicksort', 'bubble_sort']:
        # Dokonaj wstępnej alokacji w celu zwiększenia szybkości działania.
        timings = [None] * N_REPETITIONS
        for repetition_inx in range(N_REPETITIONS):
            # Mierz czas wykonania funkcji na kopii (!) listy testowej -
            # w przeciwnym razie tylko pierwszy pomiar będzie się odbywał dla
            # listy z elementami w oryginalnej kolejności, a następne - już
            # dla posortowanej listy!
            test_list_copy = test_lists[test_list_id].copy()
 
            if algorithm_id == 'quicksort':
                timed_command = '{func}(test_list_copy, 0, N_ELEMENTS - 1)'.format(func=algorithm_id)
            else:
                timed_command = '{func}(test_list_copy)'.format(func=algorithm_id)
            exec_time = timeit(timed_command, number=1, globals=globals())
            timings[repetition_inx] = exec_time
        print('{test_list_id:>15} ({algorithm_id:>13}) :  {avg_timing:.6f}'.format(
            test_list_id=test_list_id, algorithm_id=algorithm_id,
            avg_timing=sum(timings) / len(timings)
        ))
    print()