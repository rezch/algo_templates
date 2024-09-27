#include <bits/stdc++.h>


namespace ZP_functions {

template<class T>
std::vector<int> prefix(const T &s) { // O(n)
    std::vector<int> p(s.size());
    for (int i = 1; i < s.size(); i++) {
        int cur = p[i - 1];
        while (s[i] != s[cur] && cur > 0) { cur = p[cur - 1]; }
        if (s[i] == s[cur]) { p[i] = cur + 1; }
    }
    return p;
}

template<class T>
std::vector<int> z_function(const T &s) { // O(n)
    std::vector<int> z(s.size());
    int l{}, r{};
    for (int i = 1; i < s.size(); i++) {
        if (i <= r) { z[i] = std::min(r - i + 1, z[i - l]); }
        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) { ++z[i]; }
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
    return z;
}

} // ZP_functions


namespace Trie {

struct Node {
    int terminated = 0;
    int count = 0;
    std::vector<std::pair<char, Node*>> to;

    Node* go(char x) {
        for (auto&& [c, n] : to) {
            if (x == c) return n;
        }
        to.push_back({ x, new Node() });
        return to.back().second;
    }

    bool has(char x) const {
        for (auto&& [c, n] : to) {
            if (x == c) return true;
        }
        return false;
    }
};

Node* root = new Node();

void addWord(const std::string &s) {
    Node* curr = root;
    for (char c : s) {
        c -= 'a';
        ++curr->count;
        curr = curr->go(c);
    }
    ++curr->count;
    ++curr->terminated;
}

int get(const std::string& s) {
    Node* curr = root;
    for (char c : s) {
        c -= 'a';
        if (!curr->has(c)) { return 0; }
        curr = curr->go(c);
    }
    return curr->count;
}

} // Trie

namespace BitTrie {

constexpr size_t SIZE = 32; // bit size of numbers

struct Node {
    using value_type = uint32_t;

    int terminated{};
    int count{};
    Node* to[2] = { nullptr, nullptr };
    value_type mask{};
    bool full{false};

    void push() {
        if (!mask) { return; }
        if (mask & 1) {
            std::swap(to[0], to[1]);
        }
        for (int i = 0; i < 2; ++i) {
            if (!to[i]) continue;
            to[i]->mask ^= mask >> 1;
        }
        mask = 0;
    }

    void update() {
        if (!to[0] && !to[1]) {
            full = true;
            return;
        }
        full = to[0] && to[1] && to[0]->full && to[1]->full;
    }
};

inline Node::value_type reverse_bits(Node::value_type x) {
    Node::value_type result{};
    for (int i = SIZE - 1, j = 0; i >= 0; --i, ++j) {
        result ^= ((x >> i) & 1) << j;
    }
    return result;
}

Node* root = new Node();

void updateTrie(Node * curr = root) {
    if (curr->to[0]) updateTrie(curr->to[0]);
    if (curr->to[1]) updateTrie(curr->to[1]);
    curr->update();
}

void xor_trie(Node::value_type x) {
    if (!root->count) return;
    root->mask = reverse_bits(x);
}

void addWord(Node::value_type x) {
    Node* curr = root;
    for (int i = SIZE - 1; i >= 0; --i) {
        curr->push();
        int c = x >> i & 1;
        if (!curr->to[c]) { curr->to[c] = new Node(); }
        ++curr->count;
        curr = curr->to[c];
    }
    ++curr->count;
    ++curr->terminated;
    updateTrie();
}

bool has(Node::value_type x) {
    Node* curr = root;
    for (int i = SIZE - 1; i >= 0; --i) {
        curr->push();
        int c = x >> i & 1;
        if (!curr->to[c]) { return false; }
        curr = curr->to[c];
    }
    return curr->terminated;
}

Node::value_type mex() {
    Node * curr = root;
    if (!curr->count) return 0;
    Node::value_type mex{};
    curr->push();
    for (int i = SIZE - 1; i >= 0; --i) {
         curr->push();
        if (!curr->to[0]) break;
        if (!curr->to[0]->full) {
            curr = curr->to[0];
            continue;
        }
        mex += 1 << i;
        curr = curr->to[1];
        if (!curr) break;
    }
    return mex;
}

} // BitTrie
