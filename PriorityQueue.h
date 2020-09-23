/**
  * Created by Huang Jingcheng on 2020/9/23.
  * 201905130198@mail.sdu.edu.cn
*/


#ifndef DS2020_PRIORITYQUEUE_H
#define DS2020_PRIORITYQUEUE_H

#include <vector>
#include <functional>
#include "Stack.h"
#include <cstdlib>
#include "sort.h"

template<typename T>
class PriorityQueue {
    unsigned int _size = 0;
    std::vector<T> _data;
    std::function<bool(T &a, T &b)> _cmp;


public:
    void push(T data);

    void pop();

    bool isEmpty();

    T top();

    int size();

    void resetCmp(std::function<bool(T &a, T &b)> cmp = [](T &a, T &b) -> bool { return a < b; }) {
        this->_cmp = cmp;
        Algorithm<T>::sort(_data.begin(), _data.end(), _cmp);
    }

    explicit PriorityQueue(std::function<bool(T &a, T &b)> cmp = [](T &a, T &b) -> bool { return a < b; }) {
        this->_cmp = cmp;
    }
};

template<typename T>
void PriorityQueue<T>::push(T data) {
    _size++;
    _data.push_back(data);
    Stack<unsigned int> stack;
    if (_size > 1) stack.push(_size - 1);
    while (!stack.isEmpty()) {
        unsigned int x = stack.top();
        stack.pop();
        unsigned int tmp = ((x + 1u) >> 1u) - 1;
        if (_cmp(_data[tmp], _data[x])) {
            std::swap(_data[tmp], _data[x]);
            if (tmp > 0) stack.push(tmp);
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
        unsigned int tmp = ((x + 1u) << 1u) - 1u;
        int cnt = 0;
        if (tmp < _size and _cmp(_data[x], _data[tmp])) {
            std::swap(_data[tmp], _data[x]);
            if (tmp < _size) stack.push(tmp), cnt++;

        }
        if (tmp + 1 < _size and _cmp(_data[x], _data[tmp + 1])) {
            std::swap(_data[tmp + 1], _data[x]);
            if (tmp + 1 < _size) stack.push(tmp + 1), cnt++;
        }
        if (cnt == 2) {
            std::swap(_data[tmp + 1], _data[tmp]);
            x = stack.top();
            stack.pop();
            stack.pop();
            stack.push(x);
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

#endif //DS2020_PRIORITYQUEUE_H
