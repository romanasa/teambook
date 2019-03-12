
namespace fft {
    const int MOD = 998244353;
    const int maxB = 20;
    const int maxN = 1 << maxB;
    const int initROOT = 646;

    int root[maxN];
    int rev[maxN];
    int N;

    ll inv(ll a, ll m = MOD) {
        if (a == 0) return 0;
        return ((1 - inv(m % a, a) * m) / a + m) % m;
    }

    void _init(int cur_base) {
        N = 1 << cur_base;
        for (int i = 0; i < N; i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (cur_base - 1));


        int ROOT = initROOT;
        for (int i = cur_base; i < 20; i++) ROOT = 1ll * ROOT * ROOT % MOD;

        int NN = N >> 1;
        int z = 1;
        for (int i = 0; i < NN; i++) {
            root[i + NN] = z;
            z = z * (ll)ROOT % MOD;
        }
        for (int i = NN - 1; i > 0; --i) root[i] = root[2 * i];
    }

    void fft(int *a, int *f) {
        for (int i = 0; i < N; i++) f[i] = a[rev[i]];
        for (int k = 1; k < N; k <<= 1) {
            for (int i = 0; i < N; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    int z = f[i + j + k] * (ll)root[j + k] % MOD;
                    f[i + j + k] = (f[i + j] - z + MOD) % MOD;
                    f[i + j] = (f[i + j] + z) % MOD;
                }
            }
        }
    }

    int A[maxN], B[maxN], C[maxN];
    int F[maxN], G[maxN];

    void _mult(int eq) {
        fft(A, F);
        if (eq)
            for (int i = 0; i < N; i++)
                G[i] = F[i];
        else fft(B, G);
        int invN = inv(N);
        for (int i = 0; i < N; i++) A[i] = F[i] * (ll)G[i] % MOD * invN % MOD;
        reverse(A + 1, A + N);
        fft(A, C);
    }

    void mult(int n1, int n2, int eq = 0) {
        int n = n1 + n2, cur_base = 0;
        while ((1 << cur_base) < n) cur_base++;
        _init(cur_base + 1);

        for (int i = n1; i < N; ++i) A[i] = 0;
        for (int i = n2; i < N; ++i) B[i] = 0;

        _mult(eq);

        //forn(i, n1 + n2) C[i] = 0;
        //forn(i, n1) forn(j, n2) C[i + j] = (C[i + j] + A[i] * (ll)B[j]) % mod;
    }

    vector<int> mult(vector<int> A, vector<int> B) {
        for (int i = 0; i < A.size(); i++) fft::A[i] = A[i];
        for (int i = 0; i < A.size(); i++) fft::B[i] = B[i];
        mult(A.size(), B.size());
        vector<int> C(A.size() + B.size());
        for (int i = 0; i < A.size() + B.size(); i++) C[i] = fft::C[i];
        return C;
    }
}