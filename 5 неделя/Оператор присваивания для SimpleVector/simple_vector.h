#pragma once

#include <cstdlib>
#include <algorithm>

using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() : data_(nullptr), capacity_(0u), size_(0u) {}

    explicit SimpleVector(size_t size) : capacity_(size), size_(size) {
        data_ = new T[size];
    };

    SimpleVector(const SimpleVector& other) : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        copy(other.begin(), other.end(), begin());
    }

    ~SimpleVector() {
        delete[] data_;
    };


    void operator=(const SimpleVector& rhs) {
        if (rhs.size_ <= capacity_) {
            copy(rhs.begin(), rhs.end(), begin());
            size_ = rhs.size_;
        } else {
            SimpleVector<T> tmp(rhs);
            swap(tmp.data_, data_);
            swap(tmp.size_, size_);
            swap(tmp.capacity_, capacity_);
        }
    }


    T& operator[](size_t index) {
        return data_[index];
    };

    T* begin() {
        return data_;
    }

    T* end() {
        return data_ + size_;
    };

    const T* begin() const {
        return data_;
    }

    const T* end() const {
        return data_ + size_;
    }

    size_t Size() const {
        return size_;
    };

    size_t Capacity() const {
        return capacity_;
    };


    void PushBack(const T& value) {
        if (capacity_ == 0) {
            data_ = new T[1];
            capacity_ = 1u;
            size_ = 1u;
            *data_ = value;
        }
        else {
            if (size_ == capacity_) {
                size_t new_size = 2 * Capacity();
                T *new_data = new T[new_size];
                std::copy(begin(), end(), new_data);
                delete[] data_;
                data_ = new_data;
                capacity_ = new_size;
            }
            data_[size_] = value;
            size_++;
        }
    };

private:
    T* data_;
    size_t capacity_;
    size_t size_;
};
