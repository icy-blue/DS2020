/**
	Created by Huang Jingcheng on 2020/9/9.
	201905130198@mail.sdu.edu.cn
*/

#ifndef DS2020_LINKEDLIST_H
#define DS2020_LINKEDLIST_H

#include <functional>

#define debug(x) std::cout<<(#x)<<" "<<(x)<<std::endl

template<typename T>
class LinkedList {
    class Node {
        friend class LinkedList;

    private:
        explicit Node(T &data);

    public:
        Node *prev, *next;
        T data;
    };

    LinkedList(const LinkedList &obj);

    ~LinkedList();

    typename LinkedList<T>::Node *getNode(int index) const;

    void delNode(Node *node);

    void insertBehind(Node *node, T element);

public:
    Node *head = nullptr, *tail = nullptr;

    class iterator {
        friend class LinkedList;

    private:
        Node *pos;
        LinkedList<T> *parent;

        explicit iterator(Node *pos, LinkedList<T> *parent);

    public:
        void operator++(int);

        void operator++();

        void operator--(int);

        void operator--();

        bool operator==(const iterator &r) const;

        bool operator!=(const iterator &r) const;

        T operator*() const;

        bool hasNext() const;

        bool hasPre() const;

        void next();

        void pre();

        T get() const;

        void insertBefore(T data);

        void insertBehind(T data);

        void remove();

        void set(T element);
    };

    LinkedList() = default;

    void pushFront(T element);

    void pushBack(T element);

    T get(int index) const;

    void deleteElement(int index);

    bool isEmpty() const;

    void print();

    void insertBehind(int index, T element);

    void insertBefore(int index, T element);

    void forEach(std::function<void(T &)> const &func, bool front);

    int ifRemove(std::function<bool(T &)> const &func, bool front);

    void clear();

    void popFront();

    void popBack();

    typename LinkedList::iterator begin();

    typename LinkedList::iterator rbegin();

    typename LinkedList::iterator end();

    typename LinkedList::iterator rend();

    void addAll(LinkedList<T> &list, bool thisFront, bool listFront);

    int indexOf(T &data) const;
};


#endif //DS2020_LINKEDLIST_H
