/**
  * Created by Huang Jingcheng on 2020/9/20.
  * 201905130198@mail.sdu.edu.cn
*/
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include "AVLTree.h"
#include "Tree.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

AVLTree<int> tree;

int main() {
    int n;
    cin >> n;
    for (auto i = 0; i < n; i++) {
        int cmd, x;
        cin >> cmd >> x;
        switch (cmd) {
            case 1:
                tree.push(x);
                break;
            case 2:
                tree.del(x);
                break;
            case 3:
                cout << tree.rank(x) + 1 << endl;
                break;
            case 4:
                std::optional<int> oi = tree.getRankOf(x - 1);
                if (oi) cout << *oi << endl;
                break;
//            case 5:

        }
    }
}