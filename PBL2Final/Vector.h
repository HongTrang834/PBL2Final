#pragma once

#include <stdexcept> // For std::out_of_range

template<typename T>

class Vector {

private:

    T* elements;      // Pointer to the elements in the vector

    size_t capacity;  // Total capacity of the allocated array

    size_t count;     // Number of elements currently in the vector

public:

    class Iterator {

    public:

        Iterator(T* ptr) : ptr_(ptr) {}

        T& operator*() const { return *ptr_; }



        Iterator& operator++() {

            ptr_++;

            return *this;

        }

        bool operator!=(const Iterator& other) const {

            return ptr_ != other.ptr_;

        }

        // Thêm các toán t? khác n?u c?n

    private:

        T* ptr_;

    };

    Iterator begin() {

        return Iterator(elements); // gi? s? data_ là tên m?ng ch?a các ph?n t?

    }

    Iterator end() {

        return Iterator(elements + count); // gi? s? size_ là s? ph?n t? trong vector

    }

    // Default constructor

    Vector() : elements(nullptr), capacity(0), count(0) {}

    // Destructor

    ~Vector() {

        delete[] elements;

    }

    // Copy constructor

    Vector(const Vector& other) : capacity(other.capacity), count(other.count) {

        elements = new T[capacity];

        for (size_t i = 0; i < count; ++i) {

            elements[i] = other.elements[i];

        }

    }



    // Assignment operator

    Vector& operator=(const Vector& other) {

        if (this != &other) {

            delete[] elements;

            capacity = other.capacity;

            count = other.count;

            elements = new T[capacity];

            for (size_t i = 0; i < count; ++i) {

                elements[i] = other.elements[i];

            }

        }

        return *this;

    }

    // Function to add an element to the end of the vector

    void push_back(const T& value) {

        if (count >= capacity) {

            // Allocate more space

            size_t newCapacity = capacity == 0 ? 1 : capacity * 2;

            T* newElements = new T[newCapacity];

            for (size_t i = 0; i < count; ++i) {

                newElements[i] = elements[i];

            }

            delete[] elements;

            elements = newElements;

            capacity = newCapacity;

        }

        elements[count++] = value;

    }

    // Function to remove an element from the end of the vector

    void pop_back() {

        if (count > 0) {

            --count;

        }

    }

    // Function to get the number of elements in the vector

    size_t size() const {

        return count;

    }

    // Function to access elements in the vector with bounds checking

    T& at(size_t index) {

        if (index >= count) {

            throw std::out_of_range("Index out of range");

        }

        return elements[index];

    }

    // Const variant of at() for const correctness

    const T& at(size_t index) const {

        if (index >= count) {

            throw std::out_of_range("Index out of range");

        }

        return elements[index];

    }



    // Operator to access elements without bounds checking

    T& operator[](size_t index) {

        return elements[index];

    }



    // Const variant of operator[] for const correctness

    const T& operator[](size_t index) const {

        return elements[index];

    }



    // Function to check if the vector is empty

    bool empty() const {

        return size() == 0;

    }

    // Function to clear the vector

    void clear() {

        count = 0;

    }
    template <typename... Args>

    void emplace_back(Args&&... args) {

        if (count >= capacity) {

            // Allocate more space

            size_t newCapacity = capacity == 0 ? 1 : capacity * 2;

            T* newElements = new T[newCapacity];

            for (size_t i = 0; i < count; ++i) {

                newElements[i] = elements[i]; // Copy existing elements

            }

            delete[] elements; // Delete old array

            elements = newElements;

            capacity = newCapacity;

        }

        // Construct the new element in place at the end of the currently used space

        new(&elements[count]) T(std::forward<Args>(args)...);

        ++count;

    }

    // Function to get a reference to the last element in the vector

    T& back() {

        if (count == 0) {

            throw std::out_of_range("Vector is empty");

        }

        return elements[count - 1];

    }
    T& front() {

        if (empty()) {

            throw std::out_of_range("Cannot access front of an empty vector.");

        }

        return elements[0];

    }

    // Const variant of front() for const correctness

    const T& front() const {

        if (empty()) {

            throw std::out_of_range("Cannot access front of an empty vector.");

        }

        return elements[0];

    }

};

