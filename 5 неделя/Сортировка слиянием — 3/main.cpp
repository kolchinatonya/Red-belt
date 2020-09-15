#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    int count = range_end - range_begin;
    if (count < 3)
        return;
    vector<typename RandomIt::value_type> v(make_move_iterator(range_begin), make_move_iterator(range_end));
//    RandomIt part1 = v.begin() + count / 3;
//    RandomIt part2 = v.begin() + 2 * count / 3;
    MergeSort(move(v.begin()), move(v.begin() + count / 3));
    MergeSort(move(v.begin() + count / 3), move(v.begin() + 2 * count / 3));
    MergeSort(move(v.begin() + 2 * count / 3), move(v.end()));
    vector<typename RandomIt::value_type> temp;
    merge(make_move_iterator(v.begin()), make_move_iterator(v.begin() + count / 3), make_move_iterator(v.begin() + count / 3), make_move_iterator(v.begin() + 2 * count / 3), back_inserter(temp));
    merge(make_move_iterator(temp.begin()), make_move_iterator(temp.end()), make_move_iterator(v.begin() + 2 * count / 3), make_move_iterator(v.end()), range_begin);
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    for (const auto& n : numbers)
        cout << n << " ";
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
