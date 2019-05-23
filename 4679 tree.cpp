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

struct node {
    int fi, w, id;
    node () {}
    node (int _y, int _w, int _id)
    : fi(_y), w(_w), id(_id) {}
};

vector <node> edge[N];
int dis[N];
int rtx, rty, dep_max, diameter;
void radius_dfs1 (int x, int pre, int dep) {
    for (node e : edge[x]) if (e.fi != pre) {
        radius_dfs1(e.fi, x, dep + 1);
        if (dep + 1 > dep_max) {
            dep_max = dep + 1;
            rtx = e.fi;
        }
    }
}
int dx[N];
void radius_dfs2 (int x, int pre) {
    for (node e : edge[x]) if (e.fi != pre) {
        dx[e.fi] = dx[x] + 1;
        radius_dfs2(e.fi, x);
    }
}
int dy[N];
void radius_dfs_dis (int x, int pre) {
    for (node e : edge[x]) if (e.fi != pre) {
        dy[e.fi] = dy[x] + 1;
        radius_dfs_dis(e.fi, x);
    }
}

int ans = INF, ID = INF;
void dfs (int x, int pre) {
    for (node e : edge[x]) if (e.fi != pre) {
        int y = e.fi, tmp = INF;
        if (dx[x] + dy[y] + 1 == diameter) {
            tmp = max(dx[x], dy[y]) * e.w;
        }
        else {
            tmp = diameter * e.w;
        }
        if (tmp < ans) {
            ans = tmp;
            ID = e.id;
        } else if (tmp == ans) {
            ID = min(ID, e.id);
        }
        dfs(e.fi, x);
    }
}

int main () {
    int kase;
    int tt = 1;
    scanf("%d", &kase);
    while (kase--) {
        int n;
        scanf("%d", &n);
        /// initialize
        for (int i = 1; i <= n; ++i)
            edge[i].clear();
        int u, v, w;
        for (int i = 1; i < n; ++i) {
            scanf("%d %d %d", &u, &v, &w);
            edge[u].push_back(node(v, w, i));
            edge[v].push_back(node(u, w, i));
        }
        /// radius
        dep_max = 1;
        radius_dfs1(1, -1, 0);
        dx[rtx] = 0;
        radius_dfs2(rtx, -1);
        diameter = 0;
        for (int i = 1; i <= n; ++i) {
            if  (dx[i] > diameter) {
                diameter = dx[i];
                rty = i;
            }
        }
        dy[rty] = 0;
        radius_dfs_dis(rty, -1);
        /// work
        /// note that to avoid search from different kinds of roads
        /// the starting point should be rtx or rty, then dx and dy should be matched
        ans = ID = INF;
        dfs(rtx, -1);
        printf("Case #%d: %d\n", tt++, ID);
    }
    return 0;
}
