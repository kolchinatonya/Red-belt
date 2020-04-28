#pragma once

#include <cstdlib>
#include <algorithm>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
    SimpleVector() : data_(nullptr), end_(nullptr), capacity_(0u), size_(0u) {}

    explicit SimpleVector(size_t size) : capacity_(size), size_(size) {
        data_ = new T[size];
        end_ = data_;
    };

    ~SimpleVector() {
        delete[] data_;
    };

    T& operator[](size_t index) {
        return data_[index];
    };

    T* begin() {
        return data_;
    }

    T* end() {
        return end_;
    };

    size_t Size() const {
        return size_;
    };

    size_t Capacity() const {
        return capacity_;
    };

    void PushBack(const T& value) {
        if (capacity_ == 0) {
            data_ = new T[1];
            end_ = data_ + 1;
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
                end_ = new_data + capacity_;
                capacity_ = new_size;
            }
            data_[size_] = value;
            size_++;
            end_ = data_ + size_;
        }
    };

private:
    T* data_;
    T* end_;
    size_t capacity_;
    size_t size_;
};
