/**
 * Created by Clion.
 * User: icy
 * Date: 2020/9/21
 * i@icys.top
 */
#ifndef DS2020_TEST_H
#define DS2020_TEST_H


#include <bits/stdc++.h>
#include "Dinic.h"

using namespace std;

void testDinic() {
    int m, n, s, t;
    cin >> n >> m >> s >> t;
    DS2020::nodeList.resize(n);
    for (int i = 0; i < n; i++) {
        DS2020::nodeList[i].id = i;
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        DS2020::addEdge(u - 1, v - 1, w);
        DS2020::addEdge(v - 1, u - 1, 0);
    }
    cout << Dinic(s - 1, t - 1);
}

#endif