/**
 * Created by Clion.
 * User: Huang Jingcheng
 * Date: 2020/12/20
 * 201905130198@mail.sdu.edu.cn
 */

#ifndef DS2020_KRUSKAL_H
#define DS2020_KRUSKAL_H

#include "Union.h"
#include "Graph.h"
#include <algorithm>

namespace DS2020 {
    std::vector<Edge> kruskal(std::vector<Node> &_nodeList, std::vector<Edge> _edgeList) {
        std::vector<Edge> result;
        Union unionSet(_nodeList.size());
        std::sort(_edgeList.begin(), _edgeList.end(),
                  [](const Edge &a, const Edge &b) -> bool { return a.distance < b.distance; });
        for (auto edge: _edgeList) {
            if (!unionSet.checkSame(edge.from, edge.to))continue;
            unionSet.merge(edge.from, edge.to);
            result.push_back(edge);
        }
        return result;
    }
}
#endif //DS2020_KRUSKAL_H
