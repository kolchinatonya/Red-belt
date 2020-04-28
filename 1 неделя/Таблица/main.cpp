#include "test_runner.h"

using namespace std;

template <typename T>
class Table {
private:
    vector<vector<T>> _table;
    size_t _lines_count;
    size_t _columns_count;

public:
    Table(const size_t& lines_count, const size_t& columns_count) :_lines_count(lines_count), _columns_count(columns_count) {
        _table = vector<vector<T>>(_lines_count);
        for (auto& line : _table)
            line = vector<T>(columns_count);
    }

    vector<T>& operator[](const size_t& index) {
        return _table[index];
    }

    const vector<T>& operator[](const size_t& index) const {
        return _table[index];
    }

    void Resize(const size_t& new_lines_count, const size_t& new_columns_count)
    {
        _lines_count = new_lines_count;
        _columns_count = new_columns_count;
        _table.resize(new_lines_count);
        for (auto& line : _table)
            line.resize(new_columns_count);
    }

    pair<size_t, size_t> Size() const {
        return make_pair(_lines_count, _columns_count);
    }

};

void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
