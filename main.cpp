#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include "Stack.h"
//#include "test.h"

using std::cin;
using std::vector;
using std::cout;
using std::endl;
using std::for_each;

class Point {
public:
    int id;
    double x, y;
    double angle;

    Point(int id, double x, double y) {
        this->id = id;
        this->x = x;
        this->y = y;
    }

    Point(const Point &obj) {
        this->id = obj.id;
        this->x = obj.x;
        this->y = obj.y;
        this->angle = obj.angle;
    }
};

vector<Point> points;

int main() {
    int n;
    cin >> n;
    for (auto i = 0; i < n; i++) {
        double a, b;
        cin >> a >> b;
        points.emplace_back(i, a, b);
    }
    sort(points.begin(), points.end(), [](Point &a, Point &b) -> bool { return a.y < b.y; });
    for (auto i = 1; i < n; i++) {
        points[i].angle = atan2(points[i].y - points[0].y, points[i].x - points[0].x);
    }
    sort(points.begin() + 1, points.end(), [](Point &a, Point &b) -> bool { return a.angle < b.angle; });
    Stack<Point> pointStack;
    pointStack.push(points[0]);
    pointStack.push(points[1]);
    auto getCross = [](Point &a, Point &b, Point &c) -> double {
        return (b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y);
    };
    for_each(points.begin() + 2, points.end(), [&](Point &x) -> void {
        Point pre1 = pointStack.top();
        pointStack.pop();
        Point pre2 = pointStack.top();
        while (getCross(pre2, pre1, x) < 0) {
            pre1 = pre2;
            pointStack.pop();
            pre2 = pointStack.top();
        }
        pointStack.push(pre1);
        pointStack.push(x);
    });
    auto getDistance = [&](Point &a, Point &b) -> double {
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    };
    double ans = 0;
    Point tmp = points[0];
    while (!pointStack.isEmpty()) {
        Point top = pointStack.top();
        ans += getDistance(top, tmp);
        tmp = pointStack.top();
        pointStack.pop();
    }
    printf("%.2lf", ans);

    return 0;
}
