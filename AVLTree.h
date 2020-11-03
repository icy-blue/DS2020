/**
  * Created by Huang Jingcheng on 2020/10/26.
  * 201905130198@mail.sdu.edu.cn
*/


#ifndef DS2020_AVLTREE_H
#define DS2020_AVLTREE_H

#include <vector>
#include <functional>
#include <cassert>
#include "Queue.h"

template<typename T, typename Container = std::vector<T>, typename less = std::less<typename Container::value_type>>
class AVLTree {
    class Node {
        friend class AVLTree;

        Node *leftSon = nullptr, *rightSon = nullptr, *father = nullptr;
        int size{1}, depth{1}, count{1};
        T data;

        explicit Node(Node *_father, T _data) : father(_father), data(_data) {}
    };

    Node *root;

    less cmp;

    void update(Node *node);

    Node *findRankOf(unsigned int rank) const;

    Node *findMin(Node *node) const;

    Node *findMax(Node *node) const;

    Node *findPrev(Node *node) const;

    Node *findNext(Node *node) const;

    Node *findNode(T data) const;

    void leftRotate(Node *node);

    void rightRotate(Node *node);

    int calcRotate(Node *node);

public:
    void push(T data);

    int rank(T data) const;

    void del(T data);

    std::optional<T> getRankOf(int rank) const;

    AVLTree() = default;

    ~AVLTree();
};

template<typename T, typename Container, typename less>
void AVLTree<T, Container, less>::push(const T data) {
    if (root == nullptr) {
        root = new Node(nullptr, data);
        return;
    }
    Node *tmp = root;
    while (true) {
        if (!(cmp(data, tmp->data) ^ cmp(tmp->data, data))) {
            tmp->count++;
            break;
        }
        if (cmp(data, tmp->data)) {
            if (tmp->leftSon == nullptr) {
                tmp->leftSon = new Node(tmp, data);
                break;
            } else tmp = tmp->leftSon;
        } else {
            if (tmp->rightSon == nullptr) {
                tmp->rightSon = new Node(tmp, data);
                break;
            } else tmp = tmp->rightSon;
        }
    }
    update(tmp);
}

template<typename T, typename Container, typename less>
int AVLTree<T, Container, less>::rank(const T data) const {
    int result = 0;
    Node *node = root;
    while (node != nullptr) {
        if (!(cmp(data, node->data) ^ cmp(node->data, data))) return result;
        if (cmp(data, node->data)) {
            node = node->leftSon;
        } else {
            result += node->size;
            node = node->leftSon;
        }
    }
    return -1;
}

template<typename T, typename Container, typename less>
void AVLTree<T, Container, less>::del(const T data) {
    Node *node = findNode(data), *updateNode = node->father;
    if (node->leftSon == nullptr and node->rightSon == nullptr) {
        if (node == root) {
            root = nullptr;
        }
        if (cmp(node->data, node->father->data)) {
            node->father->leftSon = nullptr;
            update(node->father);
        } else {
            node->father->rightSon = nullptr;
            update(node->father);
        }
    } else if (node->leftSon != nullptr and node->rightSon == nullptr) {
        if (node == root) root = node->leftSon;
        else if (cmp(node->data, node->father->data)) node->father->leftSon = node->leftSon;
        else node->father->rightSon = node->leftSon;
        node->leftSon->father = node->father;
    } else if (node->leftSon == nullptr and node->rightSon != nullptr) {
        if (node == root)root = node->rightSon;
        else if (cmp(node->data, node->father->data)) node->father->leftSon = node->rightSon;
        else node->father->rightSon = node->rightSon;
        node->rightSon->father = node->rightSon;
    } else {
        if (node->leftSon->depth > node->rightSon->depth) {
            Node *pre = findPrev(node);
            if (node == root) root = pre;
            updateNode = pre->father;
            if (pre != node->leftSon) {
                pre->father->rightSon = pre->leftSon;
                pre->leftSon->father = pre->father;
                pre->leftSon = node->leftSon;
            }
            pre->rightSon = node->rightSon;
            node->rightSon->father = pre;
            pre->father = node->father;
            if (pre->leftSon != nullptr)pre->leftSon->father = pre;
            if (cmp(pre->data, node->father->data)) node->father->leftSon = pre;
            else node->father->rightSon = pre;
        } else {
            Node *after = findNext(node);
            if (node == root)root = after;
            updateNode = after->father;
            if (after != node->rightSon) {
                after->father->leftSon = after->rightSon;
                after->rightSon->father = after->father;
                after->rightSon = node->rightSon;
                node->rightSon->father = after;
            }
            after->leftSon = node->leftSon;
            node->leftSon->father = after;
            after->father = node->father;
            if (after->rightSon != nullptr)after->rightSon->father = after;
            if (cmp(after->data, node->father->data)) node->father->leftSon = after;
            else node->father->rightSon = after;
        }
    }
    delete node;
    update(updateNode);
}

template<typename T, typename Container, typename less>
std::optional<T> AVLTree<T, Container, less>::getRankOf(int rank) const {
    Node *node = findRankOf(rank);
    if (node == nullptr)return std::nullopt;
    return node->data;
}

