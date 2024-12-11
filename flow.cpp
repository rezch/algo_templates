#include <bits/stdc++.h>


struct Dinic {
    explicit Dinic(int n) : n(n), g(n) { }

    struct Edge {
        int to;
        int rev;
        int flow;
        int cap;
    };

    int n{}, s{}, t{};
    std::vector<int> level;
    std::vector<int> done;
    std::vector<std::vector<Edge>> g;

    void add_edge(int u, int v, int cap) {
        Edge a = { v, (int)g[v].size(), 0, cap };
        Edge b = { u, (int)g[u].size(), 0, cap };
        g[u].push_back(a);
        g[v].push_back(b);
    }

    bool bfs() {
        level.assign(n, -1);
        level[s] = 0;
        std::queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto& e : g[u]) {
                int v = e.to;
                if (level[v] != -1 || e.flow >= e.cap) continue;
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
        return level[t] != -1;
    }

    int dfs(int u, int flow) {
        if (!flow) return 0;
        if (u == t) return flow;
        for (int& i = done[u]; i < g[u].size(); i++) {
            Edge& e = g[u][i];
            if (e.cap <= e.flow) continue;
            int v = e.to;
            if (level[v] != level[u] + 1) continue;
            int pushed = dfs(v, std::min(flow, e.cap - e.flow));
            if (!pushed) continue;
            e.flow += pushed;
            g[v][e.rev].flow -= pushed;
            return pushed;
        }
        return 0;
    }

    int max_flow(int s_, int t_) {
        s = s_;
        t = t_;
        int flow{};
        while (bfs()) {
            done.assign(n, 0);
            while (int pushed = dfs(s, INT64_MAX))
                flow += pushed;
        }
        return flow;
    }
};

struct FordFulkerson {
    explicit FordFulkerson(int n) : g(n << 1, std::vector<int>(n << 1)) { }

    std::vector<std::vector<int>> g;

    void add_edge(int u, int v, int w, bool two_way = false) {
        // split edge
        // u -> v => u -> u' -> v
        _add_edge(u, u << 1, w, two_way);
        _add_edge(u << 1, v, w, two_way);
    }

    void _add_edge(int u, int v, int w, bool two_way = false) {
        g[u][v] = w;
        if (two_way) g[v][u] = w;
    }
 
    int bfs(int s, int t, std::vector<int>& parent) {
        std::queue<int> q;
		q.push(s);
		while (!q.empty()) {
			int node = q.front();
			q.pop();
			for (int son = 0; son < g.size(); ++son) {
				if (g[node][son] <= 0 || parent[son] != -1) continue;
				parent[son] = node;
				q.push(son);
			}
		}
		return parent[t] != -1;
    }

    int max_flow(int s, int t) {
        int n = g.size();
	    std::vector<int> parent(n, -1);
        int flow{};
        while (bfs(s, t, parent)) {
            int curr_flow = INT32_MAX;
            for (int node = t; node != s; node = parent[node]) {
                curr_flow = std::min(curr_flow, g[parent[node]][node]);
            }
            for (int node = t; node != s; node = parent[node]) {
                g[parent[node]][node] -= curr_flow;
                g[node][parent[node]] += curr_flow;
            }
            flow += curr_flow;
            std::fill(parent.begin(), parent.end(), -1);
        }
        return flow;
    }
};
