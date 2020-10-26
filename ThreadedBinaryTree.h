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

public:
    explicit ThreadBinaryTree(const std::function<bool(T, T)> &compare = [](T a, T b) -> bool {
        return a < b;
    }) : cmp(compare) {}

    void addNode(T element) {
        if (root == nullptr) {
            root = new Node(element);
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
                    if (newNode->leftSon != nullptr and !newNode->leftSon->rightUsed)
                        newNode->leftSon->rightSon = newNode;
                    tmp->leftSon = newNode;
                    tmp->leftUsed = 1;
                    break;
                } else tmp = tmp->leftSon;
            } else {
                if (!tmp->rightUsed) {
                    newNode->leftSon = tmp;
                    newNode->rightSon = tmp->rightSon;
                    if (newNode->rightSon != nullptr and !newNode->rightSon->leftUsed)
                        newNode->rightSon->leftSon = newNode;
                    tmp->rightSon = newNode;
                    tmp->rightUsed = 1;
                    break;
                } else tmp = tmp->rightSon;
            }
        }
        updateDepth(newNode->father);
    }

    void delNode(T element) {
        Node *node = findNode(element);
        if (node == nullptr)return;
        Node *pre = findPre(node), *after = findAfter(node), *updateNode = node->father;
        if (!node->leftUsed and !node->rightUsed) {
            printf("1-");
            if (node == root) {
                delete node;
                return;
            }
            if (cmp(node->data, node->father->data))
                node->father->leftUsed = 0;
            else node->father->rightUsed = 0;
        } else if (!node->leftUsed and node->rightUsed) {
            printf("3-");
            if (node == root)root = node->rightSon;
            if (node->father != nullptr) {
                if (cmp(node->data, node->father->data))
                    node->father->leftSon = node->rightSon;
                else node->father->rightSon = node->rightSon;
            }
            node->rightSon->father = node->father;
        } else if (node->leftUsed and !node->rightUsed) {
            printf("2-");
            if (node == root)root = node->leftSon;
            if (node->father != nullptr) {
                if (cmp(node->data, node->father->data))
                    node->father->leftSon = node->leftSon;
                else node->father->rightSon = node->leftSon;
            }
            node->leftSon->father = node->father;
        } else {
            if (node->leftSon->depth > node->rightSon->depth) {
                printf("4-");
                if (node == root)root = pre;
                updateNode = pre->father;
                if (pre != node->leftSon) {
                    if (pre->leftUsed) {
                        pre->father->rightSon = pre->leftSon;
                        pre->leftSon->father = pre->father;
                    } else {
                        pre->father->rightUsed = 0;
                    }
                    pre->leftSon = node->leftSon;
                    pre->leftUsed = 1;
                }
                pre->rightSon = node->rightSon;
                node->rightSon->father = pre;
                pre->rightUsed = 1;
                pre->father = node->father;
                if (pre->leftUsed)pre->leftSon->father = pre;
                if (node->father != nullptr) {
                    if (cmp(pre->data, node->father->data))
                        node->father->leftSon = pre;
                    else node->father->rightSon = pre;
                }
            } else {
                printf("5-");
                if (node == root)root = after;
                updateNode = after->father;
                if (after != node->rightSon) {
                    if (after->rightUsed) {
                        after->father->leftSon = after->rightSon;
                        after->rightSon->father = after->father;
                    } else {
                        after->father->leftUsed = 0;
                    }
                    after->rightSon = node->rightSon;
                    node->rightSon->father = after;
                    after->rightUsed = 1;
                }
                after->leftSon = node->leftSon;
                node->leftSon->father = after;
                after->leftUsed = 1;
                after->father = node->father;
                if (after->rightUsed)after->rightSon->father = after;
                if (node->father != nullptr) {
                    if (cmp(after->data, node->father->data))
                        node->father->leftSon = after;
                    else node->father->rightSon = after;
                }
            }
        }
        updateDepth(updateNode);
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

private:
    std::function<bool(T, T)> cmp;
    Node *root = nullptr;

    Node *findNode(const T &element) const {
        if (root == nullptr)return nullptr;
        Node *tmp = root;
        while (cmp(element, tmp->data) ^ cmp(tmp->data, element)) {
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

    Node *findPre(Node *&node) {
        if (!node->leftUsed) {
            return node->leftSon;
        }
        Node *tmp = node->leftSon;
        while (tmp->rightUsed) {
            tmp = tmp->rightSon;
        }
        return tmp;
    }

    Node *findAfter(Node *&node) {
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

    void updateDepth(Node *node) {
        while (node != nullptr) {
            int leftDepth = node->leftUsed ? node->leftSon->depth : 0;
            int rightDepth = node->rightUsed ? node->rightSon->depth : 0;
            node->depth = std::max(leftDepth, rightDepth) + 1;
            node = node->father;
        }
    }
};

#endif //DS2020_THREADEDBINARYTREE_H
