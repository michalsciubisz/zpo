#ifndef INCLUDE_TSP_HPP_
#define INCLUDE_TSP_HPP_

#include <vector>
#include <cmath>
#include <functional>

using elem_t = double;
using Edge = std::pair<std::size_t, std::size_t>;
using Path = std::vector<std::size_t>;
using CostMatrixRow = std::vector<elem_t>;

#define INF (NAN)

class CostMatrix {
public:
    explicit CostMatrix(const std::vector<CostMatrixRow>& rows);

    ~CostMatrix() = default;

    std::size_t size() const { return rows_.size(); }

    const CostMatrixRow& operator[](std::size_t pos) const { return rows_[pos]; }

    CostMatrixRow& operator[](std::size_t pos) { return rows_[pos]; }

private:
    std::vector<CostMatrixRow> rows_;
};

class InvalidSizeException : public std::runtime_error {
public:
    explicit InvalidSizeException(const std::string& what_arg) : std::runtime_error(what_arg) {}
};

Path tsp(CostMatrix cost_matrix);

void print_cost_matrix(const CostMatrix& cost_matrix);


#endif /* INCLUDE_TSP_HPP_ */
