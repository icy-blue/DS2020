/**
 * Created by Clion.
 * User: icy
 * Date: 2020/12/21
 * i@icys.top
 */

#ifndef DS2020_GRAPH_H
#define DS2020_GRAPH_H

#include <vector>

namespace DS2020 {
    class Edge {
    public:
        int from, to, distance;
    };

    class Node {
    public:
        int id, depth;
        std::vector<int> edges;
    };

    std::vector<Edge> edgeList;
    std::vector<Node> nodeList;

    void addEdge(int from, int to, int distance) {
        edgeList.push_back({from, to, distance});
        nodeList[from].edges.push_back(edgeList.size() - 1);
    }
}
#endif //DS2020_GRAPH_H
