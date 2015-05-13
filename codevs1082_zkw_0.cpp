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

const int N = 200005, M = 262144;

int n, m;
LL a[M * 2 + 1], b[M * 2 + 1];

void init() {
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
}

void add(LL a[], int x, LL y) {
    for (a[x += M] += y, x >>= 1; x; x >>= 1) {
        a[x] = a[x << 1] + a[x << 1 | 1];
    }
}

LL gao(LL a[], int s, int t) {
    LL ans = 0;
    for (s = s + M - 1, t = t + M + 1; s ^ t ^ 1; s >>= 1, t >>= 1) {
        if (~s & 1) ans += a[s ^ 1];
        if (t & 1) ans += a[t ^ 1];
    }
    return ans;
}

int h[N];

int main() {
    int f, l, r, x;
    LL al, ar;
    while (~scanf("%d", &n)) {
        init();
        FOR (i, 1, n) scanf("%d", &h[i]);
        h[0] = 0;
        FOR (i, 1, n) {
            add(a, i, h[i] - h[i - 1]);
            add(b, i, (LL) i * (h[i] - h[i - 1]));
        }
        scanf("%d", &m);
        while (m--) {
            scanf("%d", &f);
            if (f == 1) {
                scanf("%d %d %d", &l, &r, &x);
                add(a, l, x), add(a, r + 1, -x);
                add(b, l, x * l), add(b, r + 1, (r + 1) * (-x));
            } else {
                scanf("%d %d", &l, &r);
                ar = (r + 1) * gao(a, 1, r) - gao(b, 1, r);
                if (l == 1) al = 0;
                else al = l * gao(a, 1, l - 1) - gao(b, 1, l - 1);
                printf("%lld\n", ar - al);
            }
        }
    }
    return 0;
}
