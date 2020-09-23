/**
  * Created by Huang Jingcheng on 2020/9/21.
  * 201905130198@mail.sdu.edu.cn
*/

#ifndef DS2020_SORT_H
#define DS2020_SORT_H

#include "Stack.h"

template<typename T>
class Algorithm {
private:
    static void qSort(T *first, T *second) {
        Stack<Algorithm<T>::Data> stack;
        stack.push(Data(first, second));
        while (!stack.isEmpty()) {
            Data x = stack.top();
            stack.pop();
            T *fi = x._left, *se = x._right;
            int size = se - fi;
            if (size <= 1) continue;
            int l = 0, r = size - 1, pivot = fi[l];
            while (l < r) {
                while (l < r and fi[r] > pivot) r--;
                if (l < r) fi[l++] = fi[r];
                while (l < r and fi[l] < pivot) l++;
                if (l < r) fi[r--] = fi[l];
            }
            fi[l] = pivot;
            stack.push(Data(fi, fi + l));
            stack.push(Data(fi + l + 1, se));
        }
    }

    class Data {
    public:
        int *_left, *_right;

        explicit Data(int *left, int *right) : _left(left), _right(right) {}
    };

public:
    static void sort(T *first, T *second, std::function<bool(T &a, T &b)> cmp = [](T &a, T &b) -> bool {
        return a < b;
    }) {
        if (second - first < 0) throw "RangeCheckError";
        qSort(first, second);
    }
};

#endif //DS2020_SORT_H
