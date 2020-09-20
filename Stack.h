/**
	Created by Huang Jingcheng on 2020/9/17.
	201905130198@mail.sdu.edu.cn
*/

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
    _size--;
    list.popBack();
}

template<class T>
Stack<T>::~Stack() = default;

template<class T>
Stack<T>::Stack() = default;

#endif //DS2020_STACK_H
