const int N = 1e5, VN = 2 * N;

map<char,int> t[VN];
int l[VN], r[VN], p[VN], term[VN]; // ребро p[v] -> v это отрезок [l[v], r[v]) исходной строки
int cc, suf[VN], vn = 2, v = 1, pos; // идём по ребру из p[v] в v, сейчас стоим в pos

void init() {
	for (int i = 0; i < 127; i++) t[0][i] = 1; // 0 = фиктивная, 1 = корень
	l[1] = -1;
}

void add(char c, int i, const string &s) {
	auto new_leaf = [&](int v) {
		p[vn] = v, l[vn] = i, r[vn] = N, t[v][c] = vn++;
    };
    go:;
    if (r[v] <= pos) { 
    	if (!t[v].count(c)) {
    		new_leaf(v), v = suf[v], pos = r[v];
    		goto go;
    	}
    	v = t[v][c], pos = l[v] + 1;
    } else if (c == s[pos]) {
    	pos++;
    } else {
    	int x = vn++;
    	l[x] = l[v], r[x] = pos, l[v] = pos;
    	p[x] = p[v], p[v] = x;
    	t[p[x]][s[l[x]]] = x, t[x][s[pos]] = v;
    	new_leaf(x);
    	v = suf[p[x]], pos = l[x];
    	while (pos < r[x])
    		v = t[v][s[pos]], pos += r[v] - l[v];
    	suf[x] = (pos == r[x] ? v : vn);
    	pos = r[v] - (pos - r[x]);
    	goto go;
    }
}

int main() {
	init();
	string s; cin >> s;
	s += (char)0; // term
	for (int i = 0; i < (int)s.size(); i++) {
		add(s[i], i, s);
	}
	for (int i = 1; i < vn; i++) r[i] = min(r[i], (int)s.size());
	for (int i = 1; i < vn; i++) {
		for (auto c : t[i]) err("%d  [%d, %d)  %d\n", i, l[c.second], r[c.second], c.second);
	}
}