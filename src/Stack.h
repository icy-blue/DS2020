/**
 * Created by Clion.
 * User: icy
 * Date: 2020/9/21
 * i@icys.top
 */

#ifndef DS2020_STACK_H
#define DS2020_STACK_H

#include "DoubleLinkedList.h"

template<typename T>
class Stack {
private:
    DoubleLinkedList<T> list;
    int _size = 0;
public:
    bool isEmpty() const;

    T top();

    int size() const;

    void push(T element);

    void pop();

    Stack();

    ~Stack();
};

template<typename T>
bool Stack<T>::isEmpty() const {
    return this->_size == 0;
}

template<typename T>
T Stack<T>::top() {
    return list.rbegin().get();
}

template<typename T>
int Stack<T>::size() const {
    return this->_size;
}

template<typename T>
void Stack<T>::push(T element) {
    _size++;
    list.pushBack(element);
}

template<typename T>
void Stack<T>::pop() {
    _size--;
    list.popBack();
}

template<typename T>
Stack<T>::~Stack() = default;

template<typename T>
Stack<T>::Stack() = default;

#endif //DS2020_STACK_H
