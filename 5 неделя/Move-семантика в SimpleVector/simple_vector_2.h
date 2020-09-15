#include <cstdint>
#include <cstdio>
#include <algorithm>

using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size) : size_(size), capacity_(size) {
        data_ = new T[size];
    }

    ~SimpleVector() {
        delete[] data_;
    }

    T& operator[](size_t index) {
        if ((index + 1 <= size_) && (index  >= 0))
            return data_[index];
    }

    T* begin() {
        return data_;
    }

    T* end() {
        return data_ + size_;
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }
    void PushBack(T value) {
        if (capacity_ == 0) {
            data_ = new T[1];
            capacity_ = 1u;
            size_ = 1u;
            *data_ = move(value);
        }
        else {
            if (size_ == capacity_) {
                size_t new_size = 2 * Capacity();
                T *new_data = new T[new_size];
                move(begin(), end(), new_data);
                delete[] data_;
                data_ = new_data;
                capacity_ = new_size;
            }
            data_[size_] = move(value);
            size_++;
        }
    };



private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};
