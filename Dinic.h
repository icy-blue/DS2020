/**
 * Created by Clion.
 * User: Huang Jingcheng
 * Date: 2020/12/17
 * 201905130198@mail.sdu.edu.cn
 */
#ifndef DS2020_DINIC_H
#define DS2020_DINIC_H

#include <vector>

class Edge {
public:
    int from, to, distance;
};

std::vector<Edge> edgeList;

void addEdge(int from, int to, int distance) {
    edgeList.emplace_back(from, to, distance);
    edgeList.emplace_back(to, from, 0);
}

std::vector<int> bfs(int source) {
    std::vector<int>
}

#endif //DS2020_DINIC_H
