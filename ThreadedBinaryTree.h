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
        Node *leftSon = nullptr, *rightSon = nullptr;
        T data;
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
    enum class Type {
        VisitLeftSon, VisitRightSon, VisitRoot, Query, PreorderTraversal, InorderTraversal, PostorderTraversal
    };

    class BuildState {
        friend class ThreadBinaryTree;

    private:
        Type type;
        Node *parent;

        explicit BuildState(Type _type, Node *_parent) :
                type(_type), parent(_parent) {}
    };

    void makeTree(const std::vector<int> &front, const std::vector<int> &mid) {
        assert(front.size() == mid.size());
        int frontIndex = 0;
        Stack<BuildState> stack;
        stack.push(BuildState(Type::VisitRoot, nullptr));
        while (!stack.isEmpty()) {
            const BuildState &state = stack.top();
            stack.pop();
            switch (state.type) {
                case Type::VisitLeftSon:

                    break;
                case Type::VisitRightSon:

                    break;
                case Type::VisitRoot:

                default:;
            }

        }
    }

    void addNode(T element) {
        if (root == nullptr) {
            root = Node(element);
            return;
        }
        Stack<BuildState> stack;
        stack.push(BuildState(Type::VisitRoot, nullptr));
        Node *tmp = root;
        Node *newNode = new Node(element);
        while (true) {
            if (cmp(element, tmp->data)) {
                if (!tmp->leftUsed) {
                    newNode->rightSon = tmp;
                    newNode->leftSon = tmp->leftSon;
                    tmp->leftSon = newNode;
                    tmp->leftUsed = 1;
                    break;
                } else tmp = tmp->leftSon;
            } else {
                if (!tmp->rightUsed) {
                    newNode->leftSon = tmp;
                    newNode->rightSon = tmp->rightSon;
                    tmp->rightSon = newNode;
                    tmp->leftUsed = 1;
                    break;
                } else tmp = tmp->rightSon;
            }
        }
    }

    void findNode(T element) {

    }

    void delNode(T element) {

    }
};

#endif //DS2020_THREADEDBINARYTREE_H
