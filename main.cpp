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

/*
4
4 8
4 12
5 9.3
7 8
*/

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
    double ans = 0;
    auto getDistance = [](MyNode &a, MyNode &b) -> double {
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    };
    for (int i = 1; i < result; i++) {
        ans += getDistance(nodes[i], nodes[i - 1]);
    }
    ans += getDistance(nodes[0], nodes[result - 1]);
    cout << ans << endl;
}