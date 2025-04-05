//
// Created by Dominika on 01.11.2020.
//

//Grupa ZPO_grupka
//Patrycja Lobodzinska
//Karolina Wozniak
//Gustaw Cyburt

#include "TSP.hpp"
#include <algorithm>
#include <stack>
#include <optional>

std::ostream &operator<<(std::ostream &os, const CostMatrix &cm) {
    for (std::size_t r = 0; r < cm.size(); ++r) {
        for (std::size_t c = 0; c < cm.size(); ++c) {
            const auto &elem = cm[r][c];
            os << (is_inf(elem) ? "INF" : std::to_string(elem)) << " ";
        }
        os << "\n";
    }
    os << std::endl;

    return os;
}

/* PART 1 */

/**
 * Create path from unresult path and last 2x2 cost matrix.
 * @return The vector of consecutive vertex.
 */
path_t StageState::get_path() {
    path_t posortowane = {};
    auto wektor_wierzch = unsorted_path_;
    for (std::size_t i = 0; i < matrix_.size(); i++)
    {
        for (std::size_t j = 0; j < matrix_.size(); j++)
        {
            if (matrix_[i][j] != INF)
                wektor_wierzch.emplace_back(vertex_t(i, j));
        }
    }

    posortowane.push_back(wektor_wierzch[0].row);
    posortowane.push_back(wektor_wierzch[0].col);
    wektor_wierzch.erase(wektor_wierzch.cbegin());
    while (!wektor_wierzch.empty())
    {
        for (std::size_t i = 0; i < wektor_wierzch.size(); i++)
        {
            if (wektor_wierzch[i].row == posortowane.back())
            {
                posortowane.push_back(wektor_wierzch[i].col);
                wektor_wierzch.erase(wektor_wierzch.cbegin() + i);
                break;
            }
        }
    }
    posortowane.pop_back();
    return posortowane;
}

//path_t StageState::get_path() {
//    reduce_cost_matrix();
//    NewVertex new_vertex = choose_new_vertex();
//    update_cost_matrix(new_vertex.coordinates);
//    unsorted_path_.push_back(new_vertex.coordinates);
//    for(std::size_t i = 0; i < matrix_.size(); i++){
//        for(std::size_t j = 0; j < matrix_.size(); j++){
//            if(matrix_[i][j] < INF){
//                vertex_t last_vertex;
//                last_vertex.row = i;
//                last_vertex.col = j;
//                append_to_path(last_vertex);
//            }
//        }
//    }
//    std::vector<size_t> sorted_ver;
//    sorted_ver.push_back(unsorted_path_[0].row+1);
//    size_t loc_var = unsorted_path_[0].col;
//
//    while (sorted_ver.size() < get_level()){
//        for(size_t i = 0; i<get_level(); i++){
//            if(unsorted_path_[i].row == loc_var){
//                sorted_ver.push_back(unsorted_path_[i].row+1);
//                loc_var = unsorted_path_[i].col;
//            }
//        }
//    }
//    return sorted_ver;
//}

/**
 * Get minimum values from each row and returns them.
 * @return Vector of minimum values in row.
 */
std::vector<cost_t> CostMatrix::get_min_values_in_rows() const {
    std::vector<cost_t> minimalne_wartosci = {};
    for (const auto &row : matrix_)
    {
        minimalne_wartosci.push_back(*std::min_element((row).cbegin(), (row).cend()));
    }
    return minimalne_wartosci;
}


/**
 * Reduce rows so that in each row at least one zero value is present.
 * @return Sum of values reduced in rows.
 */
cost_t CostMatrix::reduce_rows()
{
    std::vector<cost_t> min_1 = get_min_values_in_rows();

    for (std::size_t m = 0; m < size(); m++)
    {
        for (std::size_t n = 0; n < size(); n++)
            if (matrix_[m][n] != INF)
                matrix_[m][n] -= min_1[m];
    }
    cost_t wynik = 0;
    for (auto elem : min_1) {
        if (elem != INF)
            wynik += elem;
    }
    return wynik;
}


/**
 * Get minimum values from each column and returns them.
 * @return Vector of minimum values in columns.
 */
std::vector<cost_t> CostMatrix::get_min_values_in_cols() const
{
    std::vector<cost_t> min_2 = {};

    for (std::size_t m = 0; m < size(); m++)
    {
        cost_t minimum = matrix_[0][m];
        for (std::size_t n = 1; n < size(); n++)
        {
            if (matrix_[n][m] < minimum)
                minimum = matrix_[n][m];
        }

        min_2.push_back(minimum);
    }
    return min_2;
}

