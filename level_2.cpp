#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 20;
const int KIND = 3;
const int INF = 0x3fffffff;
int dp[maxn][maxn][maxn];
int num_of_block[maxn][KIND];
int num_of_target[KIND];
int cnt[maxn];

int my_ceil(int aim, int temp) {
    int ret = aim/temp + (aim%temp!=0);
    return ret;
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        // Initialization
        for( int i = 0; i < maxn; i++ ) {
            for( int j = 0; j < maxn; j++ ) {
                for( int k = 0; k < maxn; k++ ) {
                    dp[i][j][k] = INF;
                }
            }
        }
        dp[0][0][0] = 0;
        for( int i = 0; i < KIND; i++ ) {
            scanf("%d", &num_of_target[i]);
        }
        int n;
        scanf("%d", &n);
        for( int i = 0; i < n; i++ ) {
            for( int j = 0; j < KIND; j++ ) {
                scanf("%d", &num_of_block[i][j]);
            }
        }
        const int & A = num_of_target[0];
        const int & B = num_of_target[1];
        const int & C = num_of_target[2];
        for( int i = 0; i < n; i++ ) {
            int temp0 = num_of_block[i][0];
            int temp1 = num_of_block[i][1];
            int temp2 = num_of_block[i][2];
            
            int ans = max({my_ceil(A,temp0),my_ceil(B, temp1),my_ceil(C, temp2)});
            
            cnt[i] = ans;
        }
        for( int p = 0; p < n; p++ ) {
            const int & np0 = num_of_block[p][0];
            const int & np1 = num_of_block[p][1];
            const int & np2 = num_of_block[p][2];
            for( int i = 0; i <= A; i++ ) {
                for( int j = 0; j <= B; j++ ) {
                    for( int k = 0; k <= C; k++ ) {
                        for( int m = 0; m <= cnt[p]; m++ ) {
                            if( i>=m*np0 && j>=m*np1 && k>=m*np2 && dp[i-m*np0][j-m*np1][k-m*np2]!= INF ) {
                                dp[i][j][k] = min( dp[i][j][k], dp[i-m*np0][j-m*np1][k-m*np2]+m );
                            }
                        }
                    }
                }
            }
        }
        printf("%d\n", dp[A][B][C]);
    }
    return 0;
}