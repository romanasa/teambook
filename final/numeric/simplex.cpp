#include <bits/stdc++.h>

#define err(...) //fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;


const double infd = 1e18;
const double eps = 1e-6;
//#define double long double
using namespace std;

struct LP {
    vector<vector<double> > A;
    vector<double> c;
    double res = 0;

    int get_e() {
        return A.size();
    }

    int get_v() {
        return c.size();
    }
};

struct CLP : public LP {
    vector<int> Xi;
};

enum STATUS {
    UNBOUNDED,
    FINISHED,
    OK,
};

void print(CLP &p) {
    err("CLP %3.3f\n", p.res);
    for (int i = 0; i < p.get_e(); i++) {
        err("%d ", p.Xi[i]);
        for (int j = 0; j <= p.get_v(); j++) {
            err("%5.2f ", p.A[i][j]);
        }
        err("\n");
    }
    for (int i = 0; i < p.get_v(); i++) {
        err("%5.2f ", p.c[i]);
    }
    err("\n");
}

void transpose(CLP &p, int cur_v, int cur_e) {
    p.res += p.c[cur_v] * (-p.A[cur_e].back() / p.A[cur_e][cur_v]);
    int old_xi = p.Xi[cur_e];
    double c = p.A[cur_e][cur_v];
    assert(abs(c) > eps);
    p.Xi[cur_e] = cur_v;
    p.A[cur_e][old_xi] = -1;
    p.A[cur_e][cur_v] = 0;
    for (int i = 0; i <= p.get_v(); i++) {
        p.A[cur_e][i] *= -1 / c;
    }

    auto trans = [&](vector<double> &x) {
        double cx = x[cur_v];
        for (int j = 0; j < (int) x.size(); j++) {
            x[j] += cx * p.A[cur_e][j];
        }
        x[cur_v] = 0;
    };

    for (int i = 0; i < p.get_e(); i++) {
        if (i == cur_e) continue;
        trans(p.A[i]);
    }
    trans(p.c);
}

STATUS simplex_iterate(CLP &p) {
    for (int i = 0; i < p.get_e(); i++) {
        assert(p.A[i].back() > -eps);
    }
    double cur_max = -infd;
    int cur_v = -1;
    for (int i = 0; i < p.get_v(); i++) {
        if (cur_max < p.c[i]) {
            cur_max = p.c[i];
            cur_v = i;
        }
    }
    if (cur_max < eps) {
        err("Finished\n");
        return STATUS::FINISHED;
    }
    assert(cur_v >= 0);
    double cur_min = infd;
    int cur_e = -1;
    for (int i = 0; i < p.get_e(); i++) {
        if (p.A[i][cur_v] > -eps) continue;
        double t = -p.A[i].back() / p.A[i][cur_v];
        if (cur_min > t) {
            cur_min = t;
            cur_e = i;
        }
    }
    if (cur_e == -1) {
        return STATUS::UNBOUNDED;
    }
    transpose(p, cur_v, cur_e);
    err("Ok\n");
    print(p);
    return STATUS::OK;
}

pair<vector<double>, double> simplex(CLP &p, int num_iter) {
    err("Start simplex\n");
    print(p);
    assert(num_iter > 0);
    STATUS status;
    for (int i = 0; i < num_iter; i++) {
        status = simplex_iterate(p);
        if (status != STATUS::OK) {
            break;
        }
    }
    int num_real_v = p.get_v() - p.get_e();
    vector<double> solution(num_real_v);
    for (int i = 0; i < p.get_e(); i++) {
        if (p.Xi[i] < num_real_v) {
            solution[p.Xi[i]] = p.A[i].back();
        }
    }
    if (status == STATUS::UNBOUNDED) {
        return {solution, infd};
    }
    return {solution, p.res};
}

