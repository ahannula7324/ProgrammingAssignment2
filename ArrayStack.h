//
// Created by Drew Hannula on 3/19/26.
//

#ifndef PROGRAMMINGASSIGNMENT2_AARAYSTACK_H
#define PROGRAMMINGASSIGNMENT2_AARAYSTACK_H

#include <vector>
#include <stdexcept>

template <typename T>
class ArrayStack {
private:
    std::vector<T> data;

public:

    void push(const T& value) {
        data.push_back(value);
    }

    void pop() {
        if (data.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        data.pop_back();
    }

    T top() const {

    }

    bool empty() const {
        return data.empty();

    }

    int size() const {

    }
};

#endif