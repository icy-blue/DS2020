/**
	Created by Huang Jingcheng on 2020/9/23.
	201905130198@mail.sdu.edu.cn
*/


#ifndef DS2020_PRIORITYQUEUE_H
#define DS2020_PRIORITYQUEUE_H

#include <vector>
#include <functional>

template<typename T>
class PriorityQueue {
    int _size = 0;
    std::vector<T> _data;
    bool lambda;
    std::function<bool(T &a, T &b)> _cmp;

    bool (*_cmpFun)(T &a, T &b);

    void adjustHeap();

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
    data.push_back(data);

}

template<typename T>
void PriorityQueue<T>::pop() {
    _size--;
}

template<typename T>
bool PriorityQueue<T>::isEmpty() {
    return _size == 0;
}

template<typename T>
T PriorityQueue<T>::top() {
    if (_size == 0) return nullptr;
    return _data[0];
}

template<typename T>
int PriorityQueue<T>::size() {
    return this->_size;
}

template<typename T>
void PriorityQueue<T>::adjustHeap() {

}

#endif //DS2020_PRIORITYQUEUE_H
