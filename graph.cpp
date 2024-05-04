#include <bits/stdc++.h>


namespace DSUsize {
    constexpr int SIZE = 131072;

    int p[SIZE], sz[SIZE];

    void init(int size) { // O(n)
        for (int i = 0; i < size; ++i) {
            p[i] = i;
            sz[i] = 1;
        }
    }

    int head(int x) { // O(a(i)) ~ O(1)
        return (x == p[x] ? x : p[x] = head(p[x]));
    }

    void unite(int a, int b) { // O(a(i)) ~ O(1)
        a = head(a); b = head(b);
        if (a == b) { return; }
        if (sz[a] < sz[b]) { std::swap(a, b); }
        p[b] = a;
        sz[a] += sz[b];
    }
}


namespace DSUrank {
    constexpr int SIZE = 131072;

    int p[SIZE], rank[SIZE];

    void init(int size) { // O(n)
        std::memset(&rank, 0, size);
        for (int i = 0; i < size; ++i) {
            p[i] = i;
        }
    }

    int head(int x) { // O(a(i)) ~ O(1)
        return (x == p[x] ? x : p[x] = head(p[x]));
    }

    void unite(int a, int b) { // O(a(i)) ~ O(1)
        a = head(a); b = head(b);
        if (a == b) { return; }
        if (rank[a] < rank[b]) { std::swap(a, b); }
        rank[a] = std::max(rank[a], rank[b] + 1);
        p[b] = a;
    }
}


namespace DFS {
    void dfs(int v, std::vector<std::vector<int>>& g, std::vector<int>& used) { // O(n + m)
        // v - current vertex, p - parent
        // g - adj list
        used[v] = 1;
        for (const auto& to : g[v]) {
            if (used[to]) { continue; }
            dfs(to, g, used);
        }
    }

    void topsort(int v, std::vector<std::vector<int>>& g, std::vector<int>& used, std::vector<int>& sorted) { // O(n + m)
        // v - current vert, g - adj list, sorted - reversed topology sorted vertexes
        used[v] = 1;
        for (const auto& to : g[v]) {
            if (!used[to]) {
                topsort(to, g, used, sorted);
            }
        }
        sorted.push_back(v);
    }
}

namespace Bridges { // O(n + m)
    // find all bridges in an undirected graph, that may include multiple edges

    // edges[a] = { { b, i } } - vert from a to b, i - index of edge
    std::vector<std::vector<std::pair<int, int>>> edges;
    std::vector<int> tin, tout, used;

    // is_bridge[v][u] - true if v-u is bridge
    std::unordered_map<int, std::unordered_map<int, int>> is_bridge;

    void dfs(int vert, int parent, int& timer) { // find all bridges
        used[vert] = true;
        tin[vert] = tout[vert] = timer++;
        for (const auto& to : edges[vert]) {
            if (to.second == parent) {
                continue;
            }
            if (used[to.first]) {
                tout[vert] = std::min(tout[vert], tin[to.first]);
            }
            else {
                dfs(to.first, to.second, timer);
                tout[vert] = std::min(tout[vert], tout[to.first]);

                if (tin[vert] < tout[to.first]) {
                    is_bridge[vert][to.first] = 1;
                    is_bridge[to.first][vert] = 1;
                }
            }
        }
    }

    void FindBridges(int V) {
        for (int i = 0; i < V; ++i) {
            int timer = 0;
            dfs(i, -1, timer);
        }
        // now is_bridges[v][u] = 1 (contains keys v, u) if v-u is bridge
    }
}

namespace BFS {

    void bfs(int start, std::vector<std::vector<int>>& g) { // O(n + m)
        // start vert, adj list
        std::queue<int> q;
        std::vector<int> used(g.size());
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (const auto& to : g[v]) {
                if (used[to]) { continue; }
                used[to] = 1;
                q.push(to);
            }
        }
    }

    void bfs_topsort() { // O(n + m)
        int n = 1, m = 1; // vert, edges count
        std::vector<std::vector<int>> g(n); // adj list of DAG
        std::vector<int> pcnt(n); // count of unseen incoming edges to the vertex
        for (int i = 0; i < m; ++i) {
            int v, u;
            std::cin >> v >> u;
            g[v].push_back(u);
            ++pcnt[u];
        }
        std::vector<int> sorted; // topology sorted vertexes
        std::queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (pcnt[i] == 0) {
                q.push(i);
                sorted.push_back(i);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (const auto& to : g[v]) {
                if (--pcnt[to] == 0) {
                    q.push(to);
                    sorted.push_back(to);
                }
            }
        }
    }
}


