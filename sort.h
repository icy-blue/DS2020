/**
  * Created by Huang Jingcheng on 2020/9/21.
  * 201905130198@mail.sdu.edu.cn
*/

#ifndef DS2020_SORT_H
#define DS2020_SORT_H

#include <random>
#include <ctime>
#include "Stack.h"

template<typename T>
class Algorithm {
private:
    static void qSort(T *first, T *second, std::function<bool(T &a, T &b)> cmp) {
        Stack<Algorithm<T>::Data> stack;
        stack.push(Data(first, second));
        std::default_random_engine generator(time(nullptr));
        while (!stack.isEmpty()) {
            Data x = stack.top();
            stack.pop();
            T *fi = x._left, *se = x._right;
            int size = se - fi;
            if (size <= 1) continue;
            std::uniform_int_distribution<int> distribution(0, size - 1);
            int random = distribution(generator);
            std::swap(fi[0], fi[random]);
            int l = 0, r = size - 1, pivot = fi[0];
            while (l < r) {
                while (l < r and cmp(pivot, fi[r])) r--;
                if (l < r) fi[l++] = fi[r];
                while (l < r and cmp(fi[l], pivot)) l++;
                if (l < r) fi[r--] = fi[l];
            }
            fi[l] = pivot;
            if (l > 1)
                stack.push(Data(fi, fi + l));
            if (se - l - 2 >= fi)
                stack.push(Data(fi + l + 1, se));
        }
    }

    static void stableSort(T *first, T *second, std::function<bool(T &a, T &b)> cmp) {
        int length = second - first;
        std::vector<T> tmp(length);
        Stack<Data> stack;
        stack.push(Data(first, second));
        while (!stack.isEmpty()) {
            Data x = stack.top();
            stack.pop();
            T *fi = x._left, *se = x._right;
            unsigned int size = se - fi;
            if (size <= 1) continue;
            int mid = fi + (size >> 1u);
            stack.push(Data(fi, mid));
            stack.push(Data(mid + 1, se));

        }
    }

    class Data {
    public:
        T *_left, *_right;

        explicit Data(T *left, T *right) : _left(left), _right(right) {}
    };

public:
    static void sort(T *first, T *second, std::function<bool(T &a, T &b)> cmp = [](T &a, T &b) -> bool {
        return a < b;
    }) {
        if (second < first) throw "RangeCheckError";
        qSort(first, second, cmp);
    }
};

#endif //DS2020_SORT_H
