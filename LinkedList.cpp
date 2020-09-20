/**
	Created by Huang Jingcheng on 2020/9/9.
	201905130198@mail.sdu.edu.cn
*/

#include <iostream>
#include "LinkedList.h"

template<typename T>
LinkedList<T>::iterator::iterator(LinkedList::Node *pos, LinkedList<T> *parent) {
    this->pos = pos;
    this->parent = parent;
}

template<typename T>
void LinkedList<T>::iterator::operator++(int) {
    if (hasNext())next();
}

template<typename T>
void LinkedList<T>::iterator::operator++() {
    if (hasNext())next();
}

template<typename T>
void LinkedList<T>::iterator::operator--(int) {
    if (hasNext())next();
}

template<typename T>
void LinkedList<T>::iterator::operator--() {
    if (hasPre())pre();
}

template<typename T>
bool LinkedList<T>::iterator::operator==(const LinkedList::iterator &r) const {
    return this->pos == r.pos;
}

template<typename T>
bool LinkedList<T>::iterator::operator!=(const LinkedList::iterator &r) const {
    return this->pos != r.pos;
}

template<typename T>
T LinkedList<T>::iterator::operator*() const {
    return this->pos->data;
}

template<typename T>
bool LinkedList<T>::iterator::hasNext() const {
    return pos->next != nullptr;
}

template<typename T>
bool LinkedList<T>::iterator::hasPre() const {
    return pos->prev != nullptr;
}

template<typename T>
void LinkedList<T>::iterator::next() {
    pos = pos->next;
}

template<typename T>
void LinkedList<T>::iterator::pre() {
    pos = pos->prev;
}

template<typename T>
T LinkedList<T>::iterator::get() const {
    return pos->data;
}

template<typename T>
void LinkedList<T>::iterator::insertBefore(T data) {
    if (pos == parent->head)
        parent->pushFront(data);
    else
        parent->insertBehind(pos->prev, data);
}

template<typename T>
void LinkedList<T>::iterator::insertBehind(T data) {
    parent->insertBehind(pos, data);
}

template<typename T>
void LinkedList<T>::iterator::remove() {
    if (hasNext()) {
        next();
        Node *node = this->pos->prev;
        parent->delNode(node);
    } else if (hasPre()) {
        pre();
        Node *node = this->pos->next;
        parent->delNode(node);
    } else {
        parent->delNode(this->pos);
    }
}

template<typename T>
void LinkedList<T>::iterator::set(T element) {
    pos->data = element;
}

template<typename T>
LinkedList<T>::Node::Node(T &data) {
    this->prev = nullptr;
    this->next = nullptr;
    this->data = data;
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::getNode(int index) const {
    if (isEmpty()) return nullptr;
    for (Node *it = head; it != nullptr; it = it->next) {
        if (index-- == 0) return it;
    }
    return nullptr;
}

template<typename T>
void LinkedList<T>::delNode(LinkedList::Node *node) {
    if (node == nullptr) return;
    if (node->prev != nullptr) {
        node->prev->next = node->next;
    } else {
        head = node->next;
    }
    if (node->next != nullptr) {
        node->next->prev = node->prev;
    } else {
        tail = node->prev;
    }
    delete node;
}

template<typename T>
void LinkedList<T>::insertBehind(LinkedList::Node *node, T element) {
    Node *newNode = new Node(element);
    if (node->next == nullptr) {
        tail = newNode;
    } else {
        Node *nxt = node->next;
        nxt->prev = newNode;
        newNode->next = nxt;
    }
    newNode->prev = node;
    node->next = newNode;
}

template<typename T>
void LinkedList<T>::pushFront(T element) {
    Node *node = new Node(element);
    node->next = head;
    if (isEmpty()) tail = node;
    else head->prev = node;
    head = node;
}

template<typename T>
void LinkedList<T>::pushBack(T element) {
    Node *node = new Node(element);
    node->prev = tail;
    if (isEmpty()) head = node;
    else tail->next = node;
    tail = node;
}

template<typename T>
T LinkedList<T>::get(int index) const {
    return getNode(index)->data;
}

template<typename T>
void LinkedList<T>::deleteElement(int index) {
    Node *node = getNode(index);
    delNode(node);
}

template<typename T>
bool LinkedList<T>::isEmpty() const {
    return head == nullptr and tail == nullptr;
}

template<typename T>
void LinkedList<T>::print() {
    forEach([](T &x) -> void { std::cout << x << " "; }, true);
    std::cout << " reverse: ";
    forEach([](T &x) -> void { std::cout << x << " "; }, false);
    std::cout << std::endl;
}

template<typename T>
void LinkedList<T>::insertBehind(int index, T element) {
    if (index == -1) {
        pushFront(element);
        return;
    }
    Node *pre = getNode(index);
    insertBehind(pre, element);
}

template<typename T>
void LinkedList<T>::insertBefore(int index, T element) {
    insertBehind(index - 1, element);
}

template<typename T>
void LinkedList<T>::forEach(const std::function<void(T &)> &func, bool front) {
    if (front) {
        for (Node *it = head; it != nullptr; it = it->next) {
            func(it->data);
        }
    } else {
        for (Node *it = tail; it != nullptr; it = it->prev) {
            func(it->data);
        }
    }
}

template<typename T>
int LinkedList<T>::ifRemove(const std::function<bool(T &)> &func, bool front) {
    int cnt = 0;
    if (front) {
        for (Node *it = head; it != nullptr;) {
            if (func(it->data)) {
                if (it->next != nullptr) {
                    it = it->next;
                    delNode(it->prev);
                } else {
                    delNode(it);
                    break;
                }
                cnt++;
            } else it = it->next;
        }
    } else {
        for (Node *it = tail; it != nullptr;) {
            if (func(it->data)) {
                if (it->prev != nullptr) {
                    it = it->prev;
                    delNode(it->next);
                } else {
                    delNode(it);
                    break;
                }
                cnt++;
            } else it = it->prev;
        }
    }
    return cnt;
}

template<typename T>
void LinkedList<T>::clear() {
    ifRemove([](T &) -> bool { return true; }, true);
}

template<typename T>
void LinkedList<T>::popFront() {
    delNode(head);
}

template<typename T>
void LinkedList<T>::popBack() {
    delNode(tail);
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin() {
    return iterator(this->head, this);
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::rbegin() {
    return iterator(this->tail, this);
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() {
    return iterator(nullptr, this);
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::rend() {
    return iterator(nullptr, this);
}

template<typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

/**
 * @tparam T
 * @param obj
 */
template<typename T>
LinkedList<T>::LinkedList(const LinkedList &obj) {
    addAll(obj, false, true);
}

/**
 * @tparam T
 * @param obj
 */
template<typename T>
void LinkedList<T>::addAll(LinkedList<T> &list, bool thisFront, bool listFront) {
    if (thisFront) {
        list.forEach([&](T &x) -> void { pushFront(x); }, !listFront);
    } else list.forEach([&](T &x) -> void { pushBack(x); }, listFront);
}

/**
 * @tparam T
 * @param obj
 */
template<typename T>
int LinkedList<T>::indexOf(T &data) const {
    int pos = -1, res = -1;
    forEach([&](T &x) -> void {
        pos++;
        if (x == data) res = res == -1 ? pos : res;
    });
    return res;
}
