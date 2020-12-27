/**
 * Created by Clion.
 * User: icy
 * Date: 2020/9/30
 * i@icys.top
 */

#ifndef DS2020_CONVEXHULL_H
#define DS2020_CONVEXHULL_H

#include <algorithm>
#include <vector>
#include <iostream>

class MyNode {
public:
    int id, rank{};
    double x, y;

    MyNode(int _id, double _x, double _y) : id(_id), x(_x), y(_y) {}

    bool operator==(const MyNode &rt) const {
        return std::abs(x - rt.x) < 1e-8 and std::abs(y - rt.y) < 1e-8;
    }
};

class ConvexHull {
    std::vector<MyNode> &innerNodes;
    const double eps = 1e-6;

    double cross(int a1, int a2, int b, int start, int length) {
        a1 -= start, a2 -= start;
        a1 += length, a2 += length;
        a1 %= length, a2 %= length;
        a1 += start, a2 += start;
        double x1 = innerNodes[b].x - innerNodes[a1].x;
        double x2 = innerNodes[b].x - innerNodes[a2].x;
        double y1 = innerNodes[b].y - innerNodes[a1].y;
        double y2 = innerNodes[b].y - innerNodes[a2].y;
        return x1 * y2 - x2 * y1;
    }

    void roll(int l, int r, bool isLeft) {
        std::vector<MyNode> tmp;
        for (int i = l; i < r; i++) {
            tmp.push_back(innerNodes[i]);
        }
        int num = 0;
        for (int i = 0; i < r - l; i++) {
            if (isLeft) num = tmp[i].rank > tmp[num].rank ? i : num;
            else num = tmp[i].rank < tmp[num].rank ? i : num;
        }
        for (int i = 0; i < r - l; i++) {
            if (isLeft) innerNodes[i + l] = tmp[(i + num) % (r - l)];
            else innerNodes[i + l] = tmp[(i + num + 1) % (r - l)];
        }
        tmp.clear();
    }

    int merge(int l, int mid, int r, int lengthA, int lengthB) {
        int p = l, q = mid + lengthB - 1, checked = 0;
        std::vector<MyNode> tmp;
        int a1, a2, b1, b2;
        while (checked < lengthA + lengthB) {
            for (int i = 0; i < lengthB; i++) {
                checked++;
                if (cross(q - 1, q, p, mid, lengthB) > -eps and
                    cross(q, q + 1, p, mid, lengthB) < eps) {
                    break;
                }
                q = (q - 1 + lengthB - mid) % lengthB + mid;
            }
            for (int i = 0; i < lengthA; i++) {
                checked++;
                if (cross(p - 1, p, q, l, lengthA) < eps and
                    cross(p, p + 1, q, l, lengthA) > -eps) {
                    break;
                }
                p = (p + 1 + lengthA - l) % lengthA + l;
            }
            if (cross(q - 1, q, p, mid, lengthB) > -eps and
                cross(q, q + 1, p, mid, lengthB) < eps and
                cross(p - 1, p, q, l, lengthA) < eps and
                cross(p, p + 1, q, l, lengthA) > -eps) {
                a1 = p, b1 = q;
                break;
            }
        }
        p = l, q = mid + lengthB - 1, checked = 0;
        while (checked < lengthA + lengthB) {
            for (int i = 0; i < lengthA; i++) {
                checked++;
                if (cross(q - 1, q, p, mid, lengthB) < eps and
                    cross(q, q + 1, p, mid, lengthB) > -eps) {
                    break;
                }
                q = (q + 1 - mid + lengthB) % lengthB + mid;
            }
            for (int i = 0; i < lengthB; i++) {
                checked++;
                if (cross(p - 1, p, q, l, lengthA) > -eps and
                    cross(p, p + 1, q, l, lengthA) < eps) {
                    break;
                }
                p = (p - 1 - l + lengthA) % lengthA + l;
            }
            if (cross(q - 1, q, p, mid, lengthB) < eps and
                cross(q, q + 1, p, mid, lengthB) > -eps and
                cross(p - 1, p, q, l, lengthA) > -eps and
                cross(p, p + 1, q, l, lengthA) < eps) {
                a2 = p, b2 = q;
                break;
            }
        }
        for (int i = b2; i != b1; i = (i - mid + 1) % lengthB + mid) {
            tmp.push_back(innerNodes[i]);
        }
        tmp.push_back(innerNodes[b1]);
        for (int i = a1; i != a2; i = (i - l + 1) % lengthA + l) {
            tmp.push_back(innerNodes[i]);
        }
        tmp.push_back(innerNodes[a2]);
        int len = tmp.size();
        for (int i = 0; i < len; i++) {
            innerNodes[l + i] = tmp[i];
        }
        tmp.clear();
        return len;
    }


//[l,r)
    int solve(int l, int r) {
        int length = r - l;
        if (length < 3) return length;
        if (length == 3) {
            if ((innerNodes[l + 1].x - innerNodes[l].x) * (innerNodes[l + 2].y - innerNodes[l].y) -
                (innerNodes[l + 2].x - innerNodes[l].x) * (innerNodes[l + 1].y - innerNodes[l].y) < 0) {
                std::swap(innerNodes[l + 1], innerNodes[l + 2]); //逆时针
            }
            return 3;
        }
        int mid = (l + r) >> 1;
        int lenA = solve(l, mid);
        int lenB = solve(mid, r);
        roll(l, l + lenA, true);
        roll(mid, mid + lenB, false);
        return merge(l, mid, r, lenA, lenB);
    }

public:
    int getHull() {
        std::sort(innerNodes.begin(), innerNodes.end(), [](MyNode &a, MyNode &b) -> bool {
            if (a.x == b.x) return a.y < b.y;
            return a.x < b.x;
        });
        int length = std::unique(innerNodes.begin(), innerNodes.end()) - innerNodes.begin();
        for (int i = 0; i < length; i++) {
            innerNodes[i].rank = i;
        }
        return solve(0, length);
    }

    explicit ConvexHull(std::vector<MyNode>
                        &nodes) : innerNodes(nodes) {}
};

#endif //DS2020_CONVEXHULL_H
