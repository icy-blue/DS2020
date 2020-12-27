/**
 * Created by Clion.
 * User: icy
 * Date: 2020/12/8
 * i@icys.top
 */

#ifndef DS2020_TREE23P_H
#define DS2020_TREE23P_H

#include <vector>
#include <functional>
#include <algorithm>
#include <cassert>

template<typename T, typename Container = std::vector<T>, typename less = std::less<typename Container::value_type>>
class Tree23P {
#define SIZE_DATA 2

    class Node {
    public:
        std::vector<Node *> sons;
        Node *father;
        std::vector<T> data;
        int nodeSize = 1, treeSize = 1, depth = 1; //depth 以x为根节点的子树层数
        bool isLeaf = true;
    };

public:
    Tree23P() = default;

    Node *root;

    void insert(const T &data) {
        if (root == nullptr) {
            root = new Node();
            root->data.push_back(data);
            return;
        }
        auto node = root;
        while (true) {
            assert(node != nullptr);
            int i = 0;
            while (i < node->nodeSize and less(node->data[i], data)) i++;
            if (node->isLeaf) {
                node->data.insert(node->data.begin() + i, data);
                node->nodeSize++;
                break;
            } else {
                node = node->sons[i];
            }
        }
        pushUp(node);
    }

    void pushUp(Node *node) {
        while (node != nullptr) {
            if (node->nodeSize > SIZE_DATA) {
                Node *node1 = new Node, *node2 = new Node;
                node1->sons.push_back(node->sons[0]);
                node1->sons.push_back(node->sons[1]);
                node1->data.push_back(node->data[0]);
                node2->sons.push_back(node->sons[2]);
                node2->sons.push_back(node->sons[3]);
                node2->data.push_back(node->data[2]);
                node1->father = node2->father = node;
                node1->isLeaf = node2->isLeaf = node->isLeaf;
                node1->depth = node2->depth = node1->depth;
                T data = node->data[1];
                if (node->father != nullptr) {
                    int i = 0;
                    while (i < node->father->nodeSize and less(node->father->data[i], data)) i++;
                    node->father->data.insert(node->father->data.begin() + i, data);
                    node->father->sons.erase(node->father->sons.begin() + i);
                    node->father->sons.insert(node->father->sons.begin() + i, node2);
                    node->father->sons.insert(node->father->sons.begin() + i, node1);
                } else {
                    node->father = new Node;
                    node->father->data.push_back(data);
                    node->father->sons.push_back(node1);
                    node->father->sons.push_back(node2);
                    node->father->isLeaf = false;
                    if (node == root) root = node->father;
                }
                delete node;
                node = node1;
            }
            if (node->father != nullptr) {
                node->father->depth = node->depth + 1;
            }
            node = node->father;
        }
    }

private:
    Node *getSibling(Node *node) {
        if (node == nullptr or node->father == nullptr)return nullptr;
        assert(node->father->nodeSize == 1);
        if (node == node->father->sons[0]) return node->father->sons[1];
        return node->father->sons[0];
    }

public:
    void del(const T &data) {
        Node *node = find(data);
        if (node == nullptr)return;
        Node *tmp = root;
        auto checkSingle = [](Node *node) -> bool {
            return node == nullptr or node->nodeSize == 1;
        };
        while (tmp != nullptr) {
            if (checkSingle(tmp)) {
                if (less(node->data[0], data) and checkSingle(tmp->sons[0])
                                                  or less(node->data[0], data) and checkSingle(tmp->sons[1])) {
                    Node *sibling = getSibling(tmp);
                    if (checkSingle(sibling)) {
                        if (less(sibling->data[0], tmp->data[0])) {
                            std::swap(sibling, tmp);
                        }
                        int i = 0;
                        while (less(tmp->father->data[i], data))i++;
                        tmp->data.push_back(tmp->father->data[i]);
                        tmp->father->data.erase(tmp->father->data.begin() + i);
                        tmp->father->nodeSize--;
                        int j = 0;
                        while (node->father->sons[j] != sibling) j++;
                        node->father->sons.erase(node->father->sons.begin() + j);
                        tmp->data.push_back(sibling->data[0]);
                        tmp->sons.push_back(sibling->sons[0]);
                        tmp->sons.push_back(sibling->sons[1]);
                        delete sibling;
                        for (auto item:tmp->sons) {
                            item->father = tmp;
                        }
                        if (tmp->father->nodeSize == 0) {
                            tmp->father = tmp->father->father;
                            if (tmp->father->father != nullptr) {
                                for (auto item:tmp->father->father->sons) {
                                    if (item == node->father) item = tmp;
                                }
                            } else {
                                root = tmp;
                            }
                            delete tmp->father;
                        }
                    } else {
                        int i = 0;
                        while (less(tmp->father->data[i], tmp->data[0]))i++;
                        tmp->data.push_back(tmp->father->data[i]);
                        tmp->sons.push_back(sibling->sons[0]);
                        tmp->father->data[i] = sibling->data[0];
                        sibling->data.erase(sibling->data.begin());
                        sibling->sons.erase(sibling->sons.begin());
                    }
                }
            }
            int i = 0;
            while (less(tmp->data[i], data) and !less(data, tmp->data[i])) i++;
            if (!(less(tmp->data[i], data) xor less(data, tmp->data[i]))) {
                if (tmp->isLeaf) {
                    tmp->data.erase(tmp->data.begin() + i);
                    tmp->nodeSize--;
                    if (tmp == root and tmp->nodeSize == 0) {
                        delete tmp;
                        root = tmp = nullptr;
                    }
                } else {
                    Node *after = findNext(tmp, data);
                    assert(after != nullptr);
                    tmp->data[i] = after->data[0];
                    after->data[0] = data;
                }
            }
        }
        if (tmp != nullptr) {
            pushUp(tmp);
            //有可能有些节点的下放产生的4节点不能造成连续下放，所以还得再升回去
        }
    }

