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

}; // ZP_functions


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

}; // Trie


namespace BitTrie {

constexpr size_t SIZE = 32; // bit size of numbers

struct Node {
    using value_type = uint32_t;

    int terminated{};
    int count{};
    Node* to[2] = { nullptr, nullptr };
    value_type mask{};
    bool full{true};

    void push() {
        if (!mask) { return; }
        if (mask & 1) {
            std::swap(to[0], to[1]);
        }
        for (auto&& child : to) {
            if (!child) continue;
            child->mask ^= mask >> 1;
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

void updateTrie(const std::vector<Node*>& nodes) {
    for (int i = nodes.size() - 1; i >= 0; --i) {
        nodes[i]->update();
    }
}

void xor_trie(Node::value_type x) {
    if (!root->count) return;
    root->mask = reverse_bits(x);
}

void addWord(Node::value_type x) {
    Node* curr = root;
    std::vector<Node*> used_nodes;
    for (int i = SIZE - 1; i >= 0; --i) {
        curr->push();
        used_nodes.push_back(curr);
        int c = x >> i & 1;
        if (!curr->to[c]) { curr->to[c] = new Node(); }
        ++curr->count;
        curr = curr->to[c];
    }
    ++curr->count;
    ++curr->terminated;
    curr->push();
    used_nodes.push_back(curr);
    updateTrie(used_nodes);
}

bool has(Node::value_type x) {
    Node* curr = root;
    for (int i = SIZE - 1; i >= 0; --i) {
        curr->push();
        int c = x >> i & 1;
        if (!curr->to[c]) { return false; }
        curr = curr->to[c];
    }
    curr->push();
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
        mex &= 1 << i;
        curr = curr->to[1];
        if (!curr) break;
    }
    return mex;
}

}; // BitTrie


namespace Aho {

class Aho {
public:
    static constexpr int ROOT = 0;

    Aho() : nodes(2)
    {
        nodes[ROOT] = Node(-1, 0);
        nodes[ROOT].cnt = 0;
    }

    void addWord(const std::string& s, int k)
    {
        int curr = ROOT;
        for (auto c : s) {
            if (!nodes[curr].to.contains(c)) {
                nodes[curr].to[c] = addNode(curr, c);
            }
            curr = nodes[curr].to[c];
            nodes[curr].cnt = -1;
        }
        nodes[curr].terminated += k;
        ++words_count;
    }

    int link(int v)
    {
        if (nodes[v].link != -1) return nodes[v].link;
        if (v == ROOT || nodes[v].p == ROOT) nodes[v].link = ROOT;
        else nodes[v].link = go(link(nodes[v].p), nodes[v].pch);
        return nodes[v].link;
    }

    int go(int v, char c)
    {
        if (nodes[v].go.contains(c)) return nodes[v].go[c];
        if (nodes[v].to.contains(c)) nodes[v].go[c] = nodes[v].to[c];
        else if (v == ROOT) nodes[v].go[c] = 0;
        else nodes[v].go[c] = go(link(v), c);
        return nodes[v].go[c];
    }

    void getCnt(int v)
    {
        if (nodes[v].cnt != -1) return;
        getCnt(link(v));
        nodes[v].cnt = nodes[nodes[v].link].cnt + nodes[v].terminated;
    }

    int countEntry(const std::string& s)
    {
        int res = 0;
        int curr = ROOT;
        for (auto c : s) {
            curr = go(curr, c);
            getCnt(curr);
            res += nodes[curr].cnt;
        }
        return res;
    }

    void clearLinks()
    {
        for (int i = 0; i < nodes.size(); ++i)
            nodes[i].clear();
    }

    void rebuild(Aho& other)
    {
        clearLinks();
        words_count += other.words_count;
        buildFrom(other);
        other = Aho();
    }

    int words_count{};

private:
    void buildFrom(const Aho& other)
    {
        std::queue<std::pair<int, int>> q;
        q.push({ ROOT, ROOT });
        while (!q.empty()) {
            auto [v, ov] = q.front();
            q.pop();
            nodes[v].terminated += other.nodes[ov].terminated;
            for (auto&& [c, to] : other.nodes[ov].to) {
                if (!nodes[v].to.contains(c)) {
                    nodes[v].to[c] = addNode(v, c);
                }
                q.push({ nodes[v].to[c], to });
            }
        }
    }

    struct Node {
        int p{-1};
        char pch{};
        int link{-1};
        std::map<char, int> to;
        std::map<char, int> go;
        int terminated{};
        int cnt{-1};

        Node() = default;
        Node(int p, char c) : p(p), pch(c) {};

        inline void clear() {
            link = -1;
            go.clear();
        }
    };

    inline int addNode(int p, char c)
    {
        nodes.emplace_back(p, c);
        return nodes.size() - 1;
    }

    std::vector<Node> nodes;
};

template <int SIZE = 1 << 19>
class DynamicAho {
public:
    static constexpr int LOG = 64 - __builtin_clzll(0LL + SIZE); // log2(SIZE) + 1

    DynamicAho() : aho(LOG - 1) { };

    void insert(const std::string& s, bool add)
    {
        aho[0].addWord(s, (add ? 1 : -1));
        int curr_bucket{};
        for (; curr_bucket < LOG; ++curr_bucket) {
            if (!aho[curr_bucket].words_count) {
                break;
            }
        }
        for (int i = 0; i < curr_bucket; ++i) {
            aho[curr_bucket].rebuild(aho[i]);
        }
    }

    int request(const std::string& s)
    {
        int res{};
        for (auto& a : aho) {
            res += a.countEntry(s);
        }
        return res;
    }

private:
    std::vector<Aho> aho;
};

}; // Aho


namespace Suffauto {

constexpr int SIZE = 1 << 17;

struct State {
    int len{};
    int link{};
    std::map<char, int> next;
    int size{};
    int sum{};
    bool used{};
};

State state[SIZE << 1];
int sz{}, last{};

void init() {
    last = 0;
    ++sz;
    state[0].len = 0;
    state[0].link = -1;
}

void extend(char c) {
    int cur = sz++;
    state[cur].len = state[last].len + 1;
    int p;
    for (p = last; p != -1 && !state[p].next.count(c); p = state[p].link) {
        state[p].next[c] = cur;
    }
    if (p == -1) {
        state[cur].link = 0;
        last = cur;
        return;
    }
    int q = state[p].next[c];
    if (state[p].len + 1 == state[q].len) {
        state[cur].link = q;
    }
    else {
        int clone = sz++;
        state[clone].len = state[p].len + 1;
        state[clone].next = state[q].next;
        state[clone].link = state[q].link;
        for (; p != -1 && state[p].next[c] == q; p = state[p].link) {
            state[p].next[c] = clone;
        }
        state[q].link = state[cur].link = clone;
    }
    last = cur;
}

void build(const std::string& s) {
    init();
    for (char c : s) {
        extend(c);
    }
}

void sizes(int v = 0) {
    if (state[v].used) return;
    state[v].used = true;
    state[v].size = 1;
    state[v].sum = 0;
    for (auto&& [c_to, to] : state[v].next) {
        sizes(to);
        state[v].size += state[to].size;
        state[v].sum += state[to].size + state[to].sum;
    }
}

}; // Suffauto