pair<vector<double>, double> get_solution(CLP p, int num_iter) {
    auto np = p;
    for (int i = 0; i < p.get_e(); i++) {
        np.A[i].push_back(1);
        swap(np.A[i][p.get_v()], np.A[i][p.get_v() + 1]);
    }
    np.c = vector<double>(p.get_v() + 1);
    np.c.back() = -1;
    int lmbd = np.get_v() - 1;

    double cur_min = infd;
    int ind_min = -1;
    for (int i = 0; i < np.get_e(); i++) {
        if (cur_min > np.A[i].back()) {
            cur_min = np.A[i].back();
            ind_min = i;
        }
    }
    if (cur_min > -eps) {
        return simplex(p, num_iter);
    }
    transpose(np, lmbd, ind_min);

    err("Adjoint LP\n");
    print(np);
    auto adjoint_solution = simplex(np, num_iter);
    print(np);

    assert(adjoint_solution.second < eps);
    if (adjoint_solution.second < -eps) {
        return {{}, 0};
    }
    int lmbda_ind = -1;
    for (int i = 0; i < np.get_e(); i++) {
        if (np.Xi[i] == lmbd) {
            lmbda_ind = i;
        }
    }
    if (lmbda_ind >= 0) {
        //assert(0);
        bool changed = 0;
        for (int i = 0; i < lmbd; i++) {
            if (abs(np.A[lmbda_ind][i]) > eps) {
                transpose(np, i, lmbda_ind);
                changed = 1;
                break;
            }
        }
        assert(changed);
    }
    for (int i = 0; i < np.get_e(); i++) {
        np.A[i].erase(np.A[i].begin() + lmbd);
    }
    np.res = 0;
    np.c = p.c;

    for (int i = 0; i < np.get_v(); i++) {
        for (int j = 0; j < np.get_e(); j++) {
            if (np.Xi[j] == i) {
                double c = p.c[i];
                np.c[i] = 0;
                for (int k = 0; k < np.get_v(); k++) {
                    np.c[k] += c * np.A[j][k];
                }
                np.res += c * np.A[j].back();
                break;
            }
        }
    }

    auto solution = simplex(np, num_iter);
    return solution;
}

CLP get_canonical_form(LP p) {
    CLP q;
    int nv = p.get_e() + p.get_v();
    for (int i = 0; i < p.get_e(); i++) {
        vector<double> c = p.A[i];
        c.resize(nv + 1);
        swap(c.back(), c[p.get_v()]);
        for (int j = 0; j < p.get_v(); j++) {
            c[j] *= -1;
        }
        q.A.push_back(c);
        q.Xi.push_back(i + p.get_v());
    }
    vector<double> c = p.c;
    c.resize(nv);
    q.c = c;
    return q;
}

void solve() {
    int n, m;
    cin >> n >> m;
    LP p;

    p.c.resize(m + 1);
    vector<vector<int> > E(n), T(n);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        if (a == n - 1 || b == 0) {
            continue;
        }
        T[a].push_back(i);
        E[b].push_back(i);
        if (b == n - 1) {
            p.c[i] = 1;
        }
        vector<double> A(m + 2);
        A[i] = 1;
        A.back() = c;
        p.A.push_back(A);
    }
    T[n - 1].push_back(m);
    E[0].push_back(m);
    for (int i = 0; i < n; i++) {
        vector<double> A(m + 2);
        for (auto a : E[i]) {
            A[a]++;
        }
        for (auto a : T[i]) {
            A[a]--;
        }
        p.A.push_back(A);
        for (auto &v : A) {
            v *= -1;
        }
        p.A.push_back(A);
    }

    auto cp = get_canonical_form(p);
    auto solution = get_solution(cp, 2000);
    int res = solution.second;
    cout << res << '\n';
    for (int i = 0; i < m; i++) {
        double x = solution.first[i];
        assert(abs(x - int(x)) < 0.001);
        err("%5.3f ", x);
        cout << (int) x << ' ';
    }
    err("%0.5f\n", solution.second);
}
