#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

const int maxn = 20;
const int KIND = 3;
const int INF = 0x3fffffff;
map<pair<pair<int,int>,int>, int> ans;
int num_of_block[maxn][KIND];
int num_of_target[KIND];
int cnt[maxn];
int n;
const int & A = num_of_target[0];
const int & B = num_of_target[1];
const int & C = num_of_target[2];
int check[maxn][KIND];

int my_ceil(int aim, int temp) {
    if( temp == 0 ) {
        return maxn;
    }
    int ret = aim/temp + (aim%temp!=0);
    return ret;
}

void build_my_cnt() {
    for( int i = 0; i < n; i++ ) {
        int temp0 = num_of_block[i][0];
        int temp1 = num_of_block[i][1];
        int temp2 = num_of_block[i][2];
        if( temp0 == 0 ) check[i][0] = 1;
        if( temp1 == 0 ) check[i][1] = 1;
        if( temp2 == 0 ) check[i][2] = 1;
        int ans = max({my_ceil(A,temp0),my_ceil(B, temp1),my_ceil(C, temp2)});
        
        cnt[i] = ans;
    }
}

int ok( int p, int i, int j, int k) {
    int & t0 = check[p][0];
    int & t1 = check[p][1];
    int & t2 = check[p][2];
    if( t0 != 1 && t1 != 1 && t2 != 1 ) return i <= 0 && j <= 0 && k <= 0;
    if( t0 == 1 && t1 != 1 && t2 != 1 ) return j <= 0 && k <= 0;
    if( t1 == 1 && t0 != 1 && t2 != 1 ) return i <= 0 && k <= 0;
    if( t2 == 1 && t0 != 1 && t1 != 1 ) return i <= 0 && j <= 0;
    if( t0 == 1 && t1 == 1 && t2 != 1 ) return k <= 0;
    if( t0 == 1 && t2 == 1 && t1 != 1 ) return j <= 0;
    if( t1 == 1 && t2 == 1 && t0 != 1 ) return i <= 0;
    else {
        cout << "The component of a block can not be all zero !!!" << endl;
        cout << "Please input again!!!" << endl;
        exit(-1);
    }
}

int dp(int p, int i, int j, int k, int m) {
    int & a = ans[make_pair(make_pair(i, j),k)];
    
//    if(i <= 0 && j <= 0 && k <= 0) return 0;
    if(ok(p, i, j, k)) return 0;
    const int mp0 = i-num_of_block[p][0];
    const int mp1 = j-num_of_block[p][1];
    const int mp2 = k-num_of_block[p][2];
    return a = min( a, dp(p, mp0, mp1, mp2, m+1)+1 );
}


int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        // Initialization
        for( int i = -maxn; i < maxn; i++ ) {
            for( int j = -maxn; j < maxn; j++ ) {
                for( int k = -maxn; k < maxn; k++ ) {
                    ans[make_pair(make_pair(i, j),k)] = INF;
                }
            }
        }
        
        for( int i = 0; i < KIND; i++ ) {
            scanf("%d", &num_of_target[i]);
        }
        scanf("%d", &n);
        for( int i = 0; i < n; i++ ) {
            for( int j = 0; j < KIND; j++ ) {
                scanf("%d", &num_of_block[i][j]);
            }
        }
        build_my_cnt();
        for( int p = 0; p < n; p++ ) {
            dp(p, A, B, C, 0);
        }
        
        
        cout << ans[make_pair(make_pair(A, B), C)] << endl;
        
    }
    return 0;
}