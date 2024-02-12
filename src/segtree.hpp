#ifndef CP_DS_ALGOS_SEGTREE_HPP
#define CP_DS_ALGOS_SEGTREE_HPP

template <class M, M (*op)(M, M), M (*e)()> struct segtree {
private:
    int n;
    std::vector<M> data;
public:
    segtree(int _n) : n(_n) {
        data.resize(2 * n,e());
    }
    segtree(vector<M> &a) : n((int)(a.size())) {
        data.resize(2 * n);
        build(0,1,n,a);
    }

    void update(int v) {
        data[v] = op(data[2 * v + 1],data[2 * v + 2]);
    }

    void build(int v,int tl, int tr,vector<M> &a) {
        if (tl == tr) {
            data[v] = a[tl - 1];
            return;
        }
        int tm = (tl + tr) / 2;
        build(2 * v + 1,tl,tm,a);
        build(2 * v + 2,tm + 1,tr,a);
        update(v);
    }

    void set(int ind,const M val) {
        assert(1 <= ind && ind <= n);
        set(0,1,n,ind,val);
    }

    void set(int v,int tl,int tr,int ind,const M val) {
        if (tl == ind) {
            data[v] = val;
        }
        if (ind < tl || tr < ind) return;
        int tm = (tl + tr) / 2;
        set(2 * v + 1,tl,tm,ind,val);
        set(2 * v + 2,tm + 1,tr,ind,val);
        update(v);
    }

    M get(int l,int r) {
        assert(l <= r && 1 <= l && r <= n);
        return get(0,1,n,l,r);
    }

    M get(int v,int tl, int tr, int l, int r) {
        if (tr < l || r < tl) return e();
        if (l <= tl && tr <= r) return data[v];
        int tm = (tl + tr) / 2;
        return op(get(2 * v + 1,tl,tm,l,r),get(2 * v + 2,tm + 1,tr,l,r));
    }
};

#endif //CP_DS_ALGOS_SEGTREE_HPP
