#include "../../Utils/TestRunner.h"
#include "Paginator.h"

#include <vector>
#include <future>
#include <algorithm>

using namespace std;

template <typename T>
int64_t CalculateSingleMatrixSum(const T& matrix){
    int64_t sum = 0;
    for(auto& matrix_row : matrix){
        for(auto& item : matrix_row){
            sum += item;
        }
    }
    return sum;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    int64_t result = 0;
    std::vector<future<int64_t>> futures;

    for(auto page : Paginate(matrix, 2000)){
        futures.push_back(async([=] {return CalculateSingleMatrixSum(page);}));
    }

    for(auto& item : futures){
        result += item.get();
    }

    return result;
}


void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}
