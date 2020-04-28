#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include <exception>

using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        T* result;
        if (!deallocated_objects_.empty()) {
            result = deallocated_objects_.front();
            deallocated_objects_.pop();
            allocated_objects_.insert(result);
        }
        else {
            T* new_object = new T;
            allocated_objects_.insert(new_object);
            result = new_object;
        }
        return result;
    };

    T* TryAllocate() {
        if (deallocated_objects_.empty())
            return nullptr;
        T* result = deallocated_objects_.front();
        allocated_objects_.insert(result);
        deallocated_objects_.pop();
        return result;
    };

    void Deallocate(T* object) {
        auto it = allocated_objects_.find(object);
        if (it == allocated_objects_.end())
            throw invalid_argument("");
        deallocated_objects_.push(object);
        allocated_objects_.erase(it);
    };

    ~ObjectPool() {
        for (auto& object : allocated_objects_) {
            delete object;
        }

        while (!deallocated_objects_.empty()) {
            T* object = deallocated_objects_.front();
            deallocated_objects_.pop();
            delete object;
        }
    };

private:
    set<T*> allocated_objects_;
    queue<T*> deallocated_objects_;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}