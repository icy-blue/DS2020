/**
 * Created by Clion.
 * User: Huang Jingcheng
 * Date: 2020/12/1
 * 201905130198@mail.sdu.edu.cn
 */

#ifndef DS2020_TREE23_H
#define DS2020_TREE23_H

#include <vector>
#include <functional>
#include <algorithm>
#include <cassert>

template<typename T, typename Container = std::vector<T>, typename less = std::less<typename Container::value_type>>
class Tree23 {
#define SIZE_DATA 2

    class Node {
    public:
        Node *sons[SIZE_DATA + 1], *father;
        T data[SIZE_DATA];
        int nodeSize = 1, treeSize = 1;
        bool isLeaf = true;
    };

    class TmpNode {
    public:
        Node *sons[SIZE_DATA + 2], *father;
        T data[SIZE_DATA + 1];
        int nodeSize = 1, treeSize = 1;
        bool isLeaf = true;

        explicit TmpNode(const Node &node) {
            for (auto i = 0; i < node.nodeSize; i++) {
                this->sons[i] = node.sons[i];
                this->data[i] = node.data[i];
            }
            this->sons[node.nodeSize] = node.sons[node.nodeSize];
            this->father = node.father;
            this->nodeSize = node.nodeSize;
            this->treeSize = node.treeSize;
            this->isLeaf = node.isLeaf;
        }

        TmpNode() = default;

        TmpNode operator+(const Node &node) {
            auto origin = TmpNode(node);

        }
    };

public:
    Tree23() = default;

    Node *root;

    void insert(T data) {
        if (root == nullptr) {
            root = new Node();
            root->data1 = data;
            return;
        }
        auto node = root;
        TmpNode *tmpNode;
        auto needUpdate = false;
        while (true) {
            assert(node != nullptr);
            if (node->isLeaf) {
                if (node->nodeSize == 1) {
                    node->data[1] = data;
                    if (less(node->data[0], node->data[1])) {
                        std::swap(node->data[0], node->data[1]);
                    }
                    node->nodeSize++, node->treeSize++;
                } else {
                    T insertArray[3] = {node->data[0], node->data[1], data};
                    std::sort(insertArray, insertArray + 3);
                    Node *leftSon = new Node, *rightSon = new Node;
                    tmpNode = new TmpNode;
                    leftSon->father = rightSon->father = tmpNode;
                    leftSon->data[0] = insertArray[0];
                    rightSon->data[0] = insertArray[2];
                    tmpNode->data[0] = insertArray[1];
                    tmpNode->sons[0] = leftSon;
                    tmpNode->sons[1] = rightSon;
                    tmpNode->isLeaf = false;
                    needUpdate = true;
                    break;
                }
            } else {
                auto i = 0;
                while (i < node->nodeSize && less(data, node->data[i]) {
                    i++;
                }
                node = node->sons[i];
            }
        }
        while (needUpdate) {
            needUpdate = false;
            auto i = 0;
            while (i < node->father->nodeSize && less(node->father->data[i], tmpData) {
                i++;
            }
            tmpNode.sons[SIZE_DATA + 1] = tmpNode.sons[SIZE_DATA];
            for (int j = node->nodeSize - 1; j >= i; j++) {
                tmpNode.sons[j + 1] = tmpNode.sons[j];
                tmpNode.data[j + 1] = tmpNode.data[j];
            }
            tmpNode.sons[i] =
        }
    }
};

#endif //DS2020_TREE23_H
