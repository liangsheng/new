#include <bits/stdc++.h>

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

const int N = 505;

int n, m, b, MOD;
int a[N], dp[2][N][N];

int main() {
    int ans, now, pre;
    while (~scanf("%d %d %d %d", &n, &m, &b, &MOD)) {
        rep (i, n) scanf("%d", &a[i]);
        now = 0, pre = 1;
        memset(dp[now], 0, sizeof(dp[now]));
        dp[now][0][0] = 1;
        rep (k, n) {
            swap(now, pre);
            memset(dp[now], 0, sizeof(dp[now]));
            rep (i, m + 1) rep (j, b + 1) {
                dp[now][i][j] = dp[pre][i][j];
                if (i > 0 && j - a[k] >= 0) {
                    dp[now][i][j] += dp[now][i - 1][j - a[k]];
                    if (dp[now][i][j] >= MOD) dp[now][i][j] -= MOD;
                }
            }
        }
        ans = 0;
        rep (i, b + 1) {
            ans += dp[now][m][i];
            if (ans >= MOD) ans-= MOD;
        }
        printf("%d\n", ans);
    }
    return 0;
}
