/**
 * Reduces rows so that in each column at least one zero value is present.
 * @return Sum of values reduced in columns.
 */
cost_t CostMatrix::reduce_cols() {
    std::vector<cost_t> min_cols_vector = get_min_values_in_cols();

    for (std::size_t i = 0; i < size(); i++)
    {
        for (std::size_t j = 0; j < size(); j++) {
            if (matrix_[i][j] != INF)
                matrix_[i][j] -= min_cols_vector[j];
        }
    }
    cost_t wynik = 0;
    for (auto element : min_cols_vector)
    {
        if (element != INF)
            wynik += element;
    }
    return wynik;
}

/**
 * Get the cost of not visiting the vertex_t (@see: get_new_vertex())
 * @param row
 * @param col
 * @return The sum of minimal values in row and col, excluding the intersection value.
 */
cost_t CostMatrix::get_vertex_cost(std::size_t row, std::size_t col) const
{
    cost_t minimum_wiersz = INF;
    cost_t minimum_kolumna = INF;

    for (std::size_t m = 0; m < size(); m++)
    {
        for (std::size_t n = 0; n < size(); n++)
        {
            if (m != row && n == col && matrix_[m][n] < minimum_kolumna && matrix_[m][n] != INF)
                minimum_kolumna = matrix_[m][n];
            if (m == row && n != col && matrix_[m][n] < minimum_wiersz && matrix_[m][n] != INF)
                minimum_wiersz = matrix_[m][n];
        }
    }
    auto wynik = minimum_wiersz + minimum_kolumna;
    return wynik;
}

/* PART 2 */

/**
 * Choose next vertex to visit:
 * - Look for vertex_t (pair row and column) with value 0 in the current cost matrix.
 * - Get the vertex_t cost (calls get_vertex_cost()).
 * - Choose the vertex_t with maximum cost and returns it.
 * @param cm
 * @return The coordinates of the next vertex.
 */
NewVertex StageState::choose_new_vertex() {
    cost_t max_koszt = 0;
    vertex_t max_wierzch;

    for (std::size_t i = 0; i < matrix_.size(); i++)
    {
        for (std::size_t j = 0; j < matrix_.size(); j++)
        {
            if (matrix_[i][j] == 0 && max_koszt < matrix_.get_vertex_cost(i, j))
            {
                max_koszt = matrix_.get_vertex_cost(i, j);
                max_wierzch = vertex_t(i, j);
            }
        }
    }
    auto wynik = NewVertex(max_wierzch, max_koszt);
    return wynik;
}

/**
 * Update the cost matrix with the new vertex.
 * @param new_vertex
 */
void StageState::update_cost_matrix(vertex_t new_vertex)
{
    for (std::size_t i = 0; i < matrix_.size(); i++)
    {
        matrix_[i][new_vertex.col] = INF;
        matrix_[new_vertex.row][i] = INF;
    }
    matrix_[new_vertex.col][new_vertex.row] = INF;

    auto rodzic = new_vertex.row;
    bool czy_znaleziony = true;
    while (czy_znaleziony) {
        for (auto wierzcholek : unsorted_path_)
        {
            if (wierzcholek.col == rodzic)
            {
                czy_znaleziony = true;
                rodzic = wierzcholek.row;
                break;
            }
            else
                czy_znaleziony = false;
        }
    }

    auto dziecko = new_vertex.col;
    bool czy_znaleziony_2 = true;
    while (czy_znaleziony_2) {
        for (auto wierzcholek : unsorted_path_)
        {
            if (wierzcholek.row == dziecko)
            {
                dziecko = wierzcholek.col;
                czy_znaleziony_2 = true;
                break;
            }
            else
                czy_znaleziony_2 = false;
        }
    }
    matrix_[dziecko][rodzic] = INF;
}

/**
 * Reduce the cost matrix.
 * @return The sum of reduced values.
 */
cost_t StageState::reduce_cost_matrix() {
    auto wynik=matrix_.reduce_rows() + matrix_.reduce_cols();
    return wynik;
}

/**
 * Given the optimal path, return the optimal cost.
 * @param optimal_path
 * @param m
 * @return Cost of the path.
 */
cost_t get_optimal_cost(const path_t &optimal_path, const cost_matrix_t &m)
{
    cost_t koszt = 0;

    for (std::size_t licznik = 1; licznik < optimal_path.size(); ++licznik)
    {
        koszt = koszt+ m[optimal_path[licznik - 1]][optimal_path[licznik]];
    }

    koszt += m[optimal_path[optimal_path.size() - 1]][optimal_path[0]];

    return koszt;
}

