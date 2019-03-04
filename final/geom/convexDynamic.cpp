struct convex {
    map<ll, ll> M;
    bool get(int x, int y) {
        if (M.size() == 0)
            return false;
        if (M.count(x))
            return M[x] >= y;
        if (x < M.begin()->first || x > M.rbegin()->first)
            return false;

        auto it1 = M.lower_bound(x), it2 = it1;
        it1--;

        return pt(pt(*it1), pt(x, y)) % pt(pt(*it1), pt(*it2)) >= 0;
    }
    void add(int x, int y) {
        if (get(x, y)) return;
        
        pt P(x, y);
        M[x] = y;

        auto it = M.lower_bound(x), it1 = it;
        it1--;
        auto it2 = it1;
        it2--;

        if (it != M.begin() && it1 != M.begin()) {
            while (it1 != M.begin() && (pt(pt(*it2), pt(*it1)) % pt(pt(*it1), P)) >= 0) {
                M.erase(it1);
                it1 = it2;
                it2--;
            }
        }
        it1 = it, it1++;
        if (it1 == M.end()) return;
        it2 = it1, it2++;

        if (it1 != M.end() && it2 != M.end()) {
            while (it2 != M.end() && (pt(P, pt(*it1)) % pt(pt(*it1), pt(*it2))) >= 0) {
                M.erase(it1);
                it1 = it2;
                it2++;
            }
        }
    }
} H, J;

int solve() {
    int q;
    cin >> q;
    while (q--) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            H.add(x, y);
            J.add(x, -y);
        }
        else {
            if (H.get(x, y) && J.get(x, -y))
                puts("YES");
            else
                puts("NO");
        }
    }
    return 0;
}