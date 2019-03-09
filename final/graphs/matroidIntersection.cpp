struct Graph {
    vector<vector<int>> G;

    Graph(int n = 0) {
        G.resize(n);
    }

    void add_edge(int v, int u) {
        G[v].push_back(u);
    }

    vector<int> get_path(vector<int> &s, vector<int> &t) {
        int n = G.size();
        vector<int> dist(n, inf), pr(n, -1);
        queue<int> Q;
        for (int i : s) {
            dist[i] = 0;
            Q.push(i);
        }
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            for (int to : G[v]) if (dist[to] > dist[v] + 1) {
                dist[to] = dist[v] + 1;
                pr[to] = v;
                Q.push(to);
            }
        }
        int V = -1;
        for (int i : t) if (V == -1 || dist[i] < dist[V]) {
            V = i;
        }
        if (V == -1 || dist[V] == inf) return {};
        vector<int> path;
        while (V != -1) {
            path.push_back(V);
            V = pr[V];
        }
        return path;
    }
};

void get_ans(vector<int> &used, int m) {
    Graph G(m);
    for (int i = 0; i < m; ++i) if (used[i]) {
        Gauss gauss;
        vector<int> color(130, 0);
        for (int j = 0; j < m; ++j) if (used[j] && j != i) {
                gauss.add(a[j]);
                color[c[j]] = 1;
            }
        for (int j = 0; j < m; ++j) if (!used[j]) {
            if (gauss.check(a[j])) {
                G.add_edge(i, j);
            }
            if (!color[c[j]]) {
                G.add_edge(j, i);
            }
        }
    }

    Gauss gauss;
    vector<int> color(130, 0);
    for (int i = 0; i < m; ++i) if (used[i]) {
        gauss.add(a[i]);
        color[c[i]] = 1;
    }
    vector<int> x1, x2;
    for (int i = 0; i < m; ++i) if (!used[i]) {
        if (gauss.check(a[i])) {
            x1.push_back(i);
        }
        if (!color[c[i]]) {
            x2.push_back(i);
        }
    }
    vector<int> path = G.get_path(x1, x2);
    if (!path.size()) return;
    for (int i : path) used[i] ^= 1;
    get_ans(used, m);
}