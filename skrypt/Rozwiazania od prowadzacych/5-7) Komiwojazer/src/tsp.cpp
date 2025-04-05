#include "tsp.hpp"

#include <algorithm>
#include <limits>

#include <iostream>
#include <iomanip>

/**
 * Sprawdź, czy dany element macierzy kosztu wyraża przejscie zakazane.
 *
 * @param elem element macierzy
 * @return prawda, jeśli element wyraża przejscie zakazane; inaczej fałsz
 */
bool is_forbidden(elem_t elem) {
    return std::isnan(elem);
}

CostMatrix::CostMatrix(const std::vector<CostMatrixRow>& rows) : rows_(rows) {
    if (rows_.empty()) {
        throw InvalidSizeException("Size cannot be 0x0.");
    }

    for (const auto& row : rows) {
        if (row.empty()) {
            throw InvalidSizeException("Row size cannot be 0.");
        }
        if (row.size() != rows.size()) {
            throw InvalidSizeException("Not a square matrix.");
        }
    }
}

void print_cost_matrix(const CostMatrix& cost_matrix) {
    for (std::size_t r = 0; r < cost_matrix.size(); ++r) {
        for (std::size_t c = 0; c < cost_matrix.size(); ++c) {
            std::cout << std::setw(4);
            if (is_forbidden(cost_matrix[r][c])) {
                std::cout << "INF";
            } else {
                std::cout << std::setprecision(5) << cost_matrix[r][c];
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


/**
 * Znajdź minimalny element w wierszu (ew. z pominięciem wybranej kolumny).
 *
 * @param cost_matrix macierz kosztu
 * @param row_inx indeks wiersza, który ma zostać przeszukany
 * @param col_inx_to_omit indeks kolumny, którą należy pominąć
 * @return minimalny element w wierszu
 */
elem_t get_min_in_row(const CostMatrix& cost_matrix, std::size_t row_inx,
                      std::size_t col_inx_to_omit = std::numeric_limits<std::size_t>::max()) {
    std::size_t min_elem_col_inx = (col_inx_to_omit > 0) ? 0 : 1;
    for (std::size_t c = 0; c < cost_matrix[0].size(); ++c) {
        if (((cost_matrix[row_inx][c] < cost_matrix[row_inx][min_elem_col_inx])
             || is_forbidden(cost_matrix[row_inx][min_elem_col_inx]))
            && (c != col_inx_to_omit)) {
            min_elem_col_inx = c;
        }
    }
    return cost_matrix[row_inx][min_elem_col_inx];
}

/**
 * Znajdź minimalny element w kolumnie (ew. z pominięciem wybranego wiersza).
 *
 * @param cost_matrix macierz kosztu
 * @param col_inx indeks kolumny, która ma zostać przeszukana
 * @param row_inx_to_omit indeks wiersza, który należy pominąć
 * @return minimalny element w kolumnie
 */
elem_t get_min_in_column(const CostMatrix& cost_matrix, std::size_t col_inx,
                         std::size_t row_inx_to_omit = std::numeric_limits<std::size_t>::max()) {
    std::size_t min_elem_row = (row_inx_to_omit > 0) ? 0 : 1;
    for (std::size_t r = 0; r < cost_matrix.size(); ++r) {
        if (((cost_matrix[r][col_inx] < cost_matrix[min_elem_row][col_inx])
             || is_forbidden(cost_matrix[min_elem_row][col_inx]))
            && (r != row_inx_to_omit)) {
            min_elem_row = r;
        }
    }
    return cost_matrix[min_elem_row][col_inx];
}

/**
 * Wyznacz wektor minimalnych elementów w poszczególnych wierszach macierzy kosztu.
 *
 * @param cost_matrix macierz kosztu
 * @return wektor minimalnych elementów w poszczególnych wierszach macierzy kosztu
*/
std::vector<elem_t> get_mins_in_rows(const CostMatrix& cost_matrix) {
    std::vector<elem_t> mins_in_rows(cost_matrix.size());
    for (std::size_t r = 0; r < cost_matrix.size(); ++r) {
        mins_in_rows[r] = get_min_in_row(cost_matrix, r);
    }
    return mins_in_rows;
}

/**
 * Wyznacz wektor minimalnych elementów w poszczególnych kolumnach macierzy kosztu.
 *
 * @param cost_matrix macierz kosztu
 * @return wektor minimalnych elementów w poszczególnych kolumnach macierzy kosztu
*/
std::vector<elem_t> get_mins_in_columns(const CostMatrix& cost_matrix) {
    std::vector<elem_t> mins_in_columns(cost_matrix.size());
    for (std::size_t c = 0; c < cost_matrix.size(); ++c) {
        mins_in_columns[c] = get_min_in_column(cost_matrix, c);
    }
    return mins_in_columns;
}

/**
 * Dokonaj redukcji (wszystkich) wierszy macierzy kosztu.
 *
 * @param cost_matrix macierz kosztu
 * @return macierz kosztu po redukcji w wierszach
 */
CostMatrix reduce_all_rows(CostMatrix cost_matrix) {
    CostMatrixRow mins_in_rows = get_mins_in_rows(cost_matrix);
    for (std::size_t r = 0; r < cost_matrix.size(); ++r) {
        for (auto& elem : cost_matrix[r]) {
            elem -= mins_in_rows[r];
        }
    }
    return cost_matrix;
}

/**
 * Dokonaj redukcji (wszystkich) kolumn macierzy kosztu.
 *
 * @param cost_matrix macierz kosztu
 * @return macierz kosztu po redukcji w kolumnach
 */
CostMatrix reduce_all_columns(CostMatrix cost_matrix) {
    CostMatrixRow mins_in_columns = get_mins_in_columns(cost_matrix);
    for (std::size_t r = 0; r < cost_matrix.size(); ++r) {
        for (std::size_t c = 0; c < cost_matrix.size(); ++c) {
            cost_matrix[r][c] -= mins_in_columns[c];
        }
    }
    return cost_matrix;
}

/**
 * Znajdź w zredukowanej macierzy kosztu przejście o największej sumie najmniejszych
 *  wartości w wierszu i kolumnie macierzy zawierających dane przejście.
 *  Kandydatami są wyłącznie te przejścia, których koszt po reducji wynosi 0.
 *
 * @param cost_matrix macierz kosztu
 * @return przejście o największej sumie najmniejszych wartości w wierszu i kolumnie
 */
Edge find_max_edge(const CostMatrix& cost_matrix) {
    std::size_t max_elem_row_inx = 0; // indeks wiersza zawierającego największą sumę wartości
    std::size_t max_elem_col_inx = 0; // indeks kolumny zawierającej największą sumę wartości
    elem_t max_elem_rc_sum = INF; // maksymalna suma minimalnych elementów w aktualnie rozpatrywanym wierszu i kolumnie

    for (std::size_t r = 0; r < cost_matrix.size(); ++r) {
        for (std::size_t c = 0; c < cost_matrix.size(); ++c) {
            if (cost_matrix[r][c] == 0) {
                elem_t elem_rc_sum = get_min_in_row(cost_matrix, r, c) + get_min_in_column(cost_matrix, c, r);
                // Warunek "LUB max_elem_rc_sum wyraża przejście zabronione" służy
                //  do nadania odpowiedniej wartości podczas rozpatrywania pierwszego
                // przejścia.
                if ((elem_rc_sum > max_elem_rc_sum)
                    || is_forbidden(max_elem_rc_sum)) {
                    max_elem_rc_sum = elem_rc_sum;
                    max_elem_row_inx = r;
                    max_elem_col_inx = c;
                }
            }
        }
    }
    return Edge{max_elem_row_inx, max_elem_col_inx};
}

/**
 * Wyznacz wszystkie dozwolone przejścia w danym wektorze kosztów.
 *
 * @param elems wektor kosztów
 * @return wektor iteratorów do dozwolonych przejść w wektorze wejściowym
 */
std::vector<std::size_t> find_allowed_transitions(const std::vector<elem_t>& elems) {
    std::vector<std::size_t> indexes;
    auto it = std::begin(elems);
    while ((it = std::find_if(it, std::end(elems), [](const auto& elem) {return !is_forbidden(elem); })) != std::end(elems)) {
        indexes.push_back(std::distance(std::begin(elems), it));
        ++it;
    }
    return indexes;
}

/**
 * Dokonaj sortowania topologicznego wektora krawędzi.
 *
 * @param edges wektor krawędzi do posortowania
 * @return ścieżka utworzona z posortowanych krawędzi
 */
Path sort_edges(const std::vector<Edge>& edges) {
    Path path{edges[0].first, edges[0].second};

    while (*(std::end(path) - 1) != path[0]) {
        for (const auto& edge : edges) {
            if (edge.first == *(std::end(path) - 1)) {
                path.push_back(edge.second);
            }
        }
    }

    return path;
}

/**
 * Wyznacz przykładowe rozwiązanie problemu komiwojażera dla grafu reprezentowanego
 *  przez zadaną macierz kosztu.
 *
 * @param cost_matrix macierz kosztu
 * @return ścieżka zawierająca rozwiązanie problemu komiwojażera dla zadanego grafu
 */
Path tsp(CostMatrix cost_matrix) {
    std::size_t max_algorithm_iterations = cost_matrix.size() - 2;
    std::vector<Edge> best_edges;

    for (size_t i = 0; i < max_algorithm_iterations; ++i) {
        // Zredukuj macierz kosztu.
        cost_matrix = reduce_all_rows(cost_matrix);
        cost_matrix = reduce_all_columns(cost_matrix);

        // Znajdź najlepszą krawędź i dodaj do cząstkowych rozwiązań.
        Edge max_edge = find_max_edge(cost_matrix);
        best_edges.push_back(max_edge);

        // Usuń najlepszą krawędź z macierzy kosztu.
        for (std::size_t r = 0; r < cost_matrix.size(); ++r) {
            cost_matrix[r][max_edge.second] = INF;
        }
        for (std::size_t c = 0; c < cost_matrix.size(); ++c) {
            cost_matrix[max_edge.first][c] = INF;
        }
        cost_matrix[max_edge.second][max_edge.first] = INF;
    }

//  print_cost_matrix(cost_matrix);

    // Wybierz najlepsze rozwiązanie w macierzy "2x2".
    CostMatrixRow min_costs_columns = get_mins_in_columns(cost_matrix);
    CostMatrixRow min_costs_rows = get_mins_in_rows(cost_matrix);
    auto columns_indexes = find_allowed_transitions(min_costs_columns);
    auto rows_indexes = find_allowed_transitions(min_costs_rows);

    if (is_forbidden(cost_matrix[rows_indexes[0]][columns_indexes[0]])
        || is_forbidden(cost_matrix[rows_indexes[1]][columns_indexes[1]])) {
        best_edges.emplace_back(Edge{rows_indexes[0], columns_indexes[1]});
        best_edges.emplace_back(Edge{rows_indexes[1], columns_indexes[0]});
    } else {
        best_edges.emplace_back(Edge{rows_indexes[0], columns_indexes[0]});
        best_edges.emplace_back(Edge{rows_indexes[1], columns_indexes[1]});
    }

    auto best_path = sort_edges(best_edges);

    for (auto& v : best_path) {
        // Przejdź z reprezentacji indeksowej na numery wierzchołków.
        ++v;
    }

    return best_path;
}
