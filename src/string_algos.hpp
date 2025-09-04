#ifndef CP_DS_ALGOS_STRING_ALGOS
#define CP_DS_ALGOS_STRING_ALGOS

#include <bits/stdc++.h>

using namespace std;

vector<size_t> prefix_function(const string &s) {
    vector<size_t> p(s.size());
    for (size_t i = 1;i < s.size();i++) {
        int cur = p[i - 1];
        while (s[i] != s[cur] && cur > 0) cur = p[cur - 1];
        if (s[i] == s[cur]) p[i] = cur + 1;
    }

    return p;
}

vector<size_t> z_function(const string &s) {
    vector<size_t> z(s.size());
    size_t l = 0, r = 0;
    for (size_t i = 1;i < s.size();i++) {
        if (i <= r) 
            z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

#endif //CP_DS_ALGOS_STRING_ALGOS