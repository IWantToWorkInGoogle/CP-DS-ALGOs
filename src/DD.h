#ifndef TEST_DD_H
#define TEST_DD_H

#include <chrono>
#include <random>

using namespace std;

mt19937_64 gen(chrono::high_resolution_clock().now().time_since_epoch().count());

#ifdef __GNUC__

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;


//    typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ord_set;

template<typename T>
struct StandardDD_gnu {
    StandardDD_gnu(T nullObj) {
        this->nullObj = nullObj;
    }

    void insert(T x) {
        data.insert(x);
    }

    void erase(T x) {
        data.erase(x);
    }

    T getKth(size_t k) {
        auto t = data.find_by_order(k);
        if (t == data.end()) {
            return nullObj;
        }
        return *(data.find_by_order(k));
    }

    bool contain(T x) {
        return data.contain(x);
    }

    size_t countSmallerThatVal(T x) {
        return data.order_of_key(x);
    }

    size_t size() {
        return data.size();
    }

private:
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> data;

    T nullObj;
};

#endif

template<typename T>
struct StandardDD_clang {

    /*
     * Example Use
     * StandardDD_clang<int32_t> st(
     *      -1,
     *      [](int32_t& a, int32_t& b)->bool{return a < b;},
     *      [](int32_t& a, int32_t& b)->bool{return a == b;});
     */

    bool (*funcLess)(T&, T&);
    bool (*funcEqual)(T&, T&);

    StandardDD_clang(T nullObj, bool (*funcLess)(T&, T&), bool (*funcEqual)(T&, T&)) {
        this->nullObj = nullObj;
        this->funcLess = funcLess;
        this->funcEqual = funcEqual;
    }

    void insert(T x) {
        if (!contain(x)) {
            data.push_back(new eto(x));
            root = merge(root, data[data.size() - 1]);
        }
    }

    bool contain(T x) {
        auto p = splitVal(x);
        bool res = p.first.second != nullptr;
        root = merge(merge(p.first.first, p.first.second), p.second);

        return res;
    }

    void erase(T x) {
        auto p = splitVal(x);
        root = merge(p.first.first, p.second);
    }

    T getKth(size_t k) {
        auto p = splitK(root, k);
        auto q = splitK(p.second, 1);
        if (q.first == nullptr) {
            merge(p.first, merge(q.first, q.second));
            return nullObj;
        } else {
            merge(p.first, merge(q.first, q.second));
            return q.first->val;
        }
    }

    size_t countSmallerThatVal(T x) {
        eto* v = root;
        size_t ans = 0;
        while (v != nullptr) {
            if (funcLess(v->val, x)) {
                ans += (v->l == nullptr? 0: v->l->sz) + 1;
                v = v->r;
            } else {
                v = v->l;
            }
        }
        return ans;
    }

    size_t size() {
        return (root == nullptr? 0: root->sz);
    }

    size_t countSmallerOrEqualThatVal(T x) {
        eto* v = root;
        size_t ans = 0;
        while (v != nullptr) {
            if (funcLess(v->val, x) || funcEqual(v->val, x)) {
                ans += (v->l == nullptr? 0: v->l->sz) + 1;
                v = v->r;
            } else {
                v = v->l;
            }
        }
        return ans;
    }

private:
    struct eto {
        eto* l;
        eto* r;
        int sz;
        T val;
        uint64_t key;

        explicit eto(T val) {
            this->val = val;
            l = nullptr;
            r = nullptr;
            sz = 1;
            key = gen();
        }
    };

    vector<eto*> data;
    eto* root = nullptr;
    T nullObj;

    void upd(eto* v) {
        if (v == nullptr) return;
        v->sz = (v->l == nullptr? 0: v->l->sz) + (v->r == nullptr? 0: v->r->sz) + 1;
    }

    eto* merge(eto* u, eto* v) {
        if (u == nullptr) {
            return v;
        }
        if (v == nullptr) {
            return u;
        }

        if (funcLess(v->val, u->val)) {
            swap(u, v);
        }

        if (u->key < v->key) {
            eto* p;
            p = merge(u->r, v);
            u->r = p;
            upd(u);
            return u;
        } else {
            eto* p = merge(u, v->l);
            v->l = p;
            upd(v);
            return v;
        }
    }

    pair<eto*, eto*> splitK(eto* v, size_t k) {
        if (v == nullptr) return {nullptr, nullptr};
        size_t sz = (v->l == nullptr? 0: v->l->sz);

        if (sz >= k) {
            auto p = splitK(v->l, k);
            v->l = p.second;
            upd(v);
            return {p.first, v};
        } else {
            auto p = splitK(v->r, k - sz - 1);
            v->r = p.first;
            upd(v);
            return {v, p.second};
        }
    }

    pair<pair<eto*, eto*>, eto*> splitVal(T val) {
        int k1 = countSmallerThatVal(val);
        int k2 = countSmallerOrEqualThatVal(val);
        auto p = splitK(root, k2);
        auto q = splitK(p.first, k1);
        return {q, p.second};
    }
};


#endif //TEST_DD_H