namespace LCA_DFS {
    constexpr int MAXN = 131072, MAXLG = 17; // LOG = log(MAXN, 2)

    int sparse[MAXN][MAXLG];
    std::vector<std::vector<int>> g;
    std::vector<int> tin, tout;

    void dfs(int v, int& t) { // O(n + m)
        // v - current vert, t - time of entry in current vert
        for (int l = 1; l < MAXLG; ++l) {
            sparse[v][l] = sparse[sparse[v][l - 1]][l - 1];
        }
        tin[v] = t++;
        for (const auto& to : g[v]) {
            sparse[to][0] = v;
            dfs(to, t);
        }
        tout[v] = t;
    }

    bool ancestor(int u, int v) { // O(1)
        // u, v - vertexes
        // return true if v is ancestor of u
        return tin[u] <= tin[v] && tin[v] < tout[u];
    }

    int lca(int a, int b) { // O(MAXLG) ~ O(1)
        // a, b - vertexes
        // return lca of a, b
        if (ancestor(a, b)) { return a; }
        if (ancestor(b, a)) { return b; }
        for (int l = MAXLG - 1; l >= 0; --l) {
            if (!ancestor(sparse[a][l], b)) {
                a = sparse[a][l];
            }
        }
        return sparse[a][0];
    }
}


namespace LCA_dynamic {
    constexpr int MAXN = 131072, LOG = 17; // LOG = log(MAXN, 2)

    int parent[MAXN], depth[MAXN];
    int up[MAXN][LOG];

    void init() {
        for (int j = 1; j < LOG; ++j) {
            for (int i = 1; i < MAXN; ++i) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }
    }

    void add(int a, int b) {
        parent[b] = a;
        depth[b] = depth[a] + 1;
        up[b][0] = a;

        for (int j = 1; j < LOG; ++j) {
            up[b][j] = up[up[b][j - 1]][j - 1];
        }
    }

    int get_lca(int a, int b) { // O(log N)
        if (depth[a] < depth[b]) {
            std::swap(a, b);
        }
        int d = depth[a] - depth[b];
        for (int j = LOG - 1; j >= 0; --j) {
            if (d & (1 << j)) {
                a = up[a][j];
            }
        }
        if (a == b) {
            return a;
        }
        for (int j = LOG - 1; j >= 0; --j) {
            if (up[a][j] != up[b][j]) {
                a = up[a][j];
                b = up[b][j];
            }
        }
        return parent[a];
    }
}


namespace PathFind {

    void dijkstra(int s, int f, std::vector<std::vector<std::pair<int, int>>>& g) { // O(m * log n)
        // s, f - start & end vertexes (f - for find path), g - adj list (pair { end of edge, len of edge })
        // dist[i] - min distance from s to i vertexes
        // path - vertexes on min way from s to f
        std::vector<int64_t> dist(g.size(), INT64_MAX);
        dist[s] = 0;
        std::set<std::pair<int64_t, int>> st;
        st.insert({ 0, s });
        std::vector<int> way(g.size());
        while (!st.empty()) {
            int cur = (*st.begin()).second;
            st.erase(st.begin());

            for (const auto& e : g[cur]) {
                if (dist[e.first] > dist[cur] + e.second) {
                    st.erase({dist[e.first], e.first});
                    dist[e.first] = dist[cur] + e.second;
                    st.insert({dist[e.first], e.first});
                    way[e.first] = cur;
                }
            }
        }

        if (dist[f] == INT64_MAX) {
            // no way from s to f
            return;
        }

        std::vector<int> path;
        int key = f;
        while (key != s) {
            path.push_back(key + 1);
            key = way[key];
        }
        path.push_back(s);
        std::reverse(path.begin(), path.end());
    }

    void Floyd(std::vector<std::vector<int>>& g) { // O(n^3)
        // adj matrix with weights of edges (g[i][i] = 0)
        for (int k = 0; k < g.size(); ++k) {
            for (int i = 0; i < g.size(); ++i) {
                for (int j = 0; j < g.size(); ++j) {
                    if (g[i][k] < INT32_MAX && g[k][j] < INT32_MAX) {
                        g[i][j] = std::min(g[i][j], g[i][k] + g[k][j]);
                    }
                }
            }
        }

        for (int i = 0; i < g.size(); ++i) {
            for (int j = 0; j < g.size(); ++j) {
                for (int t = 0; t < g.size(); ++t) {
                    if (g[i][t] < INT32_MAX && g[t][t] < 0 && g[t][j] < INT32_MAX) {
                        // graph has a negative cycle
                        return;
                    }
                }
            }
        }
        // now g[i][j] - min way from i to j (g[i][j] = -inf if
    }

