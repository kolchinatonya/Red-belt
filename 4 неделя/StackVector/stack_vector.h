#pragma once

#include <stdexcept>
#include <array>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) {
        if (a_size > N)
            throw invalid_argument("Invalid vector size!");
        size = a_size;
    };

    T& operator[](size_t index) {
        return ar[index];
    }
    const T& operator[](size_t index) const {
        return ar[index];
    }

    T* begin() {
        return ar.begin();
    };

    T* end() {
        return ar.begin() + size;
    };

    const T* begin() const {
        return ar.cbegin();
    };

    const T* end() const {
        return ar.cbegin() + size;
    };

    size_t Size() const {
        return size;
    };

    size_t Capacity() const {
        return N;
    };

    void PushBack(const T& value) {
        if (size < N) {
            ar[size++] = value;
        }
        else
            throw overflow_error("");

    };

    T PopBack() {
        if (size == 0)
            throw underflow_error("");
        return ar[--size];
    };

private:
    array<T, N> ar;
    size_t size = 0;
};

