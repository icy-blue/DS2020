#include "DoubleLinkedList.h"

DoubleLinkedList<int> list;

void test() {
    list.pushBack(1);
    list.pushFront(0);
    list.popFront();
    list.popFront();
    list.pushFront(1);
    list.pushBack(2);
    list.pushBack(3);
    list = list.reverse();
    list.deleteElement(1);
    list.print();
    list.insertBehind(1, 6);
    list.insertBefore(0, 7);
    auto it = list.begin();
    it++;
    ++it;
    --it;
    it--;
    it = list.end();
    it = list.rend();
    it = list.rbegin();
    it = list.begin();
    it.hasNext();
    it.hasPre();
    it.insertBefore(1);
    it.insertBehind(2);
    it.set(0);
    it.remove();
    list.indexOf(0);
}