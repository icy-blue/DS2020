/**
 * Created by Clion.
 * User: Huang Jingcheng
 * Date: 2020/12/17
 * 201905130198@mail.sdu.edu.cn
 */
#ifndef DS2020_DINIC_H
#define DS2020_DINIC_H

#include <vector>
#include <queue>
#include <stack>

class Edge {
public:
    int from, to, capacity;
};

class Node {
public:
    int id, depth;
    std::vector<int> edges;
};

std::vector<Edge> edgeList;
std::vector<Node> nodeList;

void addEdge(int from, int to, int capacity) {
    edgeList.push_back({from, to, capacity});
    edgeList.push_back({to, from, 0});
    nodeList[from].edges.push_back(edgeList.size() - 2);
    nodeList[to].edges.push_back(edgeList.size() - 1);
}

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
            if (edgeList[i].capacity == 0) continue;
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
        if (edge.capacity == 0) continue;
        int flow = dfs(source, destination, edge.to, std::min(validFlow, edge.capacity));
        if (flow > 0) {
            edgeList[i].capacity -= flow;
            edgeList[i ^ 1].capacity += flow;
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
