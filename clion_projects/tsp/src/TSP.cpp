// Michal Sciubisz, 406285
#include "TSP.hpp"

#include <algorithm>
#include <stack>
#include <optional>

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
path_t StageState::get_path() {

    std::vector<vertex_t> container;

    for(auto elem : unsorted_path_) {
        container.push_back(elem); //utworzenie kontenera przechowującego elementy unsorted_path'a zeby nie modyfikowac tego elementu
    }

    for(std::size_t r = 0; r < matrix_.size(); r++){
        for(std::size_t c = 0; c< matrix_.size(); c++){
            if(matrix_[r][c] < INF) {
                container.emplace_back(vertex_t(r, c));
            }
        }
    }

    path_t sorted;
    sorted.push_back(container[0].col + 1); // dodanie jedynek zeby posortowana lista byla od razu wlasciwa

    while (sorted.size() < matrix_.size()){
        for(auto i : container){
            if(sorted.back() == i.row + 1){
                sorted.push_back(i.col + 1);
            }
        }
    }

    return sorted;
}

/**
 * Get minimum values from each row and returns them.
 * @return Vector of minimum values in row.
 */
std::vector<cost_t> CostMatrix::get_min_values_in_rows() const {
    std::vector<cost_t> min_values;

    for (const auto& elem : matrix_) {
        auto holder = INF;
        for (auto& value : elem) {
            holder = std::min(value, holder);
        }
        min_values.push_back(holder);
    }

    return min_values;
}

/**
 * Reduce rows so that in each row at least one zero value is present.
 * @return Sum of values reduced in rows.
 */
cost_t CostMatrix::reduce_rows() {
    std::vector<cost_t> min_values = get_min_values_in_rows();
    cost_t result = 0;

    for (std::size_t i = 0; i < size(); i++) {
        for (std::size_t j = 0; j < size(); j++) {
            if (matrix_[i][j] != INF)
                matrix_[i][j] -= min_values[i];
        }
    }

    for (auto value : min_values) {
        if (value != INF) //suma elementów z uwzględnieniem możliwości wystąpienia INF'a
            result += value;
    }

    return result;
}


/**
 * Get minimum values from each column and returns them.
 * @return Vector of minimum values in columns.
 */
std::vector<cost_t> CostMatrix::get_min_values_in_cols() const {
    std::vector<cost_t> min_val_in_col;

    for (std::size_t i = 0; i < size(); i++) {
        auto holder = INF;
        for (std::size_t j = 0; j < size(); j++) {
            holder = std::min(matrix_[j][i], holder);
        }
        min_val_in_col.push_back(holder);
    }

    return min_val_in_col;
}

/**
 *   Reduces rows so that in each column at least one zero value is present.
 * @return Sum of values reduced in columns.
 */
cost_t CostMatrix::reduce_cols() {
    std::vector<cost_t> min_values = get_min_values_in_cols();
    cost_t result = 0;

    for (std::size_t i = 0; i < size(); i++) {
        for (std::size_t j = 0; j < size(); j++) {
            if (matrix_[i][j] != INF)
                matrix_[i][j] -= min_values[j];
        }
    }

    for (auto value : min_values) {
        if(value != INF){
            result += value;
        }
    }

    return result;
}

/**
 * Get the cost of not visiting the vertex_t (@see: get_new_vertex())
 * @param row
 * @param col
 * @return The sum of minimal values in row and col, excluding the intersection value.
 */
cost_t CostMatrix::get_vertex_cost(std::size_t row, std::size_t col) const {
    cost_t min_row = INF;
    cost_t min_col = INF;

    for (std::size_t i = 0; i < size(); i++) {
        for (std::size_t j = 0; j < size(); j++) {
            if (i == row && j != col) {
                min_row = std::min(matrix_[row][j], min_row);
            }
            if (j == col && i != row) {
                min_col = std::min(matrix_[i][col], min_col);
            }
        }
    }
    auto result = min_col + min_row;

    return result;
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
    NewVertex vertex = NewVertex();
    NewVertex additional = NewVertex();

    for (std::size_t i = 0; i < matrix_.size(); i++) {
        for (std::size_t j = 0; j < matrix_.size(); j++) {
            if (matrix_[i][j] == 0) {
                additional.coordinates = vertex_t(i, j);
                additional.cost = matrix_.get_vertex_cost(i, j);
            }
            if (vertex.cost < additional.cost){
                vertex.cost = additional.cost;
                vertex.coordinates = additional.coordinates;
            }
        }
    }
    return vertex;
}

/**
 * Update the cost matrix with the new vertex.
 * @param new_vertex
 */
void StageState::update_cost_matrix(vertex_t new_vertex) {
    auto row = new_vertex.row;
    auto col = new_vertex.col;

    for (std::size_t i = 0; i < matrix_.size(); i++) {
        matrix_[i][col] = INF;
        matrix_[row][i] = INF;
    }
    matrix_[col][row] = INF;

    bool if_found_col = true; //sprawdzenie cykli, parametr row
    while(if_found_col){
        for (auto top : unsorted_path_){
            if (top.col == row){
                row = top.row;
                if_found_col = true;
                break;
            }
            else
                if_found_col = false;

        }
    }

    bool if_found_row = true; //sprawdzenie cykli, parametr col
    while(if_found_row){
        for (auto top : unsorted_path_){
            if (top.row == col){
                col = top.col;
                if_found_row = true;
                break;
            }
            else
                if_found_row = false;
        }
    }
    matrix_[col][row] = INF;
}

/**
 * Reduce the cost matrix.
 * @return The sum of reduced values.
 */
cost_t StageState::reduce_cost_matrix(){
    return matrix_.reduce_cols() + matrix_.reduce_rows();
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
    for (const auto& s: solutions) {
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
            cost_t new_cost = left_branch.reduce_cost_matrix(); // @TODO (KROK 1)


            // 2. Update the lower bound and check the break condition.
            left_branch.update_lower_bound(new_cost);
            if (left_branch.get_lower_bound() > best_lb) {
                break;
            }

            // 3. Get new vertex and the cost of not choosing it.
            NewVertex new_vertex = left_branch.choose_new_vertex(); // @TODO (Krok 2)

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
