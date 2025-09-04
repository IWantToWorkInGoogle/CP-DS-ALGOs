#ifndef CP_DS_ALGOS_TRIE_HPP
#define CP_DS_ALGOS_TRIE_HPP

#include <vector>
#include <map>
#include <string>

template <typename T>
class trie_t {
    struct node_t {
        std::map<char, int> to;
        int end;
    };

    std::vector<node_t> data;

    bool can_go(int v, char c) { return data[v].to.count(c); }

    int& go(int v, char c) { return data[v].to[c]; }

    int create_node() { 
        data.push_back(node_t());
        return data.size() - 1;
    }

    int is_end(int v) { return data[v].end; }

public:

    trie_t() { create_node(); }

    int search(const std::string &s) {
        int v = 0;
        for (auto c : s) {
            if (!can_go(v, c)) return 0; 
            v = go(v, c);
        }
        return data[v].end;
    }

    void insert(const std::string &s) {
        int v = 0;
        for (auto c : s) {
            if (!can_go(v, c)) go(v, c) = create_node();
            v = go(v, c);
        }
        data[v].end++;
    }

    void erase(const std::string &s) {
        int v = 0;
        for (auto c : s) {
            if (!can_go(v, c)) return;
            v = go(v, c);
        }

        data[v].end = std::max(0, data[v].end - 1);
    }
};

#endif //CP_DS_ALGOS_SEGTREE_HPP

#include <bits/stdc++.h>

int main() {
    trie_t<char> trie;

    trie.insert("hello");

    assert(trie.search("hello") == 1);

    assert(!trie.search("dello"));

    assert(!trie.search("hell"));

    assert(!trie.search("helloooooooo"));

    trie.insert("hello");
    trie.insert("hello");

    assert(trie.search("hello") == 3);

    trie.erase("hello");

    assert(trie.search("hello") == 2);

    std::cout << "Tests passed" << std::endl;
}


