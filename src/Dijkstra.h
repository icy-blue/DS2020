/**
 * Created by Clion.
 * User: Huang Jingcheng
 * Date: 2020/12/5
 * 201905130198@mail.sdu.edu.cn
 */

#ifndef DS2020_DIJKSTRA_H
#define DS2020_DIJKSTRA_H

#include <vector>
#include <queue>
#include <cassert>
#include <stack>
#include <optional>
#include "Graph.h"

namespace DS2020 {
#define TYPE_DISTANCE int
#define DISTANCE_MAX (TYPE_DISTANCE)(1e9)
#define DISTANCE_ZERO 0

    std::vector<TYPE_DISTANCE> distance;
    std::vector<int> trace;

    void dijkstra(const std::vector<Node> &nodes, const Node &source) {
        assert(!nodes.empty());
        distance.clear();
        distance.resize(nodes.size(), DISTANCE_MAX);
        trace.clear();
        trace.resize(nodes.size(), -1);
        std::vector<bool> visit(nodes.size());
        std::priority_queue<std::pair<TYPE_DISTANCE, int>> priorityQueue;
        visit[source.id] = true;
        distance[source.id] = DISTANCE_ZERO;
        priorityQueue.push({DISTANCE_ZERO, source.id});
        while (!priorityQueue.empty()) {
            auto[disNow, id] = priorityQueue.top();
            priorityQueue.pop();
            if (visit[id]) continue;
            visit[id] = true;
            for (auto edge: nodeList[id].edges) {
                if (distance[edgeList[edge].to] < disNow + edgeList[edge].distance) {
                    distance[edgeList[edge].to] = disNow + edgeList[edge].distance;
                    priorityQueue.push({distance[edgeList[edge].to], nodeList[edgeList[edge].to].id});
                    trace[edgeList[edge].to] = id;
                }
            }
        }
    }

    std::optional<std::stack<int>> traceRoute(Node &source, Node &destination) {
        assert(distance[source.id] == DISTANCE_ZERO);
        std::stack<int> stack;
        for (Node *now = &destination; now != &source; now = &nodeList[trace[now->id]]) {
            if (now == nullptr) {
                return std::nullopt;
            }
            stack.push(now->id);
        }
        stack.push(source.id);
        return stack;
    }

    void printTrace(Node &source, Node &destination) {
        std::optional<std::stack<int>> result = traceRoute(source, destination);
        if (!result) {
            printf("Cannot find the route from Node %d to Node %d\n", source.id, destination.id);
        } else {
            printf("Route from Node %d to Node %d:\n", source.id, destination.id);
            while (!result->empty()) {
                int id = result->top();
                result->pop();
                printf("%d ", id);
            }
            puts("");
        }
    }
}
#endif //DS2020_DIJKSTRA_H
