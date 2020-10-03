/**
  * Created by Huang Jingcheng on 2020/9/30.
  * 201905130198@mail.sdu.edu.cn
*/

#ifndef DS2020_CONVEXHULL_H
#define DS2020_CONVEXHULL_H

#include <algorithm>
#include <vector>
#include <algorithm>

class MyNode {
public:
    int id, rank{};
    double x, y;

    MyNode(int _id, double _x, double _y) : id(_id), x(_x), y(_y) {}

    bool operator==(const MyNode &rt) const {
        return x == rt.x and y == rt.y;
    }
};

class ConvexHull {
    std::vector<MyNode> &_nodes;

    double cross(int a1, int a2, int b, int start, int length) {
        a1 -= start, a2 -= start;
        a1 += length, a2 += length;
        a1 %= length, a2 %= length;
        a1 += start, a2 += start;
        double x1 = _nodes[b].x - _nodes[a1].x;
        double x2 = _nodes[b].x - _nodes[a2].x;
        double y1 = _nodes[b].y - _nodes[a1].y;
        double y2 = _nodes[b].y - _nodes[a2].y;
        return x1 * y2 - x2 * y1;
    }

    int merge(int l, int mid, int r, int lengthA, int lengthB) {
        int p = l + lengthA - 1, q = mid, checked = 0;
        std::vector<MyNode> tmp;
        int a1, a2, b1, b2;
        while (checked < lengthA + lengthB) {
            for (; q < lengthB; q++) {
                checked++;
                if (cross(q - 1, q, p, mid, r - mid) > 0 and
                    cross(q, q + 1, p, mid, r - mid) < 0) {
                    break;
                }
            }
            for (; p >= l; p--) {
                checked++;
                if (cross(p - 1, p, q, l, mid - l) < 0 and
                    cross(p, p + 1, q, l, mid - l) > 0) {
                    break;
                }
            }
            if (cross(q - 1, q, p, mid, r - mid) > 0 and
                cross(q, q + 1, p, mid, r - mid) < 0 and
                cross(p - 1, p, q, l, mid - l) < 0 and
                cross(p, p + 1, q, l, mid - l) > 0) {
                a1 = p, b1 = q;
            }
        }
        p = l + lengthA - 1, q = mid, checked = 0;
        while (checked < lengthA + lengthB) {
            for (; q < lengthB; q++) {
                checked++;
                if (cross(q - 1, q, p, mid, r - mid) < 0 and
                    cross(q, q + 1, p, mid, r - mid) > 0) {
                    break;
                }
            }
            for (; p >= l; p--) {
                checked++;
                if (cross(p - 1, p, q, l, mid - l) > 0 and
                    cross(p, p + 1, q, l, mid - l) < 0) {
                    break;
                }
            }
            if (cross(q - 1, q, p, mid, r - mid) < 0 and
                cross(q, q + 1, p, mid, r - mid) > 0 and
                cross(p - 1, p, q, l, mid - l) > 0 and
                cross(p, p + 1, q, l, mid - l) < 0) {
                a2 = p, b2 = q;
            }
        }
        int max = 0;
        for (int i = b1; i != b2; i = (i - mid + 1) % lengthB + mid) {
            tmp.push_back(_nodes[i]);
        }
        tmp.push_back(_nodes[b2]);
        for (int i = a2; i != a1; i = (i - l + 1) % lengthA + mid) {
            tmp.push_back(_nodes[i]);
        }
        int len = tmp.size();
        for (int i = 0; i < len; i++) {
            max = tmp[i].rank > tmp[max].rank ? i : max;
        }
        for (int i = 0; i < len; i++) {
            _nodes[l + i] = tmp[(max + i) % len];
        }
        tmp.clear();
        return len;
    }


//[l,r)
    int solve(int l, int r) {
        int length = r - l;
        if (length < 3) return length;
        if (length == 3 and (_nodes[l + 1].x - _nodes[l].x) * (_nodes[l + 2].y - _nodes[l].y) -
                            (_nodes[l + 2].x - _nodes[l].x) * (_nodes[l + 1].y - _nodes[l].y) < 0) {
            std::swap(_nodes[l + 1], _nodes[l + 2]); //逆时针
            return 3;
        }
        int mid = (l + r) >> 1;
        int lenA = solve(l, mid);
        int lenB = solve(mid, r);
        return merge(l, mid, r, lenA, lenB);
    }

public:
    int getHull() {
        std::sort(_nodes.begin(), _nodes.end(), [](MyNode &a, MyNode &b) -> bool {
            if (a.x == b.x) return a.y < b.y;
            return a.x < b.x;
        });
        int length = std::unique(_nodes.begin(), _nodes.end()) - _nodes.begin();
        for (int i = 0; i < length; i++) {
            _nodes[i].rank = i;
        }
        return solve(0, length);
    }

    ConvexHull(std::vector<MyNode> &nodes) : _nodes(nodes) {}
};

#endif //DS2020_CONVEXHULL_H
