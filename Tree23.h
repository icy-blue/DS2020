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

template<typename T, typename Container = std::vector<T>, typename less = std::less<typename Container::value_type>>
class Tree23 {
    class Node {
    public:
        Node *leftSon, *midSon, *rightSon, *father;
        T data1, data2;
        int nodeSize = 1, treeSize = 1;
        bool isLeaf = true;
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
        T tmpData;
        auto needUpdate = false;
        while (node != nullptr) {
            if (node->isLeaf) {
                if (node->nodeSize == 1) {
                    node->data2 = node->data1;
                    if (less(node->data2, node->data1)) {
                        std::swap(node->data1, node->data2);
                    }
                    node->nodeSize++, node->treeSize++;
                } else {
                    T insertArray[3] = {node->data1, node->data2, data};
                    std::sort(insertArray, insertArray + 3);
                    tmpData = insertArray[1];
                    needUpdate = true;
                }
            } else {

            }
//            if (less(data, node->data1)) {

//                } else node = node->leftSon;
//            } else if (node->nodeSize == 1) {
//                if (node->isLeaf) {
//                    node->data2 = data;
//                } else {
//                    node = node->midSon;
//                }
//            } else if (less(data, node->data2)) {
//                if (node->isLeaf) {
//                    tmpData = data;
//                    needUpdate = true;
//                } else {
//
//                }
//            }
        }
    }
};

#endif //DS2020_TREE23_H
