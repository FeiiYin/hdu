/*
 * @Samaritan_infi
 * 当一条路径的两个顶点在一条边的两侧时，计算贡献值，
 * 对于一条路径，2 * son[i] * (n - son[i]) * (n - 2)! * (n - 1) (其余点排列组合 * 路径数)
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define fi first
#define se second
const int N = 1e5 + 5;
const int mod = 1e9 + 7;
vector< pair<int, int> > e[N];
int sz[N], fa[N];
int n;
ll ans = 0;
ll f[N];
void init () {
    f[0] = 1ll;
    for (int i = 1; i < N; i ++) f[i] = f[i-1]*i%mod;
}

ll calc(int row, int col) {
    return 2ll*row%mod*col%mod*f[row+col-1]%mod;
}
int dfs1(int u, int pa) {
    int sub = 0;
    for(auto x : e[u]) {
        int v = x.fi;
        if(v != pa) sub += dfs1(v, fa[v]=u);
    }
    sz[u] = sub+1;
    return sz[u];
}
void dfs2(int u) {
    for(auto x : e[u]) {
        int v = x.fi, w = x.se;
        if(v == fa[u]) continue;
        int row = sz[v], col = n-sz[v];
        ans = (ans + calc(row,col)*(ll)w%mod) % mod;
        dfs2(v);
        //cout<<u<<"-->"<<v<<" "<<calc(row,col)<<endl;
    }
}
int main() {
    init();
    while(~ scanf("%d", &n)) {
        for (int i = 1; i <= n; i ++) e[i].clear(), fa[i] = i;
        for (int i = 1; i < n; i ++) {
            int u, v, w; scanf("%d%d%d",&u,&v,&w);
            e[u].push_back(make_pair(v, w));
            e[v].push_back(make_pair(u, w));
        }
        ans = 0;
        dfs1(1, 1);
        //rep(i,1,n) cout<<sz[i]<<' ';cout<<endl;
        dfs2(1);
        cout<<ans<<endl;
    }
    return 0;
}
