/*
 * @Samaritan_infi
 */
/// 垃圾读入优化以后不用了
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 4e6 + 5;
const int inf = 0x3f3f3f3f;

struct node {
    int id, u, v, cost;
    node(int _id=0,int _u=0,int _v=0,int _cost=0):id(_id),u(_u),v(_v),cost(_cost){}
};

queue<int> que;
vector<node> edge[N];

int n, m, k;
int dis[N], vis[N];

inline void add_edge(int id, int u, int v, int w) {
    edge[u].push_back(node(id, u, v, w));
    edge[v].push_back(node(id, v, u, w));
}

void dfs(int x, int id, int deep, int father) {
    if(! vis[x]) {
        que.push(x); dis[x] = deep; vis[x] = 1;
    }
    if(dis[n] != inf) return;
    for(int i = 0; i < edge[x].size(); i++) {
        node & k = edge[x][i];
        if(k.v == father || k.id) continue;
        if(k.cost == id) {
            k.id = 1;
            dfs(k.v, id, deep, x);
            if(dis[n] != inf) return;
        }
    }
}


int main() {
    while(~ scanf("%d %d", &n, &m)) {
        memset(dis, inf, sizeof (int) * (n + 2));
        memset(vis, 0, sizeof(vis[0]) * (n + 2));
        for(int i = 0; i <= n; i++) {
            edge[i].clear();
        }
        while(! que.empty()) que.pop();

        int u, v, val;
        while(m --) {
            scanf("%d %d %d", &u, &v, &val);
            if(u == v) continue;
            add_edge(0, u, v, val);
        }
        dis[1] = 0; que.push(1); vis[1] = 1;
        while(! que.empty()) {
            int now = que.front(); que.pop();
            for(int i = 0; i < edge[now].size(); i++) {
                node & j = edge[now][i];
                if(j.id) continue;
                j.id = 1;
                dfs(j.v, j.cost, dis[now] + 1, -1);
                if(dis[n] != inf) break;
            }
            if(dis[n] != inf) break;
        }
        if(dis[n] != inf) printf("%d\n", dis[n]);
        else puts("-1");
    }
    return 0;
}