    Node *find(const T &data) {
        if (root == nullptr) return nullptr;
        Node *tmp = root;
        while (tmp != nullptr) {
            int i = 0;
            while (less(tmp->data[i], data) and !less(data, tmp->data[i])) i++;
            if (!(less(tmp->data[i], data) xor less(data, tmp->data[i]))) return tmp;
            tmp = tmp->sons[i];
        }
        return tmp;
    }

    Node *findNext(Node *node, const T &data) const {
        assert(node != nullptr);
        Node *tmp = node;
        int i = 0;
        while (i < node->nodeSize and less(node->data[i], data) and !less(data, node->data[i])) i++;
        if (!node->isLeaf)return findMin(node->sons[i + 1]);
        if (i < node->nodeSize) return node;
        while (tmp != nullptr) {
            if (tmp->father == nullptr)return nullptr;
            i = 0;
            while (i < node->father->nodeSize and less(node->father->data[i], data)
                   and !less(data, node->data[i])) {
                i++;
            }
            if (i < node->father->nodeSize) return findMin(node->father->sons[i + 1]);
            tmp = tmp->father;
        }
        return tmp;
    }

    Node *findPrev(Node *node, const T &data) const {
        assert(node != nullptr);
        Node *tmp = node;
        int i = 0;
        while (i < node->nodeSize and less(node->data[i], data) and !less(data, node->data[i])) i++;
        if (!node->isLeaf)return findMax(node->sons[i]);
        if (i > 0) return node;
        while (tmp != nullptr) {
            if (tmp->father == nullptr)return nullptr;
            i = 0;
            while (i < node->father->nodeSize and less(node->father->data[i], data)
                   and !less(data, node->data[i])) {
                i++;
            }
            if (i > 0) return findMax(node->father->sons[i]);
        }
        return tmp;
    }

    Node *findMin(Node *node) const {
        assert(node != nullptr);
        Node *tmp = node;
        while (!tmp->isLeaf) {
            assert(tmp != nullptr);
            tmp = tmp->sons[0];
        }
        return tmp;
    }

    Node *findMax(Node *node) const {
        assert(node != nullptr);
        Node *tmp = node;
        while (!tmp->isLeaf) {
            assert(tmp != nullptr);
            tmp = tmp->sons[tmp->nodeSize];
        }
        return tmp;
    }
};

#endif //DS2020_TREE23P_H
