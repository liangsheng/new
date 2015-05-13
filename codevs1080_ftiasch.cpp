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

inline void scan(int &t) {
    int n = 0, s = 1;
    char ch = getchar();
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') s = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') n = n * 10 + ch - '0', ch = getchar();
    t = n * s;
}

const int N = 100005;

int n, m;
int a[N << 1];

inline int get_id(int s, int t) {
    return (s + t) | (s != t);
}

void init() {
    memset(a, 0, sizeof(a));
}

void update(int s, int t, int k, int v) {
    if (k < s || k > t) return ;
    if (k >= s && k <= t) a[get_id(s, t)] += v;
    if (s != t) {
        int mid = (s + t) >> 1;
        update(s, mid, k, v);
        update(mid + 1, t, k, v);
    }
}

int gao(int s, int t, int l, int r) {
    if (r < s || l > t) return 0;
    if (s >= l && t <= r) return a[get_id(s, t)];
    int mid = (s + t) >> 1;
    return gao(s, mid, l, r) + gao(mid + 1, t, l, r);
}

int main() {
    //file_r("in.txt");
    //file_w("out.txt");
    int x, y, z;
    while (~scanf("%d", &n)) {
        init();
        rep (i, n) {
            scan(x);
            update(0, n - 1, i, x);
        }
        scan(m);
        while (m--) {
            scan(x), scan(y), scan(z);
            if (x == 1) update(0, n - 1, --y, z);
            else printf("%d\n", gao(0, n - 1, --y, --z));
        }
    }
    return 0;
}
