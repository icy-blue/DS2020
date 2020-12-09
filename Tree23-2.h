/**
 * Created by Clion.
 * User: Huang Jingcheng
 * Date: 2020/12/8
 * 201905130198@mail.sdu.edu.cn
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
                node1->sons.push_back(node.sons[0]);
                node1->sons.push_back(node.sons[1]);
                node1->data.push_back(node.data[0]);
                node2->sons.push_back(node.sons[2]);
                node2->sons.push_back(node.sons[3]);
                node2->data.push_back(node.data[2]);
                node1->father = node2->father = node;
                node1->isLeaf = node2->isLeaf = node->isLeaf;
                node1->depth = node2->depth = node1->depth;
                T data = node.data[1];
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

    Node *findNext(Node *node, const T &data) const {
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
};

#endif //DS2020_TREE23P_H
