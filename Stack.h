//
// Created by icy on 2020/9/17.
//

#ifndef DS2020_STACK_H
#define DS2020_STACK_H

#include "LinkedList.h"

template<class T>
class Stack {
private:
    LinkedList<T> list;
    int _size = 0;
public:
    bool isEmpty() const;

    T top() const;

    int size() const;

    void push(T element);

    void pop();

    Stack();

    ~Stack();
};

#endif //DS2020_STACK_H
