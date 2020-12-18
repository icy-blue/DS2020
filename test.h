/**
  * Created by Huang Jingcheng on 2020/9/21.
  * 201905130198@mail.sdu.edu.cn
*/

#ifndef DS2020_TEST_H
#define DS2020_TEST_H


#include <bits/stdc++.h>
#include "Dinic.h"

using namespace std;

void testDinic() {
    int m, n, s, t;
    cin >> n >> m >> s >> t;
    nodeList.resize(n);
    for (int i = 0; i < n; i++) {
        nodeList[i].id = i;
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(u - 1, v - 1, w);
    }
    cout << Dinic(s - 1, t - 1);
}

#endif