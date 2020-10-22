/**
  * Created by Huang Jingcheng on 2020/9/20.
  * 201905130198@mail.sdu.edu.cn
*/
#include <bits/stdc++.h>
#include "ThreadedBinaryTree.h"
#include "Tree.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class myInt {
public:
    int data;

    explicit myInt(int _data) : data(_data) {}

    bool operator<(const myInt &rt) const {
        return data < rt.data;
    }
};

int main() {
    int n, data;
    cin >> n;
    ThreadBinaryTree<myInt> tree{};
    for (int i = 0; i < n; i++) {
        cin >> data;
        tree.addNode(myInt(data));
    }
}