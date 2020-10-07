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
    static void dualPivotSort(T *first, T *second, std::function<bool(T &a, T &b)> cmp) {
        Stack<Algorithm<T>::Data> stack;
        stack.push(Data(first, second));
        std::default_random_engine generator(time(nullptr));
        while (!stack.isEmpty()) {
            Data x = stack.top();
            stack.pop();
            T *fi = x._left, *se = x._right;
            int size = se - fi;
            if (size <= 1) continue;
            if (size == 2) {
                if (*fi > se[-1]) std::swap(*fi, se[-1]);
                continue;
            }
            std::uniform_int_distribution<int> distribution(1, size - 2);
            int random = distribution(generator);
            std::swap(fi[0], fi[random]);
            random = distribution(generator);
            std::swap(fi[size - 1], fi[random]);
            if (fi[0] == fi[size - 1]) {
                bool allSame = true;
                for (int *p = fi; p < se; p++) {
                    bool a = cmp(*p, fi[0]), b = cmp(fi[0], *p);
                    if ((a ^ b)) {
                        allSame = false;
                        std::swap(*p, fi[0]);
                        break;
                    }
                }
                if (allSame)continue;
            }
            if (fi[0] > fi[size - 1]) std::swap(fi[0], fi[size - 1]);
            //[fi, pointer1): ai <= p [pointer1, pointer2): p < ai < q
            //[pointer2, pointer3): unknown [pointer3, se): ai >=q
            T p = *fi, q = fi[size - 1];
            T *pointer1 = fi + 1, *pointer2 = fi + 1, *pointer3 = se - 1;
            while (pointer2 < pointer3) {
                if (cmp(*pointer2, p)) {
                    std::swap(*pointer2, pointer1[-1]);
                    pointer1++;
                    std::swap(*pointer2, pointer1[-1]);
                    pointer2++;
                } else if (cmp(*pointer2, q)) {
                    pointer2++;
                } else {
                    std::swap(*pointer2, pointer3[-1]);
                    std::swap(pointer3[-1], pointer3[0]);
                    pointer3--;
                }
            }
            auto push = [&](T *fi, T *se) -> void {
                if (fi + 1 < se) stack.push(Algorithm<T>::Data(fi, se));
            };
            push(fi, pointer1 - 1);
            push(pointer1, pointer2);
            push(pointer3 + 1, se);
        }
    }

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
//        qSort(first, second, cmp);
        dualPivotSort(first, second, cmp);
    }
};

#endif //DS2020_SORT_H
