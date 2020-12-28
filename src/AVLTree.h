/**
 * Created by Clion.
 * User: icy
 * Date: 2020/10/26
 * i@icys.top
 */

#ifndef DS2020_AVLTREE_H
#define DS2020_AVLTREE_H

#include <vector>
#include <functional>
#include <cassert>
#include <optional>
#include "Queue.h"

template<typename T, typename Container = std::vector<T>, typename less = std::less<typename Container::value_type>>
class AVLTree {
    class Node {
        friend class AVLTree;

        Node *leftSon = nullptr, *rightSon = nullptr, *father = nullptr;
        int size{1}, depth{1}, count{1};
        T data;
        bool inList = false;

        explicit Node(Node *_father, T _data) : father(_father), data(_data) {}
    };

    Node *root;

    less cmp;

    Queue<Node *> updateList;

    inline void pushList(Node *node);

    void update();

    Node *findRankOf(unsigned int rank) const;

    Node *findMin(Node *node) const;

    Node *findMax(Node *node) const;

    Node *findPrev(Node *node) const;

    Node *findNext(Node *node) const;

    Node *findNode(T data) const;

    void leftRotate(Node *node);

    void rightRotate(Node *node);

    int calcRotate(Node *node) const;

public:
    void push(T data);

    int rank(T data) const;

    void del(T data);

    std::optional<T> getNextData(T data) const;

    std::optional<T> getPrevData(T data) const;

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
            tmp->size++;
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
    pushList(tmp->father);
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
    if (node->count > 1) {
        node->count--;
        node->size--;
        pushList(node->father);
        return;
    }
    if (node->leftSon == nullptr and node->rightSon == nullptr) {
        if (node == root) {
            root = nullptr;
        }
        if (cmp(node->data, node->father->data)) {
            node->father->leftSon = nullptr;
        } else {
            node->father->rightSon = nullptr;
        }
        pushList(node->father);
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
    pushList(updateNode);
}

template<typename T, typename Container, typename less>
std::optional<T> AVLTree<T, Container, less>::getRankOf(int rank) const {
    Node *node = findRankOf(rank);
    if (node == nullptr)return std::nullopt;
    return node->data;
}

template<typename T, typename Container, typename less>
void AVLTree<T, Container, less>::update() {
    while (!updateList.isEmpty()) {
        Node *node = updateList.front();
        updateList.pop();
        if (node == nullptr)continue;
        node->inList = false;
        int original_size = node->size, original_depth = node->depth;
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
        } else if (calcThis > 1) {
            calcSon = calcRotate(node->rightSon);
            if (calcSon < 0) {
                rightRotate(node->rightSon);
                leftRotate(node);
            } else {
                leftRotate(node);
            }
        }
        if (node->size != original_size or node->depth != original_depth)pushList(node->father);
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
            rank -= node->count;
            if (rank < 0)return node;
            node = node->rightSon;
        } else if (rank >= node->leftSon->size) {
            rank -= node->leftSon->size + node->count;
            if (rank < 0) return node;
            node = node->rightSon;
        } else {
            node = node->leftSon;
        }
    }
    return findMin(node);
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
    if (node->rightSon != nullptr)node->rightSon->father = node;
    pushList(node);
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
    node->leftSon = newFather->rightSon;
    newFather->rightSon = node;
    if (node->leftSon != nullptr)node->leftSon->father = node;
    pushList(node);
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
int AVLTree<T, Container, less>::calcRotate(AVLTree::Node *node) const {
    if (node == nullptr) return 0;
    int left = node->leftSon == nullptr ? 0 : node->leftSon->depth;
    int right = node->rightSon == nullptr ? 0 : node->rightSon->depth;
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

template<typename T, typename Container, typename less>
void AVLTree<T, Container, less>::pushList(AVLTree::Node *node) {
    if (node == nullptr)return;
    if (node->inList)return;
    node->inList = true;
    updateList.push(node);
}

template<typename T, typename Container, typename less>
std::optional<T> AVLTree<T, Container, less>::getNextData(T data) const {
    Node *node = findNext(findNode(data));
    if (node == nullptr) return std::nullopt;
    return node->data;
}

template<typename T, typename Container, typename less>
std::optional<T> AVLTree<T, Container, less>::getPrevData(T data) const {
    Node *node = findPrev(findNode(data));
    if (node == nullptr) return std::nullopt;
    return node->data;
}

#endif //DS2020_AVLTREE_H
