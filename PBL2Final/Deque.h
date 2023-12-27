#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class Deque {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node* frontNode;
    Node* backNode;
    std::size_t size;

public:
    Deque() : frontNode(nullptr), backNode(nullptr), size(0) {}

    ~Deque() {
        clear();
    }

    void push_front(const T& val) {
        Node* newNode = new Node(val);
        if (empty()) {
            frontNode = backNode = newNode;
        }
        else {
            newNode->next = frontNode;
            frontNode->prev = newNode;
            frontNode = newNode;
        }
        size++;
    }

    void push_back(const T& val) {
        Node* newNode = new Node(val);
        if (empty()) {
            frontNode = backNode = newNode;
        }
        else {
            newNode->prev = backNode;
            backNode->next = newNode;
            backNode = newNode;
        }
        size++;
    }

    void pop_front() {
        if (!empty()) {
            Node* temp = frontNode;
            frontNode = frontNode->next;
            if (frontNode) {
                frontNode->prev = nullptr;
            }
            else {
                backNode = nullptr;
            }
            delete temp;
            size--;
        }
    }

    void pop_back() {
        if (!empty()) {
            Node* temp = backNode;
            backNode = backNode->prev;
            if (backNode) {
                backNode->next = nullptr;
            }
            else {
                frontNode = nullptr;
            }
            delete temp;
            size--;
        }
    }

    const T& front() const {
        if (!empty()) {
            return frontNode->data;
        }
        throw std::out_of_range("Deque is empty");
    }

    const T& back() const {
        if (!empty()) {
            return backNode->data;
        }
        throw std::out_of_range("Deque is empty");
    }

    std::size_t getSize() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }
};
