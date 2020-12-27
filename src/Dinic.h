/**
 * Created by Clion.
 * User: Huang Jingcheng
 * Date: 2020/12/17
 * 201905130198@mail.sdu.edu.cn
 */
#ifndef DS2020_DINIC_H
#define DS2020_DINIC_H

#include "Graph.h"
#include <vector>
#include <queue>
#include <stack>

void bfs(int source) {
    std::vector<bool> visited(nodeList.size());
    std::queue<int> queue;
    queue.push(source);
    visited[source] = true;
    while (!queue.empty()) {
        auto x = queue.front();
        queue.pop();
        for (auto i: nodeList[x].edges) {
            if (visited[edgeList[i].to]) continue;
            if (edgeList[i].distance == 0) continue;
            visited[edgeList[i].to] = true;
            nodeList[edgeList[i].to].depth = nodeList[x].depth + 1;
            queue.push(edgeList[i].to);
        }
    }
}

int dfs(const int &source, const int &destination, int node, int validFlow) {
    if (node == destination) return validFlow;
    int sum = 0;
    for (auto i: nodeList[node].edges) {
        auto edge = edgeList[i];
        if (nodeList[edge.to].depth != nodeList[edge.from].depth + 1) continue;
        if (edge.distance == 0) continue;
        int flow = dfs(source, destination, edge.to, std::min(validFlow, edge.distance));
        if (flow > 0) {
            edgeList[i].distance -= flow;
            edgeList[i ^ 1].distance += flow;
            validFlow -= flow;
            sum += flow;
        } else {
            nodeList[edge.to].depth = -1;
        }
    }
    return sum;
}

int Dinic(const int &source, const int &destination) {
    int flow = 0, delta;
    do {
        bfs(source);
        delta = dfs(source, destination, source, (int) (1e9));
        flow += delta;
    } while (delta != 0);
    return flow;
}

#endif //DS2020_DINIC_H
