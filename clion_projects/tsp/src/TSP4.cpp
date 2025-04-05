#include "TSP.hpp"

#include <algorithm>
#include <stack>
#include <optional>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const CostMatrix& cm) {
    for (std::size_t r = 0; r < cm.size(); ++r) {
        for (std::size_t c = 0; c < cm.size(); ++c) {
            const auto& elem = cm[r][c];
            os << (is_inf(elem) ? "INF" : std::to_string(elem)) << " ";
        }
        os << "\n";
    }
    os << std::endl;

    return os;
}

/* PART 1 */

/**
 * Create path from unsorted path and last 2x2 cost matrix.
 * @return The vector of consecutive vertex.
 */
// TODO: Implement it!
path_t StageState::get_path() { //tu cos nie gra

    // Adding last 2 vertex to list
    for(std::size_t row = 0; row < matrix_.size(); row++){
        for(std::size_t col = 0; col < matrix_.size(); col++){
            if(matrix_[row][col] != INF){
                append_to_path(vertex_t(row, col));
            }
        }
    }
    // Creating sorted path
    path_t sorted_path;
    //Adding first vertex from unsorted path as first sorted vertex
    sorted_path.push_back(unsorted_path_[0].col);

    //Adding new sorted vertexes
    while(sorted_path.size() < matrix_.size()){
        for(auto i : unsorted_path_){
            if(sorted_path.back() == i.row){
                sorted_path.push_back(i.col);
            }
        }
    }

    //Starting indexing from 1
    for(auto& i : sorted_path){
        i = i+1;
    }

    return sorted_path;
}

/**
 * Get minimum values from each row and returns them.
 * @return Vector of minimum values in row.
 */
std::vector<cost_t> CostMatrix::get_min_values_in_rows() const { //to jest git
    std::vector<cost_t> min_values = {};
    for(const auto &row: matrix_)
    {
        min_values.push_back(*std::min_element((row).cbegin(), (row).cend())); //uzuskanie minimalnych wartośći w rzędach
    }
    return min_values;
}


/**
 * Reduce rows so that in each row at least one zero value is present.
 * @return Sum of values reduced in rows.
 */
cost_t CostMatrix::reduce_rows() {//to jest git
    std::vector<cost_t> min_val = get_min_values_in_rows();
    for (std::size_t i = 0; i < matrix_.size(); i++) { //iterowanie po rzędach
        for (std::size_t j = 0; j < matrix_.size(); j++) { //iterowanie po wierszach
            if (matrix_[i][j] != INF)
                matrix_[i][j] -= min_val[i]; //odejmowanie najmniejszych wartości z rzędów

        }
    }
    cost_t result_min_values = 0;

    for (auto elem: min_val) { //obliczanie sumy minimalnych wartości
        if (elem != INF)
            result_min_values += elem;
    }
    return result_min_values;
}

/**
 * Get minimum values from each column and returns them.
 * @return Vector of minimum values in columns.
 */
std::vector<cost_t> CostMatrix::get_min_values_in_cols() const {//to jest git

    std::vector<cost_t> min_values_2 = {};

    for (std::size_t i = 0; i < matrix_.size(); i++) {
        cost_t min_column = matrix_[0][i];

        for (std::size_t j = 0; j < matrix_.size(); j++) {
            if (matrix_[j][i] < min_column)
                min_column = matrix_[j][i];
        }

        min_values_2.push_back(min_column);
    }
    return min_values_2;
}

/**
 * Reduces rows so that in each column at least one zero value is present.
 * @return Sum of values reduced in columns.
 */
cost_t CostMatrix::reduce_cols() { //to tez jest git

    std::vector<cost_t> min_val_cols = get_min_values_in_cols();

    for (std::size_t i = 0; i <size(); i++) {
        for (std::size_t j = 0; j <size() ; j++) {
            if (matrix_[i][j] != INF)
                matrix_[i][j] -= min_val_cols[j];
        }
    }
    cost_t result = 0;
    for(auto elem: min_val_cols){
        if (elem != INF)
            result += elem;
    }
    return result;
}

/**
 * Get the cost of not visiting the vertex_t (@see: get_new_vertex())
 * @param row
 * @param col
 * @return The sum of minimal values in row and col, excluding the intersection value.
 */
cost_t CostMatrix::get_vertex_cost(std::size_t row, std::size_t col) const { //tu jest cos zle
    cost_t row_min_value = INF;
    cost_t col_min_value = INF;

    for(std::size_t c = 0; c < matrix_.size(); c++){
        if(c == col){
            continue;
        }
        if(matrix_[row][c] < row_min_value){
            row_min_value = matrix_[row][c];
        }
    }

    for(std::size_t r = 0; r < matrix_.size(); r++){
        if(r== row){
            continue;
        }
        if(matrix_[r][col] < col_min_value){
            col_min_value = matrix_[r][col];
        }
    }
    return col_min_value + row_min_value;
}

