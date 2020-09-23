/**
	Created by Huang Jingcheng on 2020/9/23.
	201905130198@mail.sdu.edu.cn
*/


#ifndef DS2020_PRIORITYQUEUE_H
#define DS2020_PRIORITYQUEUE_H

#include <vector>
#include <functional>
#include "Stack.h"
#include <cstdlib>

template<typename T>
class PriorityQueue {
    int _size = 0;
    std::vector<T> _data;
    bool lambda;
    std::function<bool(T &a, T &b)> _cmp;

    bool (*_cmpFun)(T &a, T &b);

    bool getCmp(T &a, T &b);


public:
    void push(T data);

    void pop();

    bool isEmpty();

    T top();

    int size();

    PriorityQueue(std::function<bool(T &a, T &b)> cmp = [](T &a, T &b) -> bool { return a < b; }) {
        this->_cmp = cmp;
        this->lambda = true;
    }

    PriorityQueue(bool (*cmpFun)(T &a, T &b)) {
        this->_cmpFun = cmpFun;
        this->lambda = false;
    }
};

template<typename T>
void PriorityQueue<T>::push(T data) {
    _size++;
    _data.push_back(data);
    Stack<unsigned int> stack;
    stack.push(_size - 1);
    while (!stack.isEmpty()) {
        unsigned int x = stack.top();
        stack.pop();
        if (x == 0) continue;
        int tmp = ((x + 1) >> 1) - 1;
        if (getCmp(_data[tmp], _data[x])) {
            std::swap(_data[tmp], _data[x]);
            stack.push(tmp);
        }
    }
}

template<typename T>
void PriorityQueue<T>::pop() {

    std::swap(_data[0], _data[_size - 1]);
    _data.pop_back();
    _size--;
    Stack<unsigned int> stack;
    stack.push(0);
    while (!stack.isEmpty()) {
        unsigned int x = stack.top();
        stack.pop();
        if (x >= _size) continue;
        int tmp = ((x + 1) << 1) - 1;
        if (tmp < _size and getCmp(_data[x], _data[tmp])) {
            std::swap(_data[tmp], _data[x]);
            stack.push(tmp);
        }
        if (tmp + 1 < _size and getCmp(_data[x], _data[tmp + 1])) {
            std::swap(_data[tmp + 1], _data[x]);
            stack.push(tmp + 1);
        }
    }
}

template<typename T>
bool PriorityQueue<T>::isEmpty() {
    return _size == 0;
}

template<typename T>
T PriorityQueue<T>::top() {
    return _data[0];
}

template<typename T>
int PriorityQueue<T>::size() {
    return this->_size;
}

template<typename T>
bool PriorityQueue<T>::getCmp(T &a, T &b) {
    if (lambda) return _cmp(a, b);
    return _cmpFun(a, b);
}

#endif //DS2020_PRIORITYQUEUE_H
