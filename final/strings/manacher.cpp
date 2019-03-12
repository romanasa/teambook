vector<int> Pal1(string s) {
    int n = (int)s.size();
    vector<int> d1(n);
    int l = 0, r = -1;
    for (int i = 0, k; i < n; i++) {
        if (i > r) k = 1;
        else k = min(d1[l + r - i], r - i);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k;
        if (i + k - 1 > r) r = i + k - 1, l = i - k + 1;
    }
    return d1;
}

vector<int> Pal2(string s) {
    int n = (int)s.size();
    vector<int> d2(n);
    int l = 0, r = -1;
    for (int i = 0, k; i < n; i++) {
        if (i > r) k = 0;
        else k = min(d2[l + r - i + 1], r - i + 1);
        while (i + k < n && i - k - 1 >= 0 && s[i + k] == s[i - k - 1]) k++;
        d2[i] = k;
        if (i + k - 1 > r) l = i - k, r = i + k - 1;
    }
    return d2;
}