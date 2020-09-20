//
// Created by icy on 2020/9/17.
//

#include "Stack.h"

template<class T>
bool Stack<T>::isEmpty() const {
    return list.isEmpty();
}

template<class T>
T Stack<T>::top() const {
    return list.get(0);
}

template<class T>
int Stack<T>::size() const {
    return this->_size;
}

template<class T>
void Stack<T>::push(T element) {
    _size++;
    list.pushBack(element);
}

template<class T>
void Stack<T>::pop() {
    list.popBack();
}

template<class T>
Stack<T>::~Stack() {
    delete list;
}

template<class T>
Stack<T>::Stack() = default;
