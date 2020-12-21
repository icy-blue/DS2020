/**
 * Created by Clion.
 * User: Huang Jingcheng
 * Date: 2020/12/21
 * 201905130198@mail.sdu.edu.cn
 */

#ifndef DS2020_GRAPH_H
#define DS2020_GRAPH_H

#include <vector>

namespace DS2020 {
    class Edge {
    public:
        static int cnt;
        int id, from, to, distance;
    };

    class Node {
    public:
        int id, depth;
        std::vector<int> edges;
    };

    std::vector<Edge> edgeList;
    std::vector<Node> nodeList;

    void addEdge(int from, int to, int distance) {
        edgeList.push_back({Edge::cnt, from, to, distance});
        nodeList[from].edges.push_back(Edge::cnt++);
    }
}
#endif //DS2020_GRAPH_H
