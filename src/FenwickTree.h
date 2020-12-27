/**
 * Created by Clion.
 * User: icy
 * Date: 2020/11/4
 * i@icys.top
 */

#ifndef DS2020_FENWICKTREE_H
#define DS2020_FENWICKTREE_H

#include <vector>
#include <optional>
#include <cassert>

template<typename T>
class FenwickTree {
    int _size;

    std::vector<T> vector;

    T _templateValue;

    static inline int lowbit(int x);

    bool rangeCheck(int pos) const;

public:
    int size() const;

    bool add(int pos, T data);

    std::optional<T> queryNode(int pos) const;

    std::optional<T> queryRange(int l, int r) const;

    std::optional<T> querySum(int pos) const;

    explicit FenwickTree(int size, T templateValue);

    explicit FenwickTree(std::vector<T> array);
};

template<typename T>
int FenwickTree<T>::size() const {
    return _size;
}

template<typename T>
int FenwickTree<T>::lowbit(int x) {
    return x & -x;
}

template<typename T>
FenwickTree<T>::FenwickTree(int size, T templateValue):_templateValue(templateValue) {
    _size = size;
    vector.resize(size, templateValue);
}

template<typename T>
bool FenwickTree<T>::add(int pos, T data) {
    if (!rangeCheck(pos))return false;
    while (pos < _size) {
        vector[pos] += data;
        pos += lowbit(pos);
    }
}

template<typename T>
bool FenwickTree<T>::rangeCheck(int pos) const {
    return pos >= 0 and pos < _size;
}

template<typename T>
std::optional<T> FenwickTree<T>::queryNode(int pos) const {
    return queryRange(pos, pos);
}

template<typename T>
std::optional<T> FenwickTree<T>::queryRange(int l, int r) const {
    if (l > r)return std::nullopt;
    if (l == 1) return querySum(r);
    auto leftSum = querySum(l - 1), rightSum = querySum(r);
    if (!leftSum || !rightSum)return std::nullopt;
    return *rightSum - *leftSum;
}

template<typename T>
std::optional<T> FenwickTree<T>::querySum(int pos) const {
    if (!rangeCheck(pos)) return std::nullopt;
    T base = _templateValue;
    while (pos >= 0) {
        base += vector[pos];
        pos -= lowbit(pos);
    }
    return base;
}

template<typename T>
FenwickTree<T>::FenwickTree(std::vector<T> array):_templateValue(array[0]) {
    assert(!array.empty());
    vector.resize(array.size(), array[0]);
    _size = array.size();
    for (auto i = 1; i < array.size(); i++) {
        vector[i] += array[i];
        int next = i + lowbit(i);
        if (next < array.size())vector[next] += array[i];
    }
}

#endif //DS2020_FENWICKTREE_H
