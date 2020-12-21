/**
 * Created by Clion.
 * User: Huang Jingcheng
 * Date: 2020/12/20
 * 201905130198@mail.sdu.edu.cn
 */

#ifndef DS2020_UNION_H
#define DS2020_UNION_H

#include <vector>

class Union {
    //route compressed.
    std::vector<int> nodeSet;
public:
    void init(int size) {
        nodeSet.resize(size);
        for (int i = 0; i < size; i++) {
            nodeSet[i] = i;
        }
    }

    int get(int pos) {
        return nodeSet[pos] = get(nodeSet[pos]);
    }

    void merge(int a, int b) {
        nodeSet[get(a)] = nodeSet[get(b)];
    }

    Union() = default;

    explicit Union(int size) {
        init(size);
    }

    bool checkSame(int a, int b) {
        return get(a) == get(b);
    }
};

#endif //DS2020_UNION_H
