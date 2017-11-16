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
        for( int p = 0; p < n; p++ ) {
            const int & np0 = num_of_block[p][0];
            const int & np1 = num_of_block[p][1];
            const int & np2 = num_of_block[p][2];
            for( int i = 0; i <= A; i++ ) {
                for( int j = 0; j <= B; j++ ) {
                    for( int k = 0; k <= C; k++ ) {
                        if( i>=np0 && j>=np1 && k>=np2 && dp[i-np0][j-np1][k-np2]!= INF ) {
                            dp[i][j][k] = min( dp[i][j][k], dp[i-np0][j-np1][k-np2]+1 );
                        }
                    }
                }
            }
        }
        printf("%d\n", dp[A][B][C]);
    }
    return 0;
}