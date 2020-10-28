/**
  * Created by Huang Jingcheng on 2020/10/26.
  * 201905130198@mail.sdu.edu.cn
*/


#ifndef DS2020_AVLTREE_H
#define DS2020_AVLTREE_H

#include <vector>
#include <functional>
#include <cassert>

template<typename T, typename Container = std::vector<T>, typename less = std::less<typename Container::value_type>>
class AVLTree {
    class Node {
        friend class AVLTree;

        Node *leftSon = nullptr, *rightSon = nullptr, *father = nullptr;
        int size{1}, depth{1};
        T data;

        explicit Node(Node *_father, T _data) : father(_father), data(_data) {}
    };

    Node *root;

    void update(Node *node);

    Node *findRankOf(unsigned int rank) const;

    Node *findMin(Node *node);

    Node *findMax(Node *node);

    Node *findPrev(Node *node);

    Node *findNext(Node *node);

    Node *findNode(T data);

    void leftRotate(Node *node);

    void rightRotate(Node *node);

    int calcRotate(Node *node);

public:
    void push(T data);

    int rank(T data) const;

    void del(T data);

    T getRankOf(int rank) const;

    AVLTree() = default;
};

template<typename T, typename Container, typename less>
void AVLTree<T, Container, less>::push(const T data) {
    if (root == nullptr) {
        root = new Node(nullptr, data);
        return;
    }
    Node *tmp = root;
    while (true) {
        if (less(data, tmp->data)) {
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
        if (!(less(data, node->data) ^ less(node->data, data))) return result;
        if (less(data, node->data)) {
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
    Node *node = findNode(data);
    if (node == root) {
        root = nullptr;
    } else if (less(node->data, node->father->data)) {
        node->father->leftSon = nullptr;
        update(node->father);
    } else {
        node->father->rightSon = nullptr;
        update(node->father);
    }
    delete node;
}

template<typename T, typename Container, typename less>
T AVLTree<T, Container, less>::getRankOf(int rank) const {
    Node *node = findRankOf(rank);
    return node == nullptr ? nullptr : node->data;
}

template<typename T, typename Container, typename less>
void AVLTree<T, Container, less>::update(AVLTree::Node *node) {
    if (node == nullptr)return;
    node->size = (node->leftSon == nullptr ? 0 : node->leftSon->size) +
                 (node->rightSon == nullptr ? 0 : node->rightSon->size) + 1;
    node->depth = std::max(node->leftSon == nullptr ? 0 : node->leftSon->depth,
                           node->rightSon == nullptr ? 0 : node->rightSon->depth) + 1;
    int calcThis = calcRotate(node), calcSon;
    if (calcThis < -1) {
        calcSon = calcRotate(node->leftSon);
        if (calcSon < 0) {
            leftRotate(node);
        }
        if (calcSon > 0) {
            leftRotate(node->leftSon);
            rightRotate(node);
        }
    }
    if (calcThis > 1) {
        calcSon = calcRotate(node->rightSon);
        if (calcSon < 0) {
            rightRotate(node->rightSon);
            leftRotate(node);
        }
        if (calcSon > 0) {
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
}

template<typename T, typename Container, typename less>
void AVLTree<T, Container, less>::leftRotate(AVLTree::Node *node) {
    if (node == root) root = node->rightSon;
    Node *newFather = node->rightSon;
    if (node->father != nullptr) {
        if (less(node->data, node->father->data)) node->father->leftSon = newFather;
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
        if (less(node->data, node->father->data)) node->father->leftSon = newFather;
        else node->father->rightSon = newFather;
    }
    newFather->father = node->father;
    node->father = newFather;
    node->rightSon = newFather->leftSon;
    newFather->leftSon = node;
    node->rightSon->father = node;
}

template<typename T, typename Container, typename less>
typename AVLTree<T, Container, less>::Node *AVLTree<T, Container, less>::findNode(T data) {
    Node *node = root;
    while (node != nullptr) {
        if (!(less(data, node->data) ^ less(node->data, data))) return node;
        if (less(data, node->data)) node = node->leftSon;
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
typename AVLTree<T, Container, less>::Node *AVLTree<T, Container, less>::findMin(AVLTree::Node *node) {
    if (node == nullptr)return nullptr;
    while (true) {
        if (node->leftSon != nullptr) node = node->leftSon;
        else return node;
    }
}

template<typename T, typename Container, typename less>
typename AVLTree<T, Container, less>::Node *AVLTree<T, Container, less>::findMax(AVLTree::Node *node) {
    if (node == nullptr)return nullptr;
    while (true) {
        if (node->rightSon != nullptr) node = node->rightSon;
        else return node;
    }
}

template<typename T, typename Container, typename less>
typename AVLTree<T, Container, less>::Node *AVLTree<T, Container, less>::findPrev(AVLTree::Node *node) {
    if (node->leftUsed) {
        return node->leftSon;
    }
    Node *tmp = node;
    while (tmp != nullptr) {
        if (tmp->father == nullptr)return nullptr;
        if (less(tmp->data, tmp->father->data)) {
            tmp = tmp->father;
        } else {
            return tmp->father;
        }
    }
    return tmp;
}

template<typename T, typename Container, typename less>
typename AVLTree<T, Container, less>::Node *AVLTree<T, Container, less>::findNext(AVLTree::Node *node) {
    if (node->rightUsed) {
        return node->rightSon;
    }
    Node *tmp = node;
    while (tmp != nullptr) {
        if (tmp->father == nullptr)return nullptr;
        if (less(tmp->data, tmp->father->data)) {
            return tmp->father;
        } else {
            tmp = tmp->father;
        }
    }
    return tmp;
}

#endif //DS2020_AVLTREE_H
