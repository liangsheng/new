#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

#define LL long long
#define ULL unsigned long long
#define mod 1000000007
#define eps 1e-8
#define MP make_pair
#define mxn 110005

LL A[mxn], B[mxn], C[mxn], F[mxn];

void init( int n ) {
    for( int i = 1; i <= n; i += 300 ) {
        B[i] = A[i]; C[i] = 1;
        B[i+1] = A[i]; C[i+1] = A[i+1] + 1;
        for( int j = i + 2; j < i + 300; ++j ) {
            B[j] = (B[j-1] + B[j-2] * A[j]) % mod;
            C[j] = (C[j-1] + C[j-2] * A[j]) % mod;
        }
    }
}

int main()
{
    //ios_base::sync_with_stdio(false);
    int t, n, m, l, r;
    cin >> t;
    while( t-- ) {
        cin >> n >> m;
        for( int i = 1; i <= n; ++i ) scanf( "%lld", A + i );
        init(n);
        while( m-- ) {
            scanf( "%d%d", &l, &r );
            if( r - l <= 350 ) {
                F[l] = A[l];
                F[l+1] = A[l+1];
                for( int i = l + 2; i <= r; ++i )
                    F[i] = (F[i-1] + F[i-2] * A[i]) % mod;
                printf( "%lld\n", F[r] );
                continue;
            }
            int k = 1;
            while( k <= l + 1 ) k += 300;
            F[l] = A[l]; F[l+1] = A[l+1];
            for( int i = l + 2; i < k; ++i )
                F[i] = (F[i-1] + F[i-2] * A[i]) % mod;
            for( int i = k, j; ; i = j ) {
                j = i + 300;
                if( j <= r ) {
                    F[j-2] = (B[j-2] * F[i-2] % mod + C[j-2] * F[i-1] % mod) % mod;
                    F[j-1] = (B[j-1] * F[i-2] % mod + C[j-1] * F[i-1] % mod) % mod;
                }
                else {
                    F[r] = (B[r] * F[i-2] % mod + C[r] * F[i-1] % mod) % mod;
                    printf( "%lld\n", F[r] );
                    break;
                }
            }
        }
    }
    return 0;
}
