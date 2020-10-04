/**
  * Created by Huang Jingcheng on 2020/9/20.
  * 201905130198@mail.sdu.edu.cn
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include "ConvexHull.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main() {
    static vector<MyNode> nodes;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        double a, b;
        cin >> a >> b;
        nodes.emplace_back(i, a, b);
    }
    ConvexHull hull(nodes);
    int result = hull.getHull();

    for (int i = 1; i < result; i++) {
        printf("%d ", nodes[i].id);
    }
}