    struct Edge {
        int a, b, cost;
    };
    void FordBellman(int n, int s, std::vector<Edge>& edges) { // O(nm)
        // n - number of vertexes, s - start vertex
        // edges - edges list (a - from vert, b - to vert, cost - len of current edge)
        std::vector<int> d(n, INT32_MAX);
        d[s] = 0;
        int x = -1;
        for (int i = 0; i < n; ++i) {
            x = -1;
            for (int j = 0; j < edges.size(); ++j) {
                if (d[edges[j].b] > d[edges[j].a] + edges[j].cost) {
                    d[edges[j].b] = std::max(INT32_MIN, d[edges[j].a] + edges[j].cost);
                    x = edges[j].b;
                }
            }
        }
        if (x != -1) {
            // graph has a negative cycle
            return;
        }
        // now d[i] - min dist from s to i
    }

    void spfa(int v, std::vector<std::vector<std::pair<int, int>>>& g, std::vector<int>& used, std::vector<int>& d, bool& flag) { // O(n + m)
        // The shortest path faster algorithm
        // v - current vert (in first call of spfa v - is the start vertex)
        // g - adj list (pair { end of edge, len of edge })
        // d[i] - dist from s to i
        // flag = true if graph has negative cycle
        if (flag) {
            return;
        }
        used[v] = 1;
        for (const auto& e : g[v]) {
            if (d[e.first] > d[v] + e.second) {
                if (!flag && used[e.first]) {
                    flag = true;
                    return;
                }
                d[e.first] = d[v] + e.second;
                spfa(e.first, g, used, d, flag);
            }
        }
        used[v] = 0;
    }
}


namespace Kruskal { // O(E logE)
    constexpr int V = 500, E = 10000;

    struct Edge {
        Edge() = default;
        int a{}, b{}, w{};
    } edges[E];

    void MST() {
        std::sort(edges, edges + E, [](const auto& l, const auto& r) {
            const auto& [lu, lv, lw] = l;
            const auto& [ru, rv, rw] = r;
            if (lw != rw) {
                return lw < rw;
            }
            return std::make_pair(lu, lv) < std::make_pair(ru, rv);
            /* or
             * return lw < rw;
             */
        });

        int64_t len = 0; // len of MST edges
        std::vector<int> ans; // indexes of MST edges from edges array
        DSUrank::init(V);
        int cnt = 0;
        for (int i = 0; i < E; ++i) {
            const auto& [u, v, w] = edges[i];
            if (DSUrank::head(u) != DSUrank::head(v)) {
                DSUrank::unite(u, v);
                len += w;
                ans.push_back(i);
                if (++cnt == V - 1) {
                    break;
                }
            }
        }
    }
}


namespace PrimeSqrt { // O(V^2) (only for full graphs)
    constexpr int MAXN = 1e5;
    int used[MAXN];
    int best_edge[MAXN];
    int64_t min_edge[MAXN];
    std::pair<int, int> points[MAXN];

    int adj[MAXN][MAXN];

    void MST(int V) {
        std::memset(&used, 0, V);
        for (int i = 0; i < V; ++i) {
            min_edge[i] = INT32_MAX;
        }
        min_edge[0] = 0;

        int64_t len = 0; // len of MST edges
        std::vector<std::pair<int, int>> ans; // MST edges
        for (int i = 0; i < V; ++i) {
            int v = -1;
            for (int u = 0; u < V; ++u) {
                if (!used[u] && (v == -1 || min_edge[u] < min_edge[v])) {
                    v = u;
                }
            }

            used[v] = 1;
            if (v != 0) {
                len += adj[v][best_edge[v]];
                ans.push_back({ v, best_edge[v] });
            }

            for (int e = 0; e < V; ++e) {
                if (e == v) {
                    continue;
                }
                if (adj[v][e] < min_edge[e]) {
                    min_edge[e] = adj[v][e];
                    best_edge[e] = v;
                }
            }
        }
    }
}


