/**
  * Created by Huang Jingcheng on 2020/9/20.
  * 201905130198@mail.sdu.edu.cn
*/
#include <iostream>
#include <algorithm>
#include <random>
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

static int data[100009];

int main() {
    int n;
    cin >> n;
    std::default_random_engine rng;
    std::uniform_int_distribution<int> generator(1, 20);
    ThreadBinaryTree<myInt> tree{};
    for (int i = 0; i < n; i++) {
        data[i] = generator(rng);
        tree.addNode(myInt(data[i]));
    }
    std::shuffle(data, data + n, std::mt19937(std::random_device()()));
    tree.forEach(false, [](myInt a) -> void { cout << a.data << " "; });
    tree.forEach(true, [](myInt a) -> void { cout << a.data << " "; });
    for (int i = 0; i < n; i++) {
        tree.delNode(myInt(data[i]));
    }
}