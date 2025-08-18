#ifndef CP_DS_ALGOS_STRING_ALGOS
#define CP_DS_ALGOS_STRING_ALGOS

#include <bits/stdc++.h>

using namespace std;

vector<size_t> prefix_function(const string &s) {
    vector<size_t> p(s.size());
    for (int i = 1;i < s.size();i++) {
        int cur = p[i - 1];
        while (s[i] != s[cur] && cur > 0) cur = p[cur - 1];
        if (s[i] == s[cur]) p[i] = cur + 1;
    }

    return p;
}

#endif //CP_DS_ALGOS_STRING_ALGOS