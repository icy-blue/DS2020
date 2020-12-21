/**
 * Created by Clion.
 * User: Huang Jingcheng
 * Date: 2020/12/21
 * 201905130198@mail.sdu.edu.cn
 */


#ifndef DS2020_EULER_H
#define DS2020_EULER_H

#include "Graph.h"
#include "Union.h"
#include <cassert>

class Euler {
    std::vector<int> edgeTrace;
    std::vector<bool> visit;

    int dfs(int u) {
        for (auto i : DS2020::nodeList[u].edges) {
            visit[i] = true;
            if (checkAllUnion()) getEulerRoute(DS2020::edgeList[i].to);
        }
    }

    bool checkAllUnion() {
        Union unionSet(DS2020::nodeList.size());
        std::vector<int> degree(DS2020::nodeList.size());
        for (const auto &edge: DS2020::edgeList) {
            if (visit[edge.id]) continue;
            degree[edge.from]++;
            degree[edge.to]++;
            if (unionSet.checkSame(edge.from, edge.to))continue;
            unionSet.merge(edge.from, edge.to);
        }
        int prev = -1;
        for (const auto &node:DS2020::nodeList) {
            if (degree[node.id] == 0)continue;
            if (prev == -1) {
                prev = unionSet.get(node.id);
            } else if (prev != unionSet.get(node.id)) {
                return false;
            }
        }
        return true;
    }

    bool checkAllVisited() {
        for (const auto &edge: DS2020::edgeList) {

        }
    }

public:
    std::vector<Edge> getEulerRoute(int source) {

    }

    Euler() {
        visit.resize(DS2020::edgeList.size());
    }

}

#endif //DS2020_EULER_H
