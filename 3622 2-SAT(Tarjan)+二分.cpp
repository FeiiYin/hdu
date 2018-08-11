/*
 * @Samaritan_infi
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

pair<int, int> a[N], b[N];
#define sqr(x) (x)*(x)
const double eps = 1e-4;
inline double cal_dis(int a, int b, int c, int d) {
    return sqrt(sqr(a - b) + sqr(c - d));
}

bool solve(int n, double r) {
    init(n * 2);
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j < i; j ++) {
            if(cal_dis(a[i].first, a[j].first, a[i].second, a[j].second) < 2 * r) {
                add_edge(i, j + n);
                add_edge(j, i + n);
            }
            if(cal_dis(a[i].first, b[j].first, a[i].second, b[j].second) < 2 * r) {
                add_edge(i, j);
                add_edge(j + n, i + n);
            }
            if(cal_dis(b[i].first, a[j].first, b[i].second, a[j].second) < 2 * r) {
                add_edge(i + n, j + n);
                add_edge(j, i);
            }
            if(cal_dis(b[i].first, b[j].first, b[i].second, b[j].second) < 2 * r) {
                add_edge(i + n, j);
                add_edge(j + n, i);
            }
        }

    for(int i = 1; i <= n * 2; i ++)
        if(! dfn[i]) tarjan(i);

    for(int i = 1; i <= n; i ++) {
        if(belong[i] == belong[n + i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, m;
    while(~ scanf("%d", &n)) {
        for(int i = 1; i <= n; i ++)
            scanf("%d %d %d %d", &a[i].first, &a[i].second,
                   &b[i].first, &b[i].second);

        double l = 0.0, r = 40000.0;
        while(fabs(l - r) > eps) {
            double mid = (l + r) / 2;
            if(solve(n, mid)) l = mid;
            else r = mid;
        }
        if(solve(n, r)) printf("%.2f\n", r);
        else printf("%.2f\n", l);
    }
    return 0;
}
