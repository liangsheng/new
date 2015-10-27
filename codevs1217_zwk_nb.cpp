//============================================================================
// Name        : codevs1217_zwk_nb.cpp
// Author      : 0222_
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

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

const int N = 1000005, SZ = 1048576, INF = ~0U >> 1;

int n, m, M, h;
int t[SZ * 2], d[SZ * 2], b[N];

void init() {
	M = 1;
	while (M <= n) M <<= 1;
	h = sizeof(int) * 8 - __builtin_clz(M);
	rep (i, n) t[M + i] = b[i];
	FORD (i, M - 1, 1) t[i] = min(t[i << 1], t[i << 1 | 1]);
}

void apply(int p, int value) {
	t[p] += value;
	if (p < M) d[p] += value;
}

void build(int p) {
	while (p > 1) p >>= 1, t[p] = min(t[p << 1], t[p << 1 | 1]) + d[p];
}

void push(int p) {
	for (int s = h; s > 0; --s) {
		int i = p >> s;
		if (d[i] != 0) {
			apply(i << 1, d[i]);
			apply(i << 1 | 1, d[i]);
			d[i] = 0;
		}
	}
}

//[l, r)
void inc(int l, int r, int value) {
	l += M, r += M;
	int l0 = l, r0 = r;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) apply(l++, value);
		if (r & 1) apply(--r, value);
	}
	build(l0);
	build(r0 - 1);
}

//[l, r)
int query(int l, int r) {
	l += M, r += M;
	push(l);
	push(r - 1);
	int res = INF;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res = min(res, t[l++]);
		if (r & 1) res = min(t[--r], res);
	}
	return res;
}

int main() {
	setbuf(stdout, NULL);
	int d, s, t, c;
	read(n), read(m);
	rep (i, n) read(b[i]);
	init();
	FOR (k, 1, m) {
		read(d), read(s), read(t);
		c = query(s - 1, t);
        if (c >= d) inc(s - 1, t, -d);
        else {
            write(-1), puts(""), write(k), puts("");
            return 0;
        }
	}
	puts("0");
	return 0;
}
