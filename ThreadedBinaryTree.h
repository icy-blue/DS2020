/**
  * Created by Huang Jingcheng on 2020/10/21.
  * 201905130198@mail.sdu.edu.cn
*/

#ifndef DS2020_THREADEDBINARYTREE_H
#define DS2020_THREADEDBINARYTREE_H

#include "Stack.h"
#include <cassert>
#include <vector>
#include <functional>

template<typename T>
class ThreadBinaryTree {
    class Node {
    public:
        Node *leftSon = nullptr, *rightSon = nullptr, *father = nullptr;
        T data;
        int depth = 1;
        unsigned leftUsed: 1;
        unsigned rightUsed: 1;

        explicit Node(T _data) : data(_data) {
            leftUsed = 0;
            rightUsed = 0;
        }
    };

    explicit ThreadBinaryTree(std::function<bool(T, T)> &compare = [](T a, T b) -> bool {
        return a < b;
    }) : cmp(compare) {}

private:
    std::function<bool(T, T)> cmp;
    Node *root;

    void addNode(T element) {
        if (root == nullptr) {
            root = Node(element);
            return;
        }
        Node *tmp = root;
        Node *newNode = new Node(element);
        while (true) {
            newNode->father = tmp;
            if (cmp(element, tmp->data)) {
                if (!tmp->leftUsed) {
                    newNode->rightSon = tmp;
                    newNode->leftSon = tmp->leftSon;
                    if (!newNode->leftSon->rightUsed)
                        newNode->leftSon->rightSon = newNode;
                    tmp->leftSon = newNode;
                    tmp->leftUsed = 1;
                    break;
                } else tmp = tmp->leftSon;
            } else {
                if (!tmp->rightUsed) {
                    newNode->leftSon = tmp;
                    newNode->rightSon = tmp->rightSon;
                    if (!newNode->rightSon->leftUsed)
                        newNode->rightSon->leftSon = newNode;
                    tmp->rightSon = newNode;
                    tmp->leftUsed = 1;
                    break;
                } else tmp = tmp->rightSon;
            }
        }
        tmp = newNode->father;
        while (tmp != nullptr) {
            int leftDepth = tmp->leftUsed ? 0 : tmp->leftSon->depth;
            int rightDepth = tmp->rightUsed ? 0 : tmp->rightSon->depth;
            tmp->depth = std::max(leftDepth, rightDepth) + 1;
            tmp = tmp->father;
        }
    }

    Node *findNode(const T &element) const {
        if (root == nullptr)return nullptr;
        Node *tmp = root;
        while (!(cmp(element, tmp->data) ^ cmp(tmp->data, element))) {
            if (cmp(element, tmp->data)) {
                if (tmp->leftUsed) tmp = tmp->leftSon;
                else return nullptr;
            } else {
                if (tmp->rightUsed) tmp = tmp->rightSon;
                else return nullptr;
            }
        }
        return tmp;
    }

    Node *findPre(const Node *&node) {
        if (!node->leftUsed) {
            return node->leftSon;
        }
        Node *tmp = node->leftSon;
        while (tmp->rightUsed) {
            tmp = tmp->rightSon;
        }
        return tmp;
    }

    Node *findAfter(const Node *&node) {
        if (!node->rightUsed) {
            return node->rightSon;
        }
        Node *tmp = node->rightSon;
        while (tmp->leftUsed) {
            tmp = tmp->leftSon;
        }
        return tmp;
    }

    Node *findFirst() {
        Node *node = root;
        while (node->leftUsed)node = node->leftSon;
        return node;
    }

    Node *findLast() {
        Node *node = root;
        while (node->rightUsed)node = node->rightSon;
        return node;
    }

    void delNode(T element) {
        Node *node = findNode(element);
        if (node == nullptr)return;
        Node *pre = findPre(node), *after = findAfter(node);

        if (!node->leftUsed and !node->rightUsed) {
            if (cmp(node->data, node->father->data)) {
                node->father->leftUsed = 0;
            } else {
                node->father->rightUsed = 0;
            }
        } else if (!node->leftUsed and node->rightUsed) {
            if (node->father != nullptr) {
                if (cmp(node->data, node->father->data))
                    node->father->leftSon = node->rightSon;
                else node->father->rightSon = node->rightSon;
            }
            node->rightSon->father = node->father;
        } else if (node->leftUsed and !node->rightUsed) {
            if (cmp(node->data, node->father->data))
                node->father->leftSon = node->leftSon;
            else node->father->rightSon = node->leftSon;
            node->leftSon->father = node->father;
        } else {
            if (node->leftSon->depth > node->rightSon->depth) {
                if (pre != node->leftSon) {
                    if (pre->leftUsed) {
                        pre->father->rightSon = pre->leftSon;
                        pre->leftSon->father = pre->father;
                    } else {
                        pre->father->rightUsed = 0;
                    }
                    pre->leftSon = node->leftSon;
                    pre->leftUsed = 1;
                } else {
                    pre->leftUsed = pre->leftSon->leftUsed;
                    pre->leftSon = pre->leftSon->leftSon;
                }
                pre->rightSon = node->rightSon;
                pre->rightUsed = 1;
                pre->father = node->father;
                if (cmp(pre->data, node->father->data))
                    node->father->leftSon = pre;
                else node->father->rightSon = pre;
            } else {
                if (after != node->rightSon) {
                    if (after->rightUsed) {
                        after->father->leftSon = after->rightSon;
                        after->rightSon->father = after->father;
                    } else {
                        after->father->leftUsed = 1;
                    }
                    after->rightSon = node->rightSon;
                    after->rightUsed = 1;
                } else {
                    after->rightUsed = after->rightSon->rightUsed;
                    after->rightSon = after->rightSon->rightSon;
                }
                after->leftSon = node->leftSon;
                after->leftUsed = 1;
                after->father = node->father;
                if (cmp(after->data, node->father->data))
                    node->father->leftSon = after;
                else node->father->rightSon = after;
            }
        }
        if (pre != nullptr and !pre->rightUsed) pre->rightSon = after;
        if (after != nullptr and !after->leftUsed) after->leftSon = pre;
        delete node;
    }

    void forEach(bool isReverse, const std::function<void(T)> &function) {
        if (!isReverse) {
            Node *node = findFirst();
            while (node != nullptr) {
                function(node->data);
                node = findAfter(node);
            }
        } else {
            Node *node = findLast();
            while (node != nullptr) {
                function(node->data);
                node = findPre(node);
            }
        }
    }
};

#endif //DS2020_THREADEDBINARYTREE_H