namespace Prime { // O(m log n)
    constexpr int MAXV = 50000, MAXE = 50000;
    constexpr int INF = 100000000;

    struct Edge {
        int from{}, to{}, w{};
    } edges[MAXE];

    int used[MAXV];
    int64_t dist[MAXV];

    struct cmp {
        bool operator() (const Edge& a, const Edge& b) const {
            return a.w < b.w;
        }
    };

    void MST(int V, std::vector<std::vector<Edge>>& edges) {
        // edges[V] = { edges from V to other vertexes }
        int64_t len = 0; // len of MST edges
        std::vector<std::pair<int, int>> ans; // MST edges

        std::priority_queue<Edge, std::vector<Edge>, cmp> q;
        std::memset(&used, 0, V);
        for (int i = 0; i < V; ++i) {
            dist[i] = INF;
        }
        dist[0] = 0;
        q.push(Edge({ 0, 0, 0 }));

        int cnt = 0;
        while (!q.empty()) {
            int v = q.top().to, from = q.top().from;
            const auto& w = q.top().w;
            q.pop();

            if (used[v]) {
                continue;
            }

            len += w;
            ans.push_back({ from, v });
            if (++cnt == V) {
                break;
            }

            used[v] = 1;

            for (const auto& e : edges[v]) {
                int u = e.to;
                const auto& wto = e.w;
                if (!used[u] && wto < dist[u]) {
                    dist[u] = wto;
                    q.push(e);
                }
            }
        }
    }
}


namespace Boruvka { // O(E logV) (for planar graphs: ~O(n))
    constexpr int MAXE = 50000;

    struct Edge {
        int a{}, b{}, w{};
    } edges[MAXE];

    int min_edge[MAXE];

    void MST(int V, int E) {
        DSUrank::init(V);
        int edges_left = V;

        int64_t len = 0; // len of MST edges
        std::vector<int> ans; // indexes of MST edges from edges array

        std::memset(&min_edge, -1, V << 2);
        while (edges_left > 1) {
            std::memset(&min_edge, -1, V << 2);
            for (int i = 0; i < E; ++i) {
                int a_head = DSUrank::head(edges[i].a);
                int b_head = DSUrank::head(edges[i].b);

                if (a_head == b_head) { continue; }
                if (min_edge[a_head] == -1 || edges[min_edge[a_head]].w > edges[i].w) { min_edge[a_head] = i; }
                if (min_edge[b_head] == -1 || edges[min_edge[b_head]].w > edges[i].w) { min_edge[b_head] = i; }
            }

            for (int i = 0; i < V; ++i) {
                if (min_edge[i] != -1) {
                    int a_head = DSUrank::head(edges[min_edge[i]].a);
                    int b_head = DSUrank::head(edges[min_edge[i]].b);
                    if (a_head == b_head) { continue; }
                    len += edges[min_edge[i]].w;
                    ans.push_back(min_edge[i]);
                    DSUrank::unite(a_head, b_head);
                    --edges_left;
                }
            }
        }
    }
}


namespace SAT2 { // O(n + m)
    std::vector<std::vector<int>> g, gt; // 1 indexing
    std::vector<int> used, scc; // 1 indexing
    std::stack<int> topsort_order;
    int color = 1;

    // get inverse topsort vertex order
    void topsort(int v) {
        used[v] = 1;
        for (const auto& to : g[v]) {
            if (!used[to]) {
                topsort(to);
            }
        }
        topsort_order.push(v);
    }

    // color vertexes by their scc's
    void color_scc(int v) {
        scc[v] = color;
        for (const auto& to : gt[v]) {
            if (!scc[to]) {
                color_scc(to);
            }
        }
    }

