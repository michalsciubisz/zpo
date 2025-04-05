#include "tsp.hpp"

#include <iostream>

int main() {

  std::vector<CostMatrixRow> cost_matrix_raw {
    {INF, 10, 8, 19, 12},
    {10, INF, 20, 6, 3},
    {8, 20, INF, 4, 2},
    {19, 6, 4, INF, 7},
    {12, 3, 2, 7, INF}
  };
  CostMatrix cost_matrix(cost_matrix_raw);

  std::cout << "\nCost matrix:\n\n";
  print_cost_matrix(cost_matrix);

  auto best_path = tsp(cost_matrix);

  std::cout << "\nTSP path:  ";
  for (const auto& e : best_path) {
    std::cout << e << " ";
  }
  std::cout << std::endl;

  return 0;
}
