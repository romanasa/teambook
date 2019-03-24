vector<vector<int> > delaunayTriangulation(vector<double> x, vector<double> y) {
    int n = x.size(); vector<double> z(n); vector<vector<int>> ret;
    for (int i = 0; i < n; i++) z[i] = x[i] * x[i] + y[i] * y[i];
    for (int i = 0; i < n - 2; i++) for (int j = i + 1; j < n; j++) for (int k = i + 1; k < n; k++) {
        if (j == k) continue;
        double xn = (y[j] - y[i]) * (z[k] - z[i]) - (y[k] - y[i]) * (z[j] - z[i]);
        double yn = (x[k] - x[i]) * (z[j] - z[i]) - (x[j] - x[i]) * (z[k] - z[i]);
        double zn = (x[j] - x[i]) * (y[k] - y[i]) - (x[k] - x[i]) * (y[j] - y[i]);
        bool f = zn < 0;
        for (int m = 0; f && m < n; m++) f = f && ((x[m] - x[i]) * xn + (y[m] - y[i]) * yn + (z[m] - z[i]) * zn <= 0);
        if (f) ret.push_back({i, j, k});
    }
    return ret;
}