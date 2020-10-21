/**
  * Created by Huang Jingcheng on 2020/10/14.
  * 201905130198@mail.sdu.edu.cn
*/

#ifndef DS2020_TREE_H
#define DS2020_TREE_H

#include "Stack.h"
#include <cassert>
#include <vector>
#include <functional>

class Tree {
public:
    class Node {
    public:
        Node *leftSon = nullptr, *rightSon = nullptr;
        int id;

        explicit Node(int _id) : id(_id) {}
    };

private:
    enum class Type {
        VisitLeftSon, VisitRightSon, VisitRoot, Query, PreorderTraversal, InorderTraversal, PostorderTraversal
    };

    class BuildState {
        friend class Tree;

    private:
        Type type;
        int lt, rt;
        Node *parent;

        explicit BuildState(Type _type, int left, int right, Node *_parent) :
                type(_type), lt(left), rt(right), parent(_parent) {}
    };

    class TraversalState {
        friend class Tree;

    private:
        Type type;
        Node *node;

        explicit TraversalState(Type _type, Node *_node) : type(_type), node(_node) {}
    };

    Node *root;
public:
    void makeTree(const std::vector<int> &front, const std::vector<int> &mid) {
        assert(front.size() == mid.size());
        int frontIndex = 0;
        Stack<BuildState> stack;
        stack.push(BuildState(Type::VisitRoot, 0, front.size(), nullptr));
        while (!stack.isEmpty()) {
            const BuildState &state = stack.top();
            stack.pop();
            Node *newNode = new Node(front[frontIndex]);
            switch (state.type) {
                case Type::VisitLeftSon:
                    state.parent->leftSon = newNode;
                    break;
                case Type::VisitRightSon:
                    state.parent->rightSon = newNode;
                    break;
                case Type::VisitRoot:
                    root = newNode;
                default:;
            }
            int midIndex = state.lt;
            while (mid[midIndex] != front[frontIndex])midIndex++;
            if (state.lt < midIndex)
                stack.push(BuildState(Type::VisitLeftSon, state.lt, midIndex, newNode));
            if (midIndex + 1 < state.rt)
                stack.push(BuildState(Type::VisitRightSon, midIndex + 1, state.rt, newNode));
            frontIndex++;
        }
    }

    ~Tree() {
        traversalTree(Type::PostorderTraversal, [](Node *x) -> void { delete x; });
    }

    void traversalTree(Type traversalType, const std::function<void(Node *)> &function) {
        Stack<TraversalState> stack;
        auto solve = [&](Node *x) -> void {
            assert(x != nullptr);
            switch (traversalType) {
                case Type::PreorderTraversal:
                    if (x->rightSon != nullptr)stack.push(TraversalState(Type::VisitRightSon, x));
                    if (x->leftSon != nullptr)stack.push(TraversalState(Type::VisitLeftSon, x));
                    stack.push(TraversalState(Type::Query, x));
                    break;
                case Type::InorderTraversal:
                    if (x->rightSon != nullptr)stack.push(TraversalState(Type::VisitRightSon, x));
                    stack.push(TraversalState(Type::Query, x));
                    if (x->leftSon != nullptr)stack.push(TraversalState(Type::VisitLeftSon, x));
                    break;
                case Type::PostorderTraversal:
                    stack.push(TraversalState(Type::Query, x));
                    if (x->rightSon != nullptr)stack.push(TraversalState(Type::VisitRightSon, x));
                    if (x->leftSon != nullptr)stack.push(TraversalState(Type::VisitLeftSon, x));
                    break;
                default:;
            }
        };
        solve(root);
        while (!stack.isEmpty()) {
            auto state = stack.top();
            switch (state.type) {
                case Type::VisitLeftSon:
                    assert(state.node->leftSon != nullptr);
                    solve(state.node->leftSon);
                    break;
                case Type::VisitRightSon:
                    assert(state.node->rightSon != nullptr);
                    solve(state.node->rightSon);
                    break;
                case Type::Query:
                    function(state.node);
                    break;
                default:;
            }
        }
    }
};


#endif //DS2020_TREE_H
