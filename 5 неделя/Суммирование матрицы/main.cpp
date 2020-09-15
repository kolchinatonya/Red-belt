#include "test_runner.h"
#include <vector>
#include <future>
#include <numeric>

using namespace std;

template<typename Iterator>
class IteratorRange {
private:
    Iterator first, last;
public:
    IteratorRange(Iterator f, Iterator l) : first(f), last(l) {}

    auto begin() const { return first; }

    auto end() const { return last; }

    size_t size() const { return last - first; }
};

template <typename It>
class Paginator {
private:
    vector<IteratorRange<It>> pages;
public:
    Paginator(It begin, It end, size_t page_size) {
        for (size_t left = distance(begin, end); left > 0; ) {
            size_t current_page_size = min(page_size, left);
            It current_page_end = next(begin, current_page_size);
            pages.push_back({begin, current_page_end});

            left -= current_page_size;
            begin = current_page_end;
        }
    }

    auto begin() const { return pages.begin(); }
    auto end() const { return pages.end(); }
    size_t size() const { return pages.size(); }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {3
    return Paginator(c.begin(), c.end(), page_size);
}

template <typename ContainerOfVectors>
int64_t SumSingleThread(const ContainerOfVectors& matrix) {
    int64_t sum = 0;
    for (const auto& row : matrix) {
        for (auto item : row) {
            sum += item;
        }
    }
    return sum;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    vector<future<int64_t>> futures;
    for (auto page : Paginate(matrix, 2000)) {
        futures.push_back(async([=] { return SumSingleThread(page); }));
    }
    int64_t result = 0;
    for (auto& f : futures) {
        result += f.get();
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