/**
 * Create the right branch matrix with the chosen vertex forbidden and the new lower bound.
 * @param m
 * @param v
 * @param lb
 * @return New branch.
 */
StageState create_right_branch_matrix(cost_matrix_t m, vertex_t v, cost_t lb)
{
    CostMatrix macierz(m);
    macierz[v.row][v.col] = INF;
    return StageState(macierz, {}, lb);
}

/**
 * Retain only optimal ones (from all possible ones).
 * @param solutions
 * @return Vector of optimal solutions.
 */
tsp_solutions_t filter_solutions(tsp_solutions_t solutions) {
    cost_t optimal_cost = INF;
    for (const auto &s : solutions) {
        optimal_cost = (s.lower_bound < optimal_cost) ? s.lower_bound : optimal_cost;
    }

    tsp_solutions_t optimal_solutions;
    std::copy_if(solutions.begin(), solutions.end(),
                 std::back_inserter(optimal_solutions),
                 [&optimal_cost](const tsp_solution_t &s) { return s.lower_bound == optimal_cost; }
    );

    return optimal_solutions;
}

/**
 * Solve the TSP.
 * @param cm The cost matrix.
 * @return A list of optimal solutions.
 */
tsp_solutions_t solve_tsp(const cost_matrix_t &cm) {

    StageState left_branch(cm);

    // The branch & bound tree.
    std::stack<StageState> tree_lifo;

    // The number of levels determines the number of steps before obtaining
    // a 2x2 matrix.
    std::size_t n_levels = cm.size() - 2;

    tree_lifo.push(left_branch);   // Use the first cost matrix as the root.

    cost_t best_lb = INF;
    tsp_solutions_t solutions;

    while (!tree_lifo.empty()) {

        left_branch = tree_lifo.top();
        tree_lifo.pop();

        while (left_branch.get_level() != n_levels && left_branch.get_lower_bound() <= best_lb) {
            // Repeat until a 2x2 matrix is obtained or the lower bound is too high...

            if (left_branch.get_level() == 0) {
                left_branch.reset_lower_bound();
            }

            // 1. Reduce the matrix in rows and columns.
            cost_t new_cost = left_branch.reduce_cost_matrix();

            // 2. Update the lower bound and check the break condition.
            left_branch.update_lower_bound(new_cost);
            if (left_branch.get_lower_bound() > best_lb)
            {
                break;
            }

            // 3. Get new vertex and the cost of not choosing it.

            NewVertex new_vertex = left_branch.choose_new_vertex();

            // 4.

            left_branch.append_to_path(new_vertex.coordinates);
            // 5.

            left_branch.update_cost_matrix(new_vertex.coordinates);
            // 6. Update the right branch and push it to the LIFO.

            cost_t new_lower_bound = left_branch.get_lower_bound() + new_vertex.cost;
            tree_lifo.push(create_right_branch_matrix(cm, new_vertex.coordinates,
                                                      new_lower_bound));
        }

        if (left_branch.get_lower_bound() <= best_lb) {
            // If the new solution is at least as good as the previous one,
            // save its lower bound and its path.
            best_lb = left_branch.get_lower_bound();
            path_t new_path = left_branch.get_path();
            solutions.push_back({get_optimal_cost(new_path, cm), new_path});
        }
    }

    return filter_solutions(solutions); // Filter solutions to find only optimal ones.
}

path_t StageState::get_path() {
    reduce_cost_matrix();
    NewVertex new_vertex = choose_new_vertex();
    update_cost_matrix(new_vertex.coordinates);
    unsorted_path_.push_back(new_vertex.coordinates);
    for(std::size_t i = 0; i < matrix_.size(); i++){
        for(std::size_t j = 0; j < matrix_.size(); j++){
            if(matrix_[i][j] < INF){
                vertex_t last_vertex;
                last_vertex.row = i;
                last_vertex.col = j;
                append_to_path(last_vertex);
            }
        }
    }
    std::vector<size_t> sorted_ver;
    sorted_ver.push_back(unsorted_path_[0].row+1);
    size_t loc_var = unsorted_path_[0].col;

    while (sorted_ver.size() < get_level()){
        for(size_t i = 0; i<get_level(); i++){
            if(unsorted_path_[i].row == loc_var){
                sorted_ver.push_back(unsorted_path_[i].row+1);
                loc_var = unsorted_path_[i].col;
            }
        }
    }
    return sorted_ver;
}
