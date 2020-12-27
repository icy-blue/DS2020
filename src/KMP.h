/**
 * Created by Clion.
 * User: Huang Jingcheng
 * Date: 2020/12/15
 * 201905130198@mail.sdu.edu.cn
 */

#ifndef DS2020_KMP_H
#define DS2020_KMP_H

#include <vector>
#include <string>

std::vector<int> getNext(std::string &pattern) {
    std::vector<int> next;
    next.push_back(-1);
    auto now = -1, i = 1;
    while (i < pattern.length()) {
        if (pattern[i] == pattern[now + 1]) {
            now++;
            next.push_back(now);
            i++;
        } else if (now != -1) {
            now = next[now];
        } else {
            next.push_back(now);
            i++;
        }
    }
    return next;
}

std::vector<int> kmpAll(std::string &str, std::string &pattern) {
    auto next = getNext(pattern);
    std::vector<int> result;
    int i = 0, j = 0;
    while (i < str.length()) {
        if (str[i] == pattern[j]) {
            i++;
            j++;
        } else if (j != 0) {
            j = next[j - 1] + 1;
        } else {
            i++;
        }
        if (j == pattern.length()) {
            result.push_back(i - j);
            j = next[j - 1] + 1;
        }
    }
    return result;
}

#endif //DS2020_KMP_H
