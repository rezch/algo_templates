#include <bits/stdc++.h>


namespace DSUsize {
    constexpr int SIZE = 8096;

    int p[SIZE], sz[SIZE];

    void init(int n) {
        for (int i = 0; i < n; ++i) {
            p[i] = i;
            sz[i] = 1;
        }
    }

    int head(int x) { // O(a(i)) ~ O(1)
        return (x == p[x] ? x : p[x] = head(p[x]));
    }

    void unite(int a, int b) { // O(a(i)) ~ O(1)
        a = head(a), b = head(b);
        if (sz[a] < sz[b]) { std::swap(a, b); }
        p[b] = a;
        sz[a] += sz[b];
    }
}


namespace DSUrank {
    constexpr int SIZE = 8096;

    int p[SIZE], rank[SIZE];

    void init(int n) {
        std::memset(&rank, 0, n);
        for (int i = 0; i < n; ++i) {
            p[i] = i;
        }
    }

    int head(int x) { // O(a(i)) ~ O(1)
        return (x == p[x] ? x : p[x] = head(p[x]));
    }

    void unite(int a, int b) { // O(a(i)) ~ O(1)
        a = head(a), b = head(b);
        if (rank[a] < rank[b]) { std::swap(a, b); }
        rank[a] = std::max(rank[a], rank[b] + 1);
        p[b] = a;
    }
}


namespace DFS {
    void dfs(int v, std::vector<std::vector<int>>& g, std::vector<int>& used, int p = -1) { // O(n + m)
        // v - current vertex, p - parent
        // g - adj list
        used[v] = 1;
        for (const auto& to : g[v]) {
            if (used[to]) { continue; }
            dfs(to, g, used, v);
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
    constexpr int MAXN = (int)1e6;
    constexpr int MAXLG = 20;

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
    constexpr int LOG = 25, MAXN = 133700;

    int parent[MAXN], depth[MAXN];
    int up[MAXN][LOG];

    void clear() {
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
        std::sort(&(*edges), &(*(edges + E)), [](const auto& l, const auto& r) {
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
                ++cnt;
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
        Edge() = default;
        int from{}, to{}, w{};
    } edges[MAXE];

    int used[MAXV];
    int64_t dist[MAXV];

    struct cmp {
        bool operator() (const Edge& a, const Edge& b) const {
            return a.w < b.w;
        }
    };

    void MST(int V, int E, std::vector<std::vector<Edge>>& edges) {
        // edges[V] = { edges from V to other vertexes }
        int64_t len = 0; // len of MST edges
        std::vector<std::pair<int, int>> ans; // MST edges

        std::priority_queue<Edge, std::vector<Edge>, cmp> q;
        std::memset(&used, 0, V);
        for (int i = 0; i < V; ++i) {
            dist[i] = INF;
        }
        dist[0] = 0;
        q.push({ 0, 0 });

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
        Edge() = default;
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
