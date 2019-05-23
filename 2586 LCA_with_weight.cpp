/*
 * @Samaritan_infi
 */
/// 最大团大小，搜索+dp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;
#define PII pair<int, int>
#define fi first
#define se second
#define pb push_back

vector <PII> edge[N];

int par[N][21];
int deep[N], dis[N];
void dfs (int x, int pre) {
    par[x][0] = pre;
    for (PII now : edge[x]) if (now.fi != pre) {
        deep[now.fi] = deep[x] + 1;
        dis[now.fi] = dis[x] + now.se;
        dfs(now.fi, x);
    }
}

void init_lca (int n) {
    dfs(1, 0);

    for (int i = 1; i <= 20; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (par[j][i-1])
                par[j][i] = par[ par[j][i-1] ][i-1];
        }
    }
}

int LCA (int u, int v) {
    if (deep[u] > deep[v])
        swap(u, v);
    /// change deep
    for (int i = 0; i <= 20; ++i) {
        if ((deep[v] - deep[u]) & (1 << i)) {
            v = par[v][i];
        }
    }
    if (u == v) return u;

    /// dep 2^20 is enough
    for (int i = 20; i >= 0; --i)
        if (par[u][i] != par[v][i]){
            u = par[u][i];
            v = par[v][i];
        }
    /// note here
    return par[u][0];
}

int main () {
    int kase;
    scanf("%d", &kase);
    while (kase--) {
        int n, query;
        scanf("%d %d", &n, &query);
        int u, v, w;
        for (int i = 1; i < n; ++i) {
            scanf("%d %d %d", &u, &v, &w);
            edge[u].pb({v, w});
            edge[v].pb({u, w});
        }

        init_lca(n);

        while (query--) {
            scanf("%d %d", &u, &v);
            int lca = LCA(u, v);
//            printf("LCA: %d\n", lca);
            printf("%d\n", dis[u] + dis[v] - 2*dis[lca]);
        }
    }
    return 0;
}
