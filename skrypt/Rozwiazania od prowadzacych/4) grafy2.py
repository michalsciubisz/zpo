from typing import List, Set, Mapping
from collections import namedtuple

VertexID = int
Distance = int
AdjList = List[List[VertexID]]


def neighbors(adjlist: AdjList, start_vertex_id: VertexID,
              max_distance: Distance) -> Set[VertexID]:
    """Znajdź wierzchołki leżące w zadanym promieniu od wierzchołka początkowego.

    :param adjlist: lista sąsiedztwa
    :param start_vertex_id: etykieta wierzchołka, od którego zaczynamy przeszukiwanie
    :param max_distance: maksymalna odległość od wierzchołka początkowego
    :return: zbiór wierzchołków leżących w odległości nie większej niż max_distance
        od wierzchołka początkowego
    """
    # Zamiast zwykłej krotki użyj typu `namedtuple`, aby poprawić czytelność kodu.
    # (Jak sama nazwa wskazuje - w przypadku `namedtuple` każdy element krotki ma
    # swój identyfikator...)
    # v_id - etykieta wierzchołka
    # dist_s - od wierzchołka początkowego
    DistEntry = namedtuple('DistEntry', ['v_id', 'dist_s'])

    visited: Mapping[VertexID, Distance] = {}  # {wierzchołek -> odległość od wierzchołka początkowego}
    queue = [DistEntry(v_id=start_vertex_id, dist_s=0)]
    while queue:
        vertex_id, current_distance = queue.pop(0)  # rozpakowywanie krotki (tuple unpacking)
        if current_distance > max_distance:
            break
        if vertex_id not in visited:
            visited[vertex_id] = current_distance
            # Wstaw do kolejki nieodwiedzonych sąsiadów (odległość od sąsiada jest
            # o 1 większa w stosunku do odległości od bieżącego wierzchołka).
            queue.extend(
                [DistEntry(v_id=v_id, dist_s=current_distance + 1)
                 for v_id in adjlist[vertex_id - 1] if v_id not in visited]
            )
    # Zwróć zbiór etykiet odwiedzonych wierzchołków spełniających kryterium odległości.
    return {v for (v, d) in visited.items() if 1 <= d <= max_distance}


# Rozwiązanie równoważne do powyższego.
def neighbors_ver2(adjlist: AdjList, start_vertex_id: VertexID,
                   max_distance: Distance) -> Set[VertexID]:
    """Znajdź wierzchołki leżące w zadanym promieniu od wierzchołka początkowego.

    :param adjlist: lista sąsiedztwa
    :param start_vertex_id: etykieta wierzchołka, od którego zaczynamy przeszukiwanie
    :param max_distance: maksymalna odległość od wierzchołka początkowego
    :return: zbiór wierzchołków leżących w odległości nie większej niż max_distance
        od wierzchołka początkowego
    """
    neighbors_list = adjlist[start_vertex_id - 1].copy()
    # Indeks pierwszego dotychczas nieprzetworzonego wierzchołka w `neighbors_list`.
    unprocessed_offset = 0
    for i in range(max_distance - 1):
        # Rozpatrz wszystkie dotychczas nieprzetworzone wierzchołki w `neighbors_list`.
        for vertex_id in neighbors_list[unprocessed_offset:]:
            # Wstaw do kolejki wszystkich nieodwiedzonych sąsiadów danego wierzchołka.
            neighbors_list.extend([v_id for v_id in adjlist[vertex_id - 1] if v_id not in neighbors_list])
            unprocessed_offset += 1
    return set(neighbors_list)


# Rozwiązanie zadania BFS_NEIGHBORS działające, ale nieoptymalne
#   (bo wielokrotnie przetwarzamy te same wierzchołki).
def neighbors_not_optimal(adjlist: AdjList, start_vertex_id: VertexID,
                          max_distance: Distance) -> Set[VertexID]:
    """Znajdź wierzchołki leżące w zadanym promieniu od wierzchołka początkowego.

    :param adjlist: lista sąsiedztwa
    :param start_vertex_id: etykieta wierzchołka, od którego zaczynamy przeszukiwanie
    :param max_distance: maksymalna odległość od wierzchołka początkowego
    :return: zbiór wierzchołków leżących w odległości nie większej niż max_distance
        od wierzchołka początkowego
    """
    # Utwórz zbiór zawierający jeden element.
    vertices_to_visit = {start_vertex_id}
    for i in range(max_distance):
        # UWAGA: Iterowanie odbywa się na kopii (!) zbioru `vertices_to_visit`!
        for vertex_id in vertices_to_visit.copy():
            # Rozszerz zbiór sąsiadów o wszystkich sąsiadów aktualnego wierzchołka.
            vertices_to_visit.update(adjlist[vertex_id - 1])
    # Usuń wierzchołek początkowy ze zbioru odwiedzonych wierzchołków.
    return vertices_to_visit.difference([start_vertex_id])


if __name__ == '__main__':
    g = [
        [2, 4],
        [3],
        [],
        [5],
        [2, 6],
        [],
        [1]
    ]

    print(neighbors(g, 1, 1))
    print(neighbors(g, 1, 2))