template<typename T, typename Container, typename less>
void AVLTree<T, Container, less>::update(AVLTree::Node *node) {
    if (node == nullptr)return;
    node->size = (node->leftSon == nullptr ? 0 : node->leftSon->size) +
                 (node->rightSon == nullptr ? 0 : node->rightSon->size) + node->count;
    node->depth = std::max(node->leftSon == nullptr ? 0 : node->leftSon->depth,
                           node->rightSon == nullptr ? 0 : node->rightSon->depth) + 1;
    int calcThis = calcRotate(node), calcSon;
    if (calcThis < -1) {
        calcSon = calcRotate(node->leftSon);
        if (calcSon <= 0) {
            leftRotate(node);
        } else {
            leftRotate(node->leftSon);
            rightRotate(node);
        }
    }
    if (calcThis > 1) {
        calcSon = calcRotate(node->rightSon);
        if (calcSon < 0) {
            rightRotate(node->rightSon);
            leftRotate(node);
        } else {
            leftRotate(node);
        }
    }
}

template<typename T, typename Container, typename less>
typename AVLTree<T, Container, less>::Node *AVLTree<T, Container, less>::findRankOf(unsigned int rank) const {
    if (root == nullptr)return nullptr;
    if (rank < 0 or rank >= root->size)return nullptr;
    Node *node = root;
    while (rank > 0) {
        if (node == nullptr) return nullptr;
        if (node->leftSon == nullptr) {
            rank--;
            if (rank == 0) return findMin(node);
            node = node->rightSon;
        } else if (rank > node->leftSon->size) {
            rank -= node->leftSon->size + 1;
            if (rank == 0) return findMin(node);
            node = node->rightSon;
        } else {
            node = node->leftSon;
        }
    }
    return nullptr;
}

template<typename T, typename Container, typename less>
void AVLTree<T, Container, less>::leftRotate(AVLTree::Node *node) {
    if (node == root) root = node->rightSon;
    Node *newFather = node->rightSon;
    if (node->father != nullptr) {
        if (cmp(node->data, node->father->data)) node->father->leftSon = newFather;
        else node->father->rightSon = newFather;
    }
    newFather->father = node->father;
    node->father = newFather;
    node->rightSon = newFather->leftSon;
    newFather->leftSon = node;
    node->rightSon->father = node;
}

template<typename T, typename Container, typename less>
void AVLTree<T, Container, less>::rightRotate(AVLTree::Node *node) {
    if (node == root)root = node->leftSon;
    Node *newFather = node->leftSon;
    if (node->father != nullptr) {
        if (cmp(node->data, node->father->data)) node->father->leftSon = newFather;
        else node->father->rightSon = newFather;
    }
    newFather->father = node->father;
    node->father = newFather;
    node->rightSon = newFather->leftSon;
    newFather->leftSon = node;
    node->rightSon->father = node;
}

template<typename T, typename Container, typename less>
typename AVLTree<T, Container, less>::Node *AVLTree<T, Container, less>::findNode(T data) const {
    Node *node = root;
    while (node != nullptr) {
        if (!(cmp(data, node->data) ^ cmp(node->data, data))) return node;
        if (cmp(data, node->data)) node = node->leftSon;
        else node = node->rightSon;
    }
    return nullptr;
}

template<typename T, typename Container, typename less>
int AVLTree<T, Container, less>::calcRotate(AVLTree::Node *node) {
    if (node == nullptr) return 0;
    int left = node->leftSon == nullptr ? 0 : node->leftSon->size;
    int right = node->rightSon == nullptr ? 0 : node->rightSon->size;
    return right - left;
}

template<typename T, typename Container, typename less>
typename AVLTree<T, Container, less>::Node *AVLTree<T, Container, less>::findMin(AVLTree::Node *node) const {
    if (node == nullptr)return nullptr;
    while (true) {
        if (node->leftSon != nullptr) node = node->leftSon;
        else return node;
    }
}

template<typename T, typename Container, typename less>
typename AVLTree<T, Container, less>::Node *AVLTree<T, Container, less>::findMax(AVLTree::Node *node) const {
    if (node == nullptr)return nullptr;
    while (true) {
        if (node->rightSon != nullptr) node = node->rightSon;
        else return node;
    }
}

template<typename T, typename Container, typename less>
typename AVLTree<T, Container, less>::Node *AVLTree<T, Container, less>::findPrev(AVLTree::Node *node) const {
    Node *tmp = node;
    if (node != nullptr and node->leftSon != nullptr)return findMax(node->leftSon);
    while (tmp != nullptr) {
        if (tmp->father == nullptr)return nullptr;
        if (cmp(tmp->data, tmp->father->data)) {
            tmp = tmp->father;
        } else {
            return tmp->father;
        }
    }
    return tmp;
}

template<typename T, typename Container, typename less>
typename AVLTree<T, Container, less>::Node *AVLTree<T, Container, less>::findNext(AVLTree::Node *node) const {
    Node *tmp = node;
    if (node != nullptr and node->rightSon != nullptr)return findMin(node->rightSon);
    while (tmp != nullptr) {
        if (tmp->father == nullptr)return nullptr;
        if (cmp(tmp->data, tmp->father->data)) {
            return tmp->father;
        } else {
            tmp = tmp->father;
        }
    }
    return tmp;
}

template<typename T, typename Container, typename less>
AVLTree<T, Container, less>::~AVLTree() {
    if (root == nullptr)return;
    Queue<Node *> queue;
    queue.push(root);
    while (!queue.isEmpty()) {
        Node *node = queue.front();
        queue.pop();
        if (node->leftSon != nullptr)queue.push(node->leftSon);
        if (node->rightSon != nullptr)queue.push(node->rightSon);
    }
}

#endif //DS2020_AVLTREE_H
