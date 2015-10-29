#include <bits/stdc++.h>

#define file_r(x) freopen(x, "r", stdin)
#define file_w(x) freopen(x, "w", stdout)
#define rep(i, n) for (int i = 0; i < n; i++)
#define FOR(i, n, m) for (int i = n; i <= m; i++)
#define repe(i, u) for (int i = head[u]; ~i; i = nxt[i])
#define FORD(i, n, m) for (int i = n; i >= m; i--)
#define repit(i, c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define pause cout << " press ant key to continue...", cin >> chh

#define pb push_back
#define mp make_pair
#define ins insert
#define X first
#define Y second
#define be begin
#define nb rbegin
#define er erase
#define SZ(c) c.size()
#define ins insert

#define sc(n) cout << #n << "= " << n, system("pause")
#define sc2(n, m) cout << #n << "= " << n << " " << #m << "= " << m, system("pause")
#define sc3(n, m, k) cout << #n << "= " << n << " " << #m << "= " << m << " " << #k << "= " << k, system("pause")
#define sc4(n, m, k, b) cout << #n << "= " << n << " " << #m << "= " << m << " " << #k << "= " << k << " " << #b << "= " << b, system("pause")

using namespace std;
int chh;

typedef long long LL;

template<class T>
inline char read(T &n){
    T x = 0, tmp = 1; char c = getchar();
    while ((c < '0' || c > '9') && c != '-' && c != EOF) c = getchar();
    if (c == '-') c = getchar(), tmp = -1;
    while (c >= '0' && c <= '9') x *= 10, x += (c - '0'), c = getchar();
    n = x * tmp;
    return c;
}

template <class T>
inline void write(T n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    int len = 0,data[20];
    while (n) {
        data[len++] = n%10;
        n /= 10;
    }
    if (!len) data[len++] = 0;
    while (len--) putchar(data[len] + 48);
}

const int N = 200005, SZ = 262144;

int n, m, h, M;
LL t[SZ * 2], d[SZ];
int b[N];

void init() {
	M = 1;
	while (M <= n) M <<= 1;
	h = sizeof(int) * 8 - __builtin_clz(M);
	rep (i, n) t[M + i] = b[i];
	FORD (i, M - 1, 1) t[i] = t[i << 1] + t[i << 1 | 1], d[i] = 0;
}

void calc(int p, int k) {
    t[p] = t[p << 1] + t[p << 1 | 1] + d[p] * k;
}

void apply(int p, LL value, int k) {
    t[p] += value * k;
    if (p < M) d[p] += value;
}

void build(int l, int r) {
    int k = 2;
    for (l += M, r += M - 1; l > 1; k <<= 1) {
        l >>= 1, r >>= 1;
        for (int i = r; i >= l; --i) calc(i, k);
    }
}

void push(int l, int r) {
    int s = h, k = 1 << (h - 1);
    for (l += M, r += M - 1; s > 0; --s, k >>= 1)
        for (int i = l >> s; i <= r >> s; ++i) if (d[i] != 0) {
                apply(i << 1, d[i], k);
                apply(i << 1 | 1, d[i], k);
                d[i] = 0;
            }
}

//[l, r)
void modify(int l, int r, LL value) {
    if (value == 0) return;
    push(l, l + 1);
    push(r - 1, r);
    int l0 = l, r0 = r, k = 1;
    for (l += M, r += M; l < r; l >>= 1, r >>= 1, k <<= 1) {
        if (l & 1) apply(l++, value, k);
        if (r & 1) apply(--r, value, k);
    }
    build(l0, l0 + 1);
    build(r0 - 1, r0);
}

//[l, r)
LL query(int l, int r) {
    push(l, l + 1);
    push(r - 1, r);
    LL res = 0;
    for (l += M, r += M; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += t[l++];
        if (r & 1) res += t[--r];
    }
    return res;
}

int main() {
    int f, l, r, x;
    LL al, ar;
    while (~scanf("%d", &n)) {
        rep (i, n) scanf("%d", &b[i]);
        init();
        scanf("%d", &m);
        while (m--) {
            scanf("%d", &f);
            if (f == 1) {
                scanf("%d %d %d", &l, &r, &x);
                modify(l - 1, r, x);
            } else {
                scanf("%d %d", &l, &r);
                printf("%lld\n", query(l - 1, r));
            }
        }
    }
    return 0;
}
