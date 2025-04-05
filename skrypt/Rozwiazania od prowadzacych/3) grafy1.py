from typing import List

# Pomocnicza definicja podpowiedzi typu reprezentującego etykietę
# wierzchołka (liczba 1..n).
VertexID = int

# Pomocnicza definicja podpowiedzi typu reprezentującego listę sąsiedztwa.
AdjList = List[List[VertexID]]


def adjmat_to_adjlist(adjmat: List[List[int]]) -> AdjList:
    """Zamiana reprezentacji macierzowej grafu bez wag na listę sąsiedztwa.

    :param adjmat: macierz sąsiedztwa o wymiarach NxN
    :return: lista sąsiedztwa
    """
    adjlist = []
    for row in adjmat:
        adjlist_entry = []
        # Parametr słownikowy `start` określa od jakiej wartości mają zaczynać
        # się indeksy zwracane przez enumerate().
        for (end_vertex_id, n_edges) in enumerate(row, start=1):
            adjlist_entry.extend([end_vertex_id] * n_edges)
        adjlist.append(adjlist_entry)
    return adjlist


# Zwróć uwagę, że domyślna wartość parametru `visited_ids` musi być typu
# niemutowalnego! (Dlatego NIE zastosowano `[]`, tylko "hak" z użyciem `None`).
def dfs(adjlist: AdjList, start_vertex_id: VertexID,
        visited_ids: List[VertexID] = None) -> List[VertexID]:
    """Przeszukaj graf w głąb (rekurencyjnie).

    :param adjlist: lista sąsiedztwa
    :param start_vertex_id: etykieta wierzchołka, od którego zaczynamy przeszukiwanie
    :param visited_ids: lista zawierająca etykiety odwiedzonych wierzchołków
    :return: lista zawierające etykiety wierzchołków w kolejności odwiedzenia
    """
    if visited_ids is None:
        visited_ids = []
    visited_ids.append(start_vertex_id)
    for vertex in adjlist[start_vertex_id - 1]:
        if vertex not in visited_ids:
            dfs(adjlist, vertex, visited_ids)
    return visited_ids


# def dfs_iter(adjlist: AdjList, start_vertex_id: VertexID) -> List[VertexID]:
#     visited_ids = []
#     queue = [start_vertex_id]
#     while queue:
#         v_id = queue.pop(0)
#         if v_id not in visited_ids:
#             visited_ids.append(v_id)
#             queue = [v for v in adjlist[v_id - 1] if v not in visited_ids] + queue
#     return visited_ids


# Zwróć uwagę, że domyślna wartość parametru `visited_ids` musi być typu
# niemutowalnego! (Dlatego NIE zastosowano `[]`, tylko "hak" z użyciem `None`).
def is_cyclic_dfs(adjlist: AdjList, start_vertex_id: VertexID,
                  visited_ids: List[VertexID] = None) -> bool:
    """Przeszukaj graf w głąb (rekurencyjnie) i sprawdź, czy występuje cykl.

    Z cyklem mamy do czynienia, gdy próbujemy odwiedzić wierzchołek już
    odwiedzony w ramach danej gałęzi drzewa rekursji (gałęzie "równoległe" nie
    mają wpływu na znajdowanie cyklu, gdyż mamy do czynienia z grafem skierowanym).

    :param adjlist: lista sąsiedztwa
    :param start_vertex_id: etykieta wierzchołka, od którego zaczynamy przeszukiwanie
    :param visited_ids: lista zawierająca etykiety odwiedzonych wierzchołków
    :return: True, jeśli w grafie występuje cykl, inaczej False
    """
    if visited_ids is None:
        visited_ids = []
    visited_ids.append(start_vertex_id)
    for vertex_id in adjlist[start_vertex_id - 1]:
        # Zwróć uwagę, że lista odwiedzonych wierzchołków jest kopiowana!
        # Dzięki temu gałęzie "równoległe" nie mają wpływu na znajdowanie cyklu.
        if (vertex_id in visited_ids) \
                or is_cyclic_dfs(adjlist, vertex_id, visited_ids[:]):
            return True
    return False


def is_acyclic(adjlist: AdjList) -> bool:
    """Sprawdź, czy graf jest acykliczny.

    Funkcja korzysta ze zmodyfikowanego algorytmu DFS w wersji rekurencyjnej.

    Możemy powiedzić "graf skierowany G jest acykliczny" dopiero wówczas, gdy
    dokonaliśmy przeszukiwania G zaczynając z każdego wierzchołka G i podczas
    żadnego z tych przeszukiwań nie natrafiliśmy na cykl.

    :param adjlist: lista sąsiedztwa
    :return: wartość logiczna określająca, czy graf jest acykliczny
    """

    for start_vertex_id in range(1, len(adjlist)):
        if is_cyclic_dfs(adjlist, start_vertex_id, None):
            return False
    return True

A={1: [2, 3], 3: [4]}
print(is_acyclic(A))