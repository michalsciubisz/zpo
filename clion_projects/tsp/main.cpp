#include "TSP.hpp"

#include <iostream>


int main() {
//    cost_matrix_t cm = {{INF, 10, 8,   19, 12},
//                      {10, INF, 20,  6,  3},
//                      {8,   20, INF, 4,  2},
//                      {19,  6,  4, INF,  7},
//                      {12,  3,  2,   7, INF}
//    };

    /* Rozwiązania:
     * 32 : 3 4 5 2 1
     * 32 : 2 5 4 3 1
     */

//    cost_matrix_t cm {
//            {INF, 12,   3,  45,   6},
//            {78, INF,  90,  21,   3},
//            { 5,  56, INF,  23,  98},
//            {12,   6,   8, INF,  34},
//            { 3,  98,   3,   2, INF}
//    };

    /* Rozwiązanie:
     * 30 : 5 4 3 1 2
    */

//    cost_matrix_t cm {
//            {INF,  3,  4,  2,  7},
//            {3,  INF,  4,  6,  3},
//            {4,  4,  INF,  5,  8},
//            {2,  6,  5,  INF,  6},
//            {7,  3,  8,  6,  INF},
//    };

    /* Rozwiązania:
     * 19 : 5 4 1 3 2
     * 19 : 2 3 1 4 5
    */

    cost_matrix_t cm {
            {INF, 12,   3,  45,   6,   7,   4},
            {78, INF,  90,  21,   3,  10,  14},
            { 5,  56, INF,  23,  98,  15,  87},
            {12,   6,   8, INF,  34,   7,  23},
            { 3,   9,   8,   2, INF,  11,   9},
            { 8,  78,   9,  33,  12, INF,   8},
            { 2,  34,  22,   6,  90,  35, INF}
    };

    tsp_solutions_t solutions = solve_tsp(cm);


    for (auto elem : solutions) {
        std::cout << elem.lower_bound << " : ";
        for (auto pelem : elem.path) {
            std::cout << pelem << " ";
        }
        std::cout << "\n";
    }

    return EXIT_SUCCESS;
}
