#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>

#define pause cout << " press ansy key to continue...",  cin >> chh
#define file_r(x) freopen(x,  "r",  stdin)
#define file_w(x) freopen(x,  "w",  stdout)
#define lowbit(x) ((x) & (-x))
#define repit(i, c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define rep(i, n) for (int i = 0; i < (n); i++)
#define repe(i, u) for (int i = head[u]; i != -1; i = nxt[i])
#define repd(i, n) for (int i = (n - 1); i >= 0; i--)
#define FOR(i, n, m) for (int i = (n); i <= (m); i++)
#define FORD(i, n, m) for (int i = (n); i >= (m); i--)
#define pb push_back
#define X first
#define Y second
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define SZ(c) (c).size()
#define ALL(c) (c).begin(), (c).end()
#define sqr(r) ((r) * (r))
#define dis(x1, y1, x2, y2) (((x1) - (x2)) * ((x1) - (x2)) + ((y1) - (y2)) * ((y1) - (y2)))

#define bug(x) cout << #x" = " << x << endl
#define bug2(x, y) cout << #x" = " << x << " " << #y" = " << y << endl
#define bug3(x, y, z) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << endl
#define bug4(x, y, z, w) cout << #x" = " << x << " " << #y" = " << y << " " << #z" = " << z << " " << #w" = " << w << endl

#define in(n) scanf("%d", &n)
#define in2(n, m) scanf("%d %d", &n, &m)
#define in3(x, y, z) scanf("%d %d %d", &x, &y, &z)

using namespace std;
int chh;

typedef vector<int> vi;
typedef set<int> si;
typedef map<int, int> mii;
typedef pair<int, int> pii;
typedef pair<int, pii> pi3;
typedef vector< pair<int, int> > vpii;
typedef long long LL;

inline void scan(int &t) {
    int n = 0, s = 1;
    char ch = getchar();
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') s = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') n = n * 10 + ch - '0', ch = getchar();
    t = n * s;
}

const int N = 100005, MOD = 1000000007;
int M = 300;

int T, n, m;
int A[N], B[N], C[N], F[N];

void init() {
    int i, j;
    for (i = 0; i < n; i += M) {
        B[i] = A[i], C[i] = 1;
        B[i + 1] = A[i], C[i + 1] = A[i + 1] + 1;
        for (j = i + 2; j < n && j < i + M; j++) {
            B[j] = (B[j - 1] + (LL) B[j - 2] * A[j] % MOD) % MOD;
            C[j] = (C[j - 1] + (LL) C[j - 2] * A[j] % MOD) % MOD;
        }
    }
}

int gao(int l, int r) {
    F[l] = A[l], F[l + 1] = A[l + 1];
    if (r <= l + 1) return F[r];
    if (r - l + 1 <= M + 10) {
        FOR (i, l + 2, r) F[i] = (F[i - 1] + (LL) F[i - 2] * A[i] % MOD) % MOD;
        return F[r];
    }
    l += 2;
    while (l % M) F[l] = (F[l - 1] + (LL) F[l - 2] * A[l] % MOD) % MOD, l++;
    while (r - l + 1 > M) {
        int x = l + M - 2, y = x + 1;
        F[x] = ((LL) B[x] * F[l - 2] + (LL) C[x] * F[l - 1]) % MOD;
        F[y] = ((LL) B[y] * F[l - 2] + (LL) C[y] * F[l - 1]) % MOD;
        l += M;
    }
    F[r] = ((LL) B[r] * F[l - 2] + (LL) C[r] * F[l - 1]) % MOD;
    return F[r];
}

int main() {
    int l, r, k;
    scan(T);
    while (T--) {
        scan(n), scan(m);
        M = int(sqrt(n * 1.0));
        rep (i, n) scan(A[i]);
        init();
        while (m--) {
            scan(l), scan(r);
            printf("%d\n", gao(l - 1, r - 1));
        }
    }
    return 0;
}
