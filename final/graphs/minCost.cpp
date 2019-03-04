ll findflow(int s, int t) {
    ll cost = 0;
    ll flow = 0;
    
    forn(i, N) G[i] = inf;

    queue<int> q;

    q.push(s);
    used[s] = true;
    G[s] = 0;

    while (q.size()) {
        int v = q.front();
        used[v] = false;
        q.pop();

        forn(i, E[v].size()) {
            auto &e = E[v][i];
            if (e.f < e.c && G[e.to] > G[v] + e.w) {
                G[e.to] = G[v] + e.w;
                if (!used[e.to]) {
                    q.push(e.to);
                    used[e.to] = true;
                }
            }
        }
    }

    while (1) {
        forn(i, N)
            d[i] = inf, p[i] = { -1, -1 }, used[i] = 0;

        d[s] = 0;
        while (1) {
            int v = -1;
            forn(i, N) {
                if (!used[i] && d[i] != inf && (v == -1 || d[i] < d[v]))
                    v = i;
            }
            if (v == -1)
                break;
            used[v] = 1;

            forn(i, E[v].size()) {

                auto &e = E[v][i];
                if (e.f < e.c && d[e.to] > d[v] + e.w + G[v] - G[e.to]) {
                    p[e.to] = mp(v, i);
                    d[e.to] = d[v] + e.w + G[v] - G[e.to];
                }
            }

        }
        if (p[t].first == -1) {
            break;
        }
        int add = inf;
        for (int i = t; p[i].first != -1; i = p[i].first) {
            add = min(add, E[p[i].first][p[i].second].c - E[p[i].first][p[i].second].f);
        }
        for (int i = t; p[i].first != -1; i = p[i].first) {
            auto &e = E[p[i].first][p[i].second];
            cost += 1ll * add * e.w;
            e.f += add;
            E[e.to][e.back].f -= add;
        }
        flow += add;
        if (add == 0)
            break;
        forn(i, N)
            G[i] += d[i];
    }
    return cost;
}
