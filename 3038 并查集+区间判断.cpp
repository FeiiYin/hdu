/*
 * @Samaritan_infi
 */
//#include<bits/stdc++.h>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 200000 + 5;
int par[maxn];
int val[maxn];

int find_par(int x ){
    if(par[x] == x )
        return x;
    else{
        int f = par[x];
        ///注意要先查找，再相加，从根往下加
        par[x] = find_par(par[x]);
        val[x] += val[f];
        return par[x];
    }
}

bool unite(int x, int y, int sum) {
    int a = find_par(x);
    int b = find_par(y);
    if(a == b) {
        if(val[x] + sum == val[y]) return true;
        return false;
    }
//    par[a] = b;
//    val[a] = -val[x] + sum + val[y];
    par[b] = a;
    val[b] = -val[y] + val[x] + sum;
    return true;
}

int main() {
    int n, m;
    while(~ scanf("%d %d", &n, &m)) {
        for(int i = 0; i <= n; i ++) par[i] = i, val[i] = 0;

        int a, b, v;
        int ans = 0;
        while(m --) {
            scanf("%d %d %d", &a, &b, &v);
            if(a > b) swap(a, b);
            if(! unite(a - 1, b, v)) ans ++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
