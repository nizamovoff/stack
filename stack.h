#pragma once

#include <iostream>

template<typename ValueType>
class Stack {
public:
    explicit Stack() : size_(kDefaultSize), capacity_(kDefaultCapacity), array_(new ValueType[kDefaultCapacity]) {}

    ~Stack() {
        delete[] array_;
    }

    Stack(const Stack& other) {
        Copy(other);
    }

    Stack& operator=(const Stack& other) {
        if (this == &other) {
            return *this;
        }

        Copy(other);
        return *this;
    }

    Stack(Stack&& other) noexcept : size_(other.size_), capacity_(other.capacity_), array_(other.array_) {
        MakeDefault(*&other);
    }

    Stack& operator=(Stack&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete[] array_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        array_ = other.array_;

        MakeDefault(*&other);
        return *this;
    }

    ValueType Top() const {
        if (size_ == 0) {
            // return signal 11: SIGSEGV
            exit(139);
        }
        return array_[size_ - 1];
    }

    bool Empty() const {
        return size_ == 0;
    }

    size_t Size() const {
        return size_;
    }

    void Clear() {
        delete[] array_;
        MakeDefault(*this);
    }

    void Push(const ValueType value) {
        if (size_ >= capacity_) {
            AddMemory();
        }
        array_[size_++] = value;
    }

    void Pop() {
        if (size_ == 0) {
            // return signal 11: SIGSEGV
            exit(139);
        }
        --size_;
    }

    void Swap(Stack& other) {
        std::swap(*this, other);
    }

private:
    const size_t kDefaultSize = 0;
    const size_t kDefaultCapacity = 1;

    size_t size_ = kDefaultSize;
    size_t capacity_ = kDefaultCapacity;
    ValueType* array_ = nullptr;

    void AddMemory(size_t new_capacity = 0) {
        if (new_capacity == 0) {
            new_capacity = capacity_ * 2;
        }

        ValueType* old_array = array_;
        array_ = new ValueType[new_capacity];

        for (size_t i = 0; i < size_; ++i) {
            array_[i] = old_array[i];
        }

        capacity_ = new_capacity;
        delete[] old_array;
    }

    void Copy(const Stack& other) {
        AddMemory(other.capacity_);
        size_ = other.size_;
        for (size_t i = 0; i < size_; ++i) {
            array_[i] = other.array_[i];
        }
    }

    void MakeDefault(Stack& other) noexcept {
        other.size_ = kDefaultSize;
        other.capacity_ = kDefaultCapacity;
        other.array_ = nullptr;
    }
};