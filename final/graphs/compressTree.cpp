vector<pair<int, int>> compressTree(LCA& lca, const vi& subset) {
	static vector<int> rev; rev.resize(sz(lca.dist));
	vi li = subset, &T = lca.time;
	auto cmp = [&](int a, int b) { return T[a] < T[b]; };
	sort(all(li), cmp);
	int m = sz(li)-1;
	rep(i,0,m) {
		int a = li[i], b = li[i+1];
		li.push_back(lca.query(a, b));
	}
	sort(all(li), cmp);
	li.erase(unique(all(li)), li.end());
	rep(i,0,sz(li)) rev[li[i]] = i;
	vpi ret = {pii(0, li[0])};
	rep(i,0,sz(li)-1) {
		int a = li[i], b = li[i+1];
		ret.emplace_back(rev[lca.query(a, b)], b);
	}
	return ret;
}