#include <bits/stdc++.h>


namespace DSU {
    constexpr int SIZE = 8096;
    struct DSU {

        void init() {
            for (int i = 0; i < SIZE; ++i) {
                p[i] = i;
                sz[i] = 1;
            }
        }

        int head(int x) { // O(a(i)) ~ O(1)
            return (x == p[x] ? x : p[x] = head(x));
        }

        void unite(int a, int b) { // O(a(i)) ~ O(1)
            a = head(a), b = head(b);
            if (sz[a] < sz[b]) { std::swap(a, b); }
            p[b] = a;
            sz[a] += sz[b];
        }

    private:
        int p[SIZE], sz[SIZE];
    };
}


namespace DFS {
    void dfs(int v, std::vector<std::vector<int>>& g, std::vector<int>& used, int p = -1) { // O(n + m)
        // v - current vertex, p - parent
        // g - adj list, used - vector of used vertexes (used[i] = 1 if the spfa was in vertex i)
        used[v] = 1;
        for (const auto& to : g[v]) {
            if (used[to]) { continue; }
            dfs(to, v);
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


namespace LCA {
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
        // Shortest path faster algorithm
        // v - current vert (in first call of spfa v - is the start vertex)
        // g - adj list (pair { end of edge, len of edge })
        // used - vector of used vertexes (used[i] = 1 if the spfa was in vertex i)
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

