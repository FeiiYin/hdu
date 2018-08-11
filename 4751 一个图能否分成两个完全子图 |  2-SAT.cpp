/*
 * @Samaritan_infi
 * 4751 一个图能否分成两个完全子图 |  2-SAT.cpp
 */
/// tarjan比双dfs快
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

int head[N], vis[N], belong[N];
int low[N], dfn[N], Stack[N];
int edge_num;

void add_edge(int u, int v) {
    edge[edge_num] = Edge(v, head[u]);
    head[u] = edge_num++;
}

int stack_num, top, scc_num;
void init(int n) {
    memset(dfn, 0, sizeof (int) * (n + 2));
    memset(head, -1, sizeof (int) * (n + 2));
    memset(vis, 0, sizeof (int) * (n + 2));
    edge_num = 1;
    scc_num = top = stack_num = 0;
}



void tarjan(int u) {
    low[u] = dfn[u] = ++ stack_num;
    Stack[top ++] = u;
    vis[u] = 1;
    for(int i = head[u]; ~ i; i = edge[i].next) {
        int v = edge[i].to;
        if(! dfn[v]) {
            tarjan(v);
            if(low[v] < low[u]) low[u] = low[v];
        } else if(vis[v] && dfn[v] < low[u]) {
            low[u] = dfn [v];
        }
    }

    if(dfn[u] == low[u]) {
        scc_num ++;
        int x;
        do {
            x = Stack[-- top];
            belong[x] = scc_num;
            vis[x] = 0;
        } while(x != u);
    }
}

bool solve(int n) {
    for(int i = 1; i <= n * 2; i ++)
        if(! dfn[i]) tarjan(i);

    for(int i = 1; i <= n; i ++) {
        if(belong[i] == belong[n + i]) {
            return false;
        }
    }
    return true;
}

bool pic[105][105];

int main() {
    int n, m;
    while(~ scanf("%d", &n)) {
        init(n * 2);
        memset(pic, false, sizeof pic);
        for(int i = 1, x; i <= n; i ++) {
            while(~ scanf("%d", &x) && x)
                pic[i][x] = true;
        }
        for(int i = 1; i <= n; i ++) {
            for(int j = 1; j < i; j ++) {
                if(pic[i][j] && pic[j][i]) ;
                else {
                    add_edge(i, j + n);
                    add_edge(j, i + n);
                    add_edge(i + n, j);
                    add_edge(j + n, i);
                }
            }
        }

        if(solve(n)) puts("YES");
        else puts("NO");
    }
    return 0;
}
