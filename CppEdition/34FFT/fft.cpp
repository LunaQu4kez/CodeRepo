#include<bits/stdc++.h>
using namespace std;

const int maxn = 6000010;
const double PI = acos(-1);

int n, m, k, sm;
int tax[maxn];
complex<double> F[maxn], G[maxn];

void make_rev(const int N);
void FFT(complex<double> *A, int N);

inline int read() {
    int x = 0, f = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return x * f;
}

int main() {
    n = read();
    m = read();
    for (int i = 0, x; i <= n; ++i) {
        x = 0; x = read(); F[i] = x;
    }
    for (int i = 0, x; i <= m; ++i) {
        x = 0; x = read(); G[i] = x;
    }
    sm = n + m; k = 1;
    while (k <= sm) k <<= 1;
    make_rev(k);
    FFT(F, k); 
    FFT(G, k);
    for (int i = 0; i < k; ++i) F[i] *= G[i];
    FFT(F, k);
    reverse(F + 1, F + k);
    for (int i = 0; i <= sm; ++i) printf("%d ", int((F[i].real()) / k + 0.5));

  return 0;
}

void FFT(complex<double> *A, int N) {
    for (int i = 1; i < N; ++i) if (tax[i] > i) swap(A[i], A[tax[i]]);
    for (int len = 2, M = 1; len <= N; M = len, len <<= 1) {
        complex<double> W(cos(PI / M), sin(PI / M)), w(1.0, 0.0);
        for (auto L = 0, R = len - 1; R <= N; L += len, R += len) {
            auto w0 = w;
            for (auto p = L, lim = L + M; p < lim; ++p) {
                auto x = A[p] + w0 * A[p + M], y = A[p] - w0 * A[p + M];
                A[p] = x; A[p + M] = y;
                w0 *= W;
            }
        }
    }
}

void make_rev(const int N) {
    int d = N >> 1, p = 0;
    tax[p++] = 0;
    tax[p++] = d;
    for (int w = 2; w <= N; w <<= 1) {
        d >>= 1;
        for (int p0 = 0; p0 < w; ++p0) tax[p++] = tax[p0] | d;
    }
}