#include "test_runner.h"
#include <vector>
#include <future>
#include <algorithm>
#include <numeric>

using namespace std;

template <typename T>
class Page{
private:
    T begin_;
    T end_;
public:
    Page(T vBegin, T vEnd) : begin_(std::move(vBegin)), end_(std::move(vEnd)) {}

    T begin() const {return  begin_;}
    T end() const {return end_;}

    [[nodiscard]] size_t size() const {return std::distance(begin_, end_);}

};

template <typename Iterator>
class Paginator {
private:
    std::vector<Page<Iterator>> pages;
public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        while(begin != end){
            pages.emplace_back(begin, std::next(begin, std::min(page_size, static_cast<size_t>(std::distance(begin, end)))));
            begin = std::next(begin, std::min(page_size, static_cast<size_t>(std::distance(begin, end))));
        }
    }

    auto begin() const {return pages.begin();}
    auto end() const {return pages.end();}

    [[nodiscard]] size_t size() const {return pages.size();}
};

template <typename C>
auto Paginate(C& c, size_t page_size){
    return Paginator(c.begin(), c.end(), page_size);
}

std::vector<size_t> form_number_pages(size_t i){

    size_t page_size = i / 4;
    i = i % 4;

    return {page_size, page_size, page_size, page_size + i};

}

int64_t CalculateSingleMatrixSum2(const vector<vector<int>>& matrix, size_t begin_row, size_t end_row){
    int64_t sum = 0;
    for(size_t i = begin_row; i < end_row; ++i){
        for(auto& item : matrix[i]){
            sum += item;
        }
    }
    return sum;
}



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
        futures.push_back(async([page] {return CalculateSingleMatrixSum(page);}));
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
    {13, 14, 15, 16},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
