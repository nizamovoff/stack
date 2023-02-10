#pragma once

#include <iostream>

template<typename ValueType>
class Stack {
public:
    explicit Stack();

    ~Stack();

    Stack(const Stack& other);

    Stack& operator=(const Stack& other);

    Stack(Stack&& other) noexcept;

    Stack& operator=(Stack&& other) noexcept;

    ValueType Top() const;

    bool Empty() const;

    size_t Size() const;

    void Clear();

    void Push(const ValueType value);

    void Pop();

    void Swap(Stack& other);

private:
    const size_t kDefaultSize = 0;
    const size_t kDefaultCapacity = 0;
    static const size_t kDoubleCapacity = -1;

    size_t size_ = kDefaultSize;
    size_t capacity_ = kDefaultCapacity;
    ValueType* array_ = nullptr;

    void AddMemory(size_t new_capacity = kDoubleCapacity);

    void Copy(const Stack& other);

    void MakeDefault(Stack& other) noexcept;
};

template<typename ValueType>
Stack<ValueType>::Stack() : size_(kDefaultSize), capacity_(kDefaultCapacity), array_(nullptr) {}

template<typename ValueType>
Stack<ValueType>::~Stack() {
    delete[] array_;
}

template<typename ValueType>
Stack<ValueType>::Stack(const Stack &other) {
    Copy(other);
}

template<typename ValueType>
Stack<ValueType> &Stack<ValueType>::operator=(const Stack &other) {
    if (this == &other) {
        return *this;
    }

    Copy(other);
    return *this;
}

template<typename ValueType>
Stack<ValueType>::Stack(Stack &&other) noexcept : size_(other.size_), capacity_(other.capacity_), array_(other.array_) {
    MakeDefault(*&other);
}

template<typename ValueType>
Stack<ValueType> &Stack<ValueType>::operator=(Stack &&other) noexcept {
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

template<typename ValueType>
ValueType Stack<ValueType>::Top() const {
    if (size_ == 0) {
        // return signal 11: SIGSEGV
        exit(139);
    }
    return array_[size_ - 1];
}

template<typename ValueType>
bool Stack<ValueType>::Empty() const {
    return size_ == 0;
}

template<typename ValueType>
size_t Stack<ValueType>::Size() const {
    return size_;
}

template<typename ValueType>
void Stack<ValueType>::Clear() {
    delete[] array_;
    MakeDefault(*this);
}

template<typename ValueType>
void Stack<ValueType>::Push(const ValueType value) {
    if (size_ >= capacity_) {
        AddMemory();
    }
    array_[size_++] = value;
}

template<typename ValueType>
void Stack<ValueType>::Pop() {
    if (size_ == 0) {
        // return signal 11: SIGSEGV
        exit(139);
    }
    --size_;
}

template<typename ValueType>
void Stack<ValueType>::Swap(Stack &other) {
    std::swap(*this, other);
}

template<typename ValueType>
void Stack<ValueType>::AddMemory(size_t new_capacity) {
    if (new_capacity == kDoubleCapacity) {
        new_capacity = (capacity_ == 0 ? 1 : capacity_ * 2);
    }

    ValueType *old_array = array_;
    array_ = new ValueType[new_capacity];

    for (size_t i = 0; i < size_; ++i) {
        array_[i] = old_array[i];
    }

    capacity_ = new_capacity;
    delete[] old_array;
}

template<typename ValueType>
void Stack<ValueType>::Copy(const Stack &other) {
    AddMemory(other.capacity_);
    size_ = other.size_;
    for (size_t i = 0; i < size_; ++i) {
        array_[i] = other.array_[i];
    }
}

template<typename ValueType>
void Stack<ValueType>::MakeDefault(Stack &other) noexcept {
    other.size_ = kDefaultSize;
    other.capacity_ = kDefaultCapacity;
    other.array_ = nullptr;
}