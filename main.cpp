/**
  * Created by Huang Jingcheng on 2020/9/20.
  * 201905130198@mail.sdu.edu.cn
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <chrono>
#include "ConvexHull.h"
#include "sort.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
int array[50009];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(array, array + n, std::default_random_engine(seed));
    Algorithm<int>::sort(array, array + n);
    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
}