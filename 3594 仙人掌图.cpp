/*
 * @Samaritan_infi
 */
/// 仙人掌图指 只有一个强连通分量并且每一条边只属于一个环中

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e4 + 10;
const int M = 5e4 + 10;

struct Edge {
    int to, next;
    Edge() {}
    Edge(int _t, int _n) : to(_t), next(_n) {}
} edge[M];

int head[N], vis[N], belong[N], in[N];
int low[N], dfn[N], Stack[N], father[N];
int edge_num;

void add_edge(int u, int v) {
    edge[edge_num] = Edge(v, head[u]);
    head[u] = edge_num++;
}

int num, top, scc_num;
bool flag;
void init(int n) {
    memset(dfn, 0, sizeof (int) * (n + 2));
    memset(head, -1, sizeof (int) * (n + 2));
    memset(vis, 0, sizeof (int) * (n + 2));
    memset(in, 0, sizeof (int) * (n + 2));
    edge_num = 1;
    scc_num = top = num = 0;
}

void dfs(int u, int v) {
    while(father[u] != v) {
        in[u] ++;
        if(in[u] > 1) {
            flag = false;
            return;
        }
        u = father[u];
    }
}

void targan(int u) {
    if(! flag) return;
    low[u] = dfn[u] = ++ num;
    Stack[top ++] = u;
    vis[u] = 1;
    for(int i = head[u]; ~ i; i = edge[i].next) {
        int v = edge[i].to;
        if(! dfn[v]) {
            father[v] = u;
            targan(v);
            if(low[v] < low[u]) low[u] = low[v];
        } else if(vis[v] && dfn[v] < low[u]) {
            dfs(u, v);
            if(! flag) return;
            low[u] = dfn[v];
        }
    }

    if(dfn[u] == low[u]) {
        scc_num ++;
        if(scc_num > 1) {
            flag = false;
            return;
        }
        int x;
        do {
            x = Stack[-- top];
            belong[x] = scc_num;
            vis[x] = 0;
        } while(x != u);
    }
}

int main() {
    int kase;
    scanf("%d", &kase);
    while(kase --) {
        int n;
        scanf("%d", &n);
        init(n);
        flag = true;
        int u, v;
        while(~ scanf("%d %d", &u, &v), u + v) {
            u ++, v ++;
            /// 去重边
            for(int i = head[u]; ~ i; i = edge[i].next)
                if(edge[i].to == v) flag = false;
            add_edge(u, v);
        }
        for(int i = 1; i <= n && flag; i ++)
            if(! dfn[i]) targan(i);

        if(flag) printf("YES\n");
        else puts("NO");
    }
}