    bool solve(int n, std::vector<std::pair<int, int>>& clauses, std::vector<int>& solution) {
        // n - number of variables and 2-CNF clauses in formula
        // solution - vector to write the solution if it exists (0 - indexing)
        // Example: clauses = { {-1, -2}, {-3, 2} } <=> (1 | !2) & (!3 | 2) (1, 2, 3 - var_1, var_2, var_3)
        // solution - { 1, 0, 0 } <=> var_1 = true, var_2 = false, var_3 = false;

        g.clear(); gt.clear();
        used.clear(); scc.clear();
        color = 1;

        // transform 2-CNF pairs to implication edges
        g.resize(n << 1 | 1);
        gt.resize(n << 1 | 1);
        for (auto& [a, b] : clauses) {
            int pos_a = n + abs(a), neg_a = abs(a);
            int pos_b = abs(b), neg_b = n + abs(b);
            if (a < 0) { std::swap(pos_a, neg_a); }
            if (b < 0) { std::swap(pos_b, neg_b); }
            g[pos_a].push_back(pos_b);
            g[neg_b].push_back(neg_a);
            gt[pos_b].push_back(pos_a);
            gt[neg_a].push_back(neg_b);
        }
        // topsort
        used.assign(n << 1 | 1, 0);
        for (int i = 1; i <= (n << 1); ++i) {
            if (!used[i]) {
                topsort(i);
            }
        }
        // coloring formula variables by their scc in implication graph
        scc.resize(n << 1 | 1);
        while (!topsort_order.empty()) {
            int v = topsort_order.top();
            topsort_order.pop();
            if (!scc[v]) {
                color_scc(v);
                ++color;
            }
        }
        // check the existence of a formula solution and finding the solution
        solution.assign(n, false);
        for (int i = 1; i <= n; ++i) {
            if (scc[i] == scc[i + n]) { // a and not(a) in the same scc
                return false;
            }
            solution[i - 1] = int(scc[i] > scc[i + n]);
        }
        return true;
    }

    // a xor b <=> (a | b) & (!a | !b)
    // a xnor b <=> (!a | b) & (a | !b) (a <-> b)
    // a -> b <=> (!a | b)
}

namespace HLD { // preproccessing O(n), operations O(log^2(n))
    // hld with add, set & get on tree ways

    constexpr int MAXN = (1 << 17);
    // maximum tree nodes count

    using T = int64_t;
    // tree nodes type

    T negative_value = {};
    // such value that combines(X, negative_value) == X
    // using in get for empty returns

    T base_add_value = {};
    // such value that add_merge(node, base_val) = node
    // using to fill segment add value to default

    T merge(const T& a, const T& b) {
        // using to merge two segments
        // seg = merge(seg_left, seg_right)
        return a + b;
    }

    T mapping(const T& a, int k) {
        // using to get value on segment that contains k equals values
        // seg = [ val, val, ..., val - k times ] -> seg = mapping(val, k)
        return k * a;
    }

    T add_merge(const T& a, const T& b) { // merging values that adding to nodes segments
        // using to merge segment add_
        // seg_add = add_merge(seg_add_left + seg_add_right)
        return a + b;
    }

    // ------------------------------------
    std::vector<int> g[MAXN];
    int sz[MAXN], p[MAXN], tin[MAXN], tout[MAXN], used[MAXN], head[MAXN];
    int t = 0;
    int size_;
    std::vector<T> tree_, add_, push_, raw_data_;
    std::vector<bool> push_used_;

    void STBuild(int v = 1, int l = 0, int r = size_ - 1) {
        if (l == r) {
            tree_[v] = raw_data_[l];
            return;
        }
        int mid = (l + r) >> 1;
        STBuild(v << 1, l, mid);
        STBuild(v << 1 | 1, mid + 1, r);
        tree_[v] = merge(tree_[v], tree_[v << 1]);
        tree_[v] = merge(tree_[v], tree_[v << 1 | 1]);
    }

    void STPush(int v, int l, int r) {
        if (push_used_[v]) { // push
            if (l != r) {
                push_used_[v << 1] = push_used_[v << 1 | 1] = true;
                push_[v << 1] = push_[v << 1 | 1] = push_[v];
                add_[v << 1] = add_[v << 1 | 1] = base_add_value;
            }
            tree_[v] = mapping(push_[v], r - l + 1);
            push_used_[v] = false;
        }
        if (l != r) { // push add
            add_[v << 1] = add_merge(add_[v << 1], add_[v]);
            add_[v << 1 | 1] = add_merge(add_[v << 1 | 1], add_[v]);
        }
        tree_[v] = merge(tree_[v], mapping(add_[v], r - l + 1));
        add_[v] = base_add_value;
    }

    T STGet(int v, int tl, int tr, int l, int r) {
        STPush(v, tl, tr);
        if (l > r) { return negative_value; }
        if (l == tl && r == tr) { return tree_[v]; }
        int mid = (tl + tr) >> 1;
        return merge(
                STGet(v << 1, tl, mid, l, std::min(mid, r)),
                STGet(v << 1 | 1, mid + 1, tr, std::max(mid + 1, l), r)
                );
    }

