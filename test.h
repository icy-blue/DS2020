#include "DoubleLinkedList.h"
#include "sort.h"
#include <algorithm>
#include <cstring>
#include "PriorityQueue.h"

#ifndef DS2020_TEST_H
#define DS2020_TEST_H
static DoubleLinkedList<int> list;

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

static int arr[] = {1, 5, 7, 9, 8, 2, 4, 6};

void testSort() {
    std::for_each(arr, arr + 8, [](int x) -> void { printf("%d ", x); });
    Algorithm<int>::sort(arr, arr + 8);
    puts("");
    std::for_each(arr, arr + 8, [](int x) -> void { printf("%d ", x); });
}

void testPQ() {
    PriorityQueue<int> queue;
    std::for_each(arr, arr + 8, [&](int x) -> void {
        queue.push(x);
        printf("%d ", queue.top());
    });
    puts("");
    std::for_each(arr, arr + 8, [&](int x) -> void {
        printf("%d ", queue.top());
        queue.pop();
    });
}

#endif