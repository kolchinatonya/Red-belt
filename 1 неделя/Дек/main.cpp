//#include "test_runner.h"

#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Deque {
public:
    Deque() {
        front.resize(0);
        back.resize(0);
    }

    bool Empty() const{
        return front.empty() && back.empty();
    }

    size_t Size() const{
        return front.size() + back.size();
    }

    T& operator [](const size_t& index) {
        return At(index);
    }

    const T& operator [](const size_t& index) const {
        return At(index);
    }

    T& At(const size_t& index) {
        if (index < front.size()) {
            return front[front.size() - 1 - index];
        } else if (index - front.size() < back.size()) {
            return back[index - front.size()];
        } else {
            throw out_of_range("Tried to access out of range element");
        }
    }

    const T& At(const size_t& index) const {
        return At(index);
    }

    const T& Front() const {
        if (!front.empty())
            return front.back();
        if (!back.empty())
            return back.front();
        throw out_of_range("Tried to access out of range element");
    }

    T& Front() {
        if (!front.empty())
            return front.back();
        if (!back.empty())
            return back.front();
        throw out_of_range("Tried to access out of range element");
    }

    const T& Back() const {
        if (!back.empty())
            return back.back();
        if (!front.empty())
            return front.front();
        throw out_of_range("Tried to access out of range element");
    }

    T& Back() {
        if (!back.empty())
            return back.back();
        if (!front.empty())
            return front.front();
        throw out_of_range("Tried to access out of range element");
    }

    void PushFront(const T& element) {
        front.push_back(element);
    }

    void PushBack(const T& element) {
        back.push_back(element);
    }

private:
    vector<T> front;
    vector<T> back;
};

//void TestEmpty() {
//    Deque<int> dq;
//    ASSERT(dq.Empty());
//}
//
//void TestPush() {
//    Deque<int> dq;
//    dq.PushBack(2);
//    dq.PushFront(1);
//    ASSERT(!dq.Empty());
//}
//
//void TestSize() {
//    Deque<int> dq;
//    dq.PushBack(2);
//    dq.PushFront(1);
//    ASSERT_EQUAL(dq.Size(), 2u);
//}
//
//void TestFront() {
//    Deque<int> dq;
//    dq.PushFront(1);
//    ASSERT_EQUAL(dq.Front(), 1);
//
//    dq.Front() = 0;
//    ASSERT_EQUAL(dq.Front(), 0);
//}
//
//void TestBack() {
//    Deque<int> dq;
//    dq.PushBack(1);
//    ASSERT_EQUAL(dq.Back(), 1);
//
//    dq.Back() = 0;
//    ASSERT_EQUAL(dq.Back(), 0);
//}
//
//void TestOperator() {
//    // front и back имеют элементы
//    Deque<int> dq_of_int;
//    dq_of_int.PushFront(1);
//    dq_of_int.PushFront(2);
//    dq_of_int.PushFront(3);
//    dq_of_int.PushBack(4);
//    dq_of_int.PushBack(5);
//    ASSERT_EQUAL(dq_of_int[0], 3);
//    ASSERT_EQUAL(dq_of_int[1], 2);
//    ASSERT_EQUAL(dq_of_int[2], 1);
//    ASSERT_EQUAL(dq_of_int[3], 4);
//    ASSERT_EQUAL(dq_of_int[4], 5);
//
//    // front имеет элементы, back – пуст
//    Deque<double> dq_of_db;
//    dq_of_db.PushFront(1.5);
//    dq_of_db.PushFront(2.5);
//    dq_of_db.PushFront(3.5);
//    ASSERT_EQUAL(dq_of_db[0], 3.5);
//    ASSERT_EQUAL(dq_of_db[1], 2.5);
//    ASSERT_EQUAL(dq_of_db[2], 1.5);
//
//    // back имеет элементы, front – пуст
//    Deque<char> dq_of_ch;
//    dq_of_ch.PushBack('a');
//    dq_of_ch.PushBack('b');
//    ASSERT_EQUAL(dq_of_ch[0], 'a');
//}
//
//void TestAt() {
//    // front и back имеют элементы
//    Deque<int> dq_of_int;
//    dq_of_int.PushFront(1);
//    dq_of_int.PushFront(2);
//    dq_of_int.PushFront(3);
//    dq_of_int.PushBack(4);
//    dq_of_int.PushBack(5);
//    ASSERT_EQUAL(dq_of_int.At(0), 3);
//    ASSERT_EQUAL(dq_of_int.At(1), 2);
//    ASSERT_EQUAL(dq_of_int.At(2), 1);
//    ASSERT_EQUAL(dq_of_int.At(3), 4);
//    ASSERT_EQUAL(dq_of_int.At(4), 5);
//
//    // front имеет элементы, back – пуст
//    Deque<double> dq_of_db;
//    dq_of_db.PushFront(1.5);
//    dq_of_db.PushFront(2.5);
//    dq_of_db.PushFront(3.5);
//    ASSERT_EQUAL(dq_of_db.At(0), 3.5);
//    ASSERT_EQUAL(dq_of_db.At(1), 2.5);
//    ASSERT_EQUAL(dq_of_db.At(2), 1.5);
//
//    try {
//        dq_of_db.At(3);
//    } catch (const out_of_range& ex) {
//        bool exception_caught = true;
//        ASSERT(exception_caught);
//    }
//
//    // back имеет элементы, front – пуст
//    Deque<char> dq_of_ch;
//    dq_of_ch.PushBack('a');
//    dq_of_ch.PushBack('b');
//    ASSERT_EQUAL(dq_of_ch.At(0), 'a');
//}
//
//
//void TestDop() {
//    Deque<string> d;
//    d.PushBack("A");
//    ASSERT_EQUAL(d.Front(), "A");
//    ASSERT_EQUAL(d.Back(), "A");
//}
//
//int main() {
//    TestRunner tr;
//    RUN_TEST(tr, TestEmpty);
//    RUN_TEST(tr, TestPush);
//    RUN_TEST(tr, TestSize);
//    RUN_TEST(tr, TestFront);
//    RUN_TEST(tr, TestBack);
//    RUN_TEST(tr, TestOperator);
//    RUN_TEST(tr, TestAt);
//    RUN_TEST(tr, TestDop);
//    return 0;
//}