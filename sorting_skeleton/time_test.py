import random, sort
import timeit

#Utworzenie list z zadania 3-go

#posortowana lista
lst_sorted = [x for x in range(0, 1001)]

#odwrotnie posortowana lista
lst_reverse_sorted = [i for i in reversed(lst_sorted)]

#lista składajaca sie z elementow o rownych wartosciach
lst_single_value = [5 for x in range(0, 1001)]

#lista skladajaca sie z losowych wartosci
lst_random_values = [random.randint(1, 100) for x in range(0, 1001)]

#sprawdzanie ktora funkcja ma szybszy czas kompilacji w przypadku kazdej z przygotowanych list


#sorted_lst

time1_bubble = timeit.timeit('sort.bubblesort(lst_sorted)', number=1000, globals=globals())
time1_quicksort = timeit.timeit('sort.quicksort(lst_sorted)', number=1000, globals=globals())

print(time1_bubble/1000)
print(time1_quicksort/1000)

#czyli funkcja bubblesort w przypadku posortowanej listy dziala szybciej


#reverse_sorted_lst

time2_bubble = timeit.timeit('sort.bubblesort(lst_reverse_sorted)', number=1000, globals=globals())
time2_quicksort = timeit.timeit('sort.quicksort(lst_reverse_sorted)', number=1000, globals=globals())

print(time2_bubble/1000)
print(time2_quicksort/1000)

#w tym przypadku funkcj quicksort jest zdecydowanie bardziej optymalna w przypadku listy odwroconej


#single_value_lst

time3_bubble = timeit.timeit('sort.bubblesort(lst_single_value)', number=1000, globals=globals())
time3_quicksort = timeit.timeit('sort.quicksort(lst_single_value)', number=1000, globals=globals())

print(time3_bubble/1000)
print(time3_quicksort/1000)

#w przypadku listy z jedna wartoscia bubblesort radzi sobie na podobnym poziomie co w przypadku listy uporządkowanej


#random_value_lst

time4_bubble = timeit.timeit('sort.bubblesort(lst_random_values)', number=1000, globals=globals())
time4_quicksort = timeit.timeit('sort.quicksort(lst_random_values)', number=1000, globals=globals())

print(time4_bubble/1000)
print(time4_quicksort/1000)

#przy liscie z losowymi liczbami zdecydowanie wydajniejszy jest quicksort, dziala bardziej optymalnie dzielac liste na mniejsze fragmenty