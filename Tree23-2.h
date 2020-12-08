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

    void insert(T data) {
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
        assert(node != nullptr);
        while (node) {
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
                node->data.clear();
                node->sons.clear();
                node->data[0] = data;
                node->sons[0] = node1;
                node->sons[1] = node2;
                node->isLeaf = false;
                node->depth++;
            }
            if (node->father != nullptr) {
                node->father->depth = node->depth + 1;
            }
        }
    }
};

#endif //DS2020_TREE23P_H