//cost_t CostMatrix::get_vertex_cost(std::size_t row, std::size_t col) const {
//
//    cost_t min_val_row = INF;
//    cost_t min_val_col = INF;
//
//    for (std::size_t i = 0; i <matrix_.size() ; i++) {
//        for (std::size_t j = 0; j <matrix_.size() ; j++) {
//            if (i != row && i == col && matrix_[row][j] <= min_val_col && matrix_[row][j] != INF)
//                min_val_col = matrix_[i][j];
//            if (i != row && i == col && matrix_[i][col] <= min_val_row && matrix_[i][col] != INF)
//                min_val_row = matrix_[i][j];
//        }
//    }
//
//    return min_val_row + min_val_col;
//}

/* PART 2 */

/**
 * Choose next vertex to visit:
 * - Look for vertex_t (pair row and column) with value 0 in the current cost matrix.
 * - Get the vertex_t cost (calls get_vertex_cost()).
 * - Choose the vertex_t with maximum cost and returns it.
 * @return The coordinates of the next vertex.
 */
NewVertex StageState::choose_new_vertex() {
    cost_t max_cost = 0; //zainicjalozowanie podpunktu 1
    vertex_t max_apex;
    for (std::size_t i = 0; i < matrix_.size(); i++) {
        for (std::size_t j = 0; j < matrix_.size(); j++) {
            if(matrix_[i][j] == 0 && matrix_.get_vertex_cost(i,j) > max_cost){

                max_cost += matrix_.get_vertex_cost(i,j);
                max_apex = vertex_t(i,j);
            }
        }
    }

    auto result = NewVertex(max_apex);
    return result;
}

/**
 * Update the cost matrix with the new vertex.
 * @param new_vertex
 */
// TODO: Implement it! CYKLE
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
    auto result = matrix_.reduce_cols() + matrix_.reduce_rows();
    return result;
}

/**
 * Given the optimal path, return the optimal cost.
 * @param optimal_path
 * @param m
 * @return Cost of the path.
 */
cost_t get_optimal_cost(const path_t& optimal_path, const cost_matrix_t& m) {
    cost_t cost = 0;

    for (std::size_t idx = 1; idx < optimal_path.size(); ++idx) {
        cost += m[optimal_path[idx - 1] - 1][optimal_path[idx] - 1];
    }

    // Add the cost of returning from the last city to the initial one.
    cost += m[optimal_path[optimal_path.size() - 1] - 1][optimal_path[0] - 1];

    return cost;
}


/**
 * Create the right branch matrix with the chosen vertex forbidden and the new lower bound.
 * @param m
 * @param v
 * @param lb
 * @return New branch.
 */
StageState create_right_branch_matrix(cost_matrix_t m, vertex_t v, cost_t lb) {
    CostMatrix cm(m);
    cm[v.row][v.col] = INF;
    return StageState(cm, {}, lb);
}

/**
 * Retain only optimal ones (from all possible ones).
 * @param solutions
 * @return Vector of optimal solutions.
 */
tsp_solutions_t filter_solutions(tsp_solutions_t solutions) {
    cost_t optimal_cost = INF;
    for (const auto& s : solutions) {
        optimal_cost = (s.lower_bound < optimal_cost) ? s.lower_bound : optimal_cost;
    }

    tsp_solutions_t optimal_solutions;
    std::copy_if(solutions.begin(), solutions.end(),
                 std::back_inserter(optimal_solutions),
                 [&optimal_cost](const tsp_solution_t& s) { return s.lower_bound == optimal_cost; }
    );

    return optimal_solutions;
}

/**
 * Solve the TSP.
 * @param cm The cost matrix.
 * @return A list of optimal solutions.
 */
tsp_solutions_t solve_tsp(const cost_matrix_t& cm) {

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
//            cost_t new_cost = 0; // @TODO (KROK 1)
            cost_t new_cost = left_branch.reduce_cost_matrix();

            // 2. Update the lower bound and check the break condition.
            left_branch.update_lower_bound(new_cost);
            if (left_branch.get_lower_bound() > best_lb) {
                break;
            }

            // 3. Get new vertex and the cost of not choosing it.
            // @TODO (KROK 2)
            NewVertex new_vertex = left_branch.choose_new_vertex();

            // 4. @TODO Update the path - use append_to_path method.
            left_branch.append_to_path(new_vertex.coordinates);
            // 5. @TODO (KROK 3) Update the cost matrix of the left branch.
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

//Bartosz Bartoszewski, 406690
