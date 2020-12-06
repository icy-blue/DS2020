/**
 * Created by Clion.
 * User: Huang Jingcheng
 * Date: 2020/12/5
 * 201905130198@mail.sdu.edu.cn
 */

#include <vector>
#include <queue>
#include <cassert>
#include <stack>
#include <optional>

namespace DS2020 {
#define TYPE_DISTANCE double
#define DISTANCE_MAX 1e10
#define DISTANCE_ZERO 0

    class Node;

    class Edge {
    public:
        Node *from, *to;
        TYPE_DISTANCE distance;

        Edge(Node *_from, Node *_to, TYPE_DISTANCE _distance) : from(_from), to(_to), distance(_distance) {}
    };

    class Node {
    public:
        int id; //from 0 to size(nodeList) - 1
        std::vector<Edge> edges;

        bool operator<(const Node &rt) const {
            return this->id < rt.id;
        } //comparable
    };

    std::vector<TYPE_DISTANCE> distance;
    std::vector<Node *> trace;
    std::vector<Node> nodeList;

    void dijkstra(const std::vector<Node> &nodes, const Node &source) {
        assert(!nodes.empty());
        distance.clear();
        distance.resize(nodes.size(), DISTANCE_MAX);
        trace.clear();
        trace.resize(nodes.size(), nullptr);
        std::vector<bool> visit(nodes.size());
        std::priority_queue<std::pair<TYPE_DISTANCE, Node>> priorityQueue;
        visit[source.id] = true;
        distance[source.id] = DISTANCE_ZERO;
        priorityQueue.push(std::make_pair(DISTANCE_ZERO, source));
        while (!priorityQueue.empty()) {
            auto[disNow, node] = priorityQueue.top();
            priorityQueue.pop();
            if (visit[node.id]) continue;
            visit[node.id] = true;
            for (auto edge: node.edges) {
                if (distance[edge.to->id] < disNow + edge.distance) {
                    distance[edge.to->id] = disNow + edge.distance;
                    priorityQueue.push(std::make_pair(distance[edge.to->id], *edge.to));
                    trace[edge.to->id] = &node;
                }
            }
        }
    }

    std::optional<std::stack<Node *>> traceRoute(Node &source, Node &destination) {
        assert(distance[source.id] == DISTANCE_ZERO);
        std::stack<Node *> stack;
        for (Node *now = &destination; now != &source; now = trace[now->id]) {
            if (now == nullptr) {
                return std::nullopt;
            }
            stack.push(now);
        }
        stack.push(&source);
        return stack;
    }

    void addEdgeFromID(int from, int to, TYPE_DISTANCE dis) {
        nodeList[from].edges.emplace_back(&nodeList[from], &nodeList[to], dis);
    }

    void addEdgeFromNode(Node *from, Node *to, TYPE_DISTANCE dis) {
        nodeList[from->id].edges.emplace_back(from, to, dis);
    }

    void printTrace(Node &source, Node &destination) {
        std::optional<std::stack<Node *>> result = traceRoute(source, destination);
        if (!result) {
            printf("Cannot find the route from Node %d to Node %d\n", source.id, destination.id);
        } else {
            printf("Route from Node %d to Node %d:\n", source.id, destination.id);
            while (!result->empty()) {
                Node *node = result->top();
                result->pop();
                printf("%d ", node->id);
            }
            puts("");
        }
    }
}