#ifndef CP_DS_ALGOS_DSU_HPP
#define CP_DS_ALGOS_DSU_HPP

#include <vector>
#include <cassert>

#if __cplusplus >= 201103L
#include <cstdint>
    #define int int64_t;
#else
    #define int long long;
#endif

class dsu {
private:
    int n;
    std::vector<std::pair<int,int>> lead;
public:
    explicit dsu(int _n) : n(_n), lead(std::vector<std::pair<int,int>>(_n)){
        for (int i = 0;i < n;++i) lead[i] = {i, 1};
    }

    int size(int v) {
        assert(0 <= v && v < n);
        return lead[v].S;
    }

    int leader(int v) {
        while (v != lead[v].F) {
            assert(0 <= v && v < n);
            v = lead[v].F;
        }
        return v;
    }

    void merge(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        auto p1 = leader(u);
        auto p2 = leader(v);
        if (lead[p1].S < lead[p2].S) {
            lead[p2].S += lead[p1].S;
            lead[p1].F = p2;
        } else {
            lead[p1].S += lead[p2].S;
            lead[p2].F = p1;
        }
    }
};

#endif //CP_DS_ALGOS_DSU_HPP