    void STSet(int v, int tl, int tr, int l, int r, T value) {
        STPush(v, tl, tr);
        if (l > r) { return; }
        if (l == tl && r == tr) {
            push_used_[v] = true;
            push_[v] = value;
            add_[v] = base_add_value;
            STPush(v, l, r);
            return;
        }
        int mid = (tl + tr) >> 1;
        STSet(v << 1, tl, mid, l, std::min(mid, r), value);
        STSet(v << 1 | 1, mid + 1, tr, std::max(mid + 1, l), r, value);
        tree_[v] = merge(tree_[v << 1], tree_[v << 1 | 1]);
    }

    void STAdd(int v, int tl, int tr, int l, int r, T value) {
        STPush(v, tl, tr);
        if (l > r) { return; }
        if (l == tl && r == tr) {
            add_[v] = add_merge(add_[v], value);
            STPush(v, l, r);
            return;
        }
        int mid = (tl + tr) >> 1;
        STAdd(v << 1, tl, mid, l, std::min(mid, r), value);
        STAdd(v << 1 | 1, mid + 1, tr, std::max(mid + 1, l), r, value);
        tree_[v] = merge(tree_[v << 1], tree_[v << 1 | 1]);
    }

    inline bool ancestor (int a, int b) { return tin[a] <= tin[b] && tin[b] < tout[a]; }

    void _up_get(int& a, int& b, T& ans) {
        while (!ancestor(head[a], b)) {
            ans = merge(ans, STGet(1, 0, size_ - 1, tin[head[a]], tin[a]));
            a = p[head[a]];
        }
    }

    void _up_add(int& a, int& b, T value) {
        while (!ancestor(head[a], b)) {
            STAdd(1, 0, size_ - 1, tin[head[a]], tin[a], value);
            a = p[head[a]];
        }
    }

    void _up_set(int& a, int& b, T value) {
        while (!ancestor(head[a], b)) {
            STSet(1, 0, size_ - 1, tin[head[a]], tin[a], value);
            a = p[head[a]];
        }
    }

    void _set_sizes(int v = 0) {
        sz[v] = 1;
        for (auto &to: g[v]) {
            if (p[to] == -1 && to) {
                p[to] = v;
                _set_sizes(to);
                sz[v] += sz[to];
                if (sz[to] > sz[g[v][0]]) { // to - heaviest child
                    std::swap(to, g[v][0]);
                }
            }
        }
    }

    void _build_hld(int v, std::vector<T>& vals) {
        used[v] = 1;
        tin[v] = t++;
        raw_data_[tin[v]] = vals[v];
        for (const auto &to: g[v]) {
            if (used[to]) { continue; }
            // to - is heaviest -> head[v] else to
            head[to] = (to == g[v][0] ? head[v] : to);
            _build_hld(to, vals);
        }
        tout[v] = t;
    }

    // ************************ main function ************************

    void add_edge(int a, int b) { // add edge to tree
        g[a].push_back(b);
        g[b].push_back(a);
    }

    void prepare_hld(int n, std::vector<T>& vals) { // prepare hld
        // n - number of tree vertexes
        std::memset(&p, -1, n << 2);
        _set_sizes();
        size_ = n;
        tree_.resize(size_ << 2);
        add_.resize(size_ << 2, base_add_value);
        push_.resize(size_ << 2);
        push_used_.resize(size_ << 2, false);
        std::memset(&used, 0, n);
        raw_data_.resize(n);
        _build_hld(0, vals);
        STBuild();
    }

    void Add(int a, int b, T value) { // add value to all vertexes on way a-b
        _up_add(a, b, value);
        _up_add(b, a, value);
        if (!ancestor(a, b)) {
            std::swap(a, b);
        }
        STAdd(1, 0, size_ - 1, tin[a], tin[b], value);
    }

    void Set(int a, int b, T value) { // set value to all vertexes on way a-b
        _up_set(a, b, value);
        _up_set(b, a, value);
        if (!ancestor(a, b)) {
            std::swap(a, b);
        }
        STSet(1, 0, size_ - 1, tin[a], tin[b], value);
    }

    T Get(int a, int b) { // get sum of values from all vertexes on way a-b
        T ans = negative_value;
        _up_get(a, b, ans);
        _up_get(b, a, ans);
        if (!ancestor(a, b)) {
            std::swap(a, b);
        }
        return merge(ans, STGet(1, 0, size_ - 1, tin[a], tin[b]));
    }
}
