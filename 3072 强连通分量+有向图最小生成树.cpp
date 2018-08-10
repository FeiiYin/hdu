/*
 * @Samaritan_infi
 */
/// 缩点后为DAG
/// DAG 有向图的最小生成树 贪心选择每个顶点入边值最小即可

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5e4 + 5;
const int inf = 0x3f3f3f3f;


vector< pair<int, int> > edge[N];
vector< pair<int, int> > reverse_edge[N];
vector<int> vs;
/// 记录属于第几个联通块
int save[N];
bool vis[N];

void add_edge(int l, int r, int val) {
    edge[l].emplace_back(make_pair(r, val));
    reverse_edge[r].emplace_back(make_pair(l, val));
}

void dfs(int now) {
    vis[now] = true;
    for(auto t : edge[now]) {
        int to = t.first;
        if(! vis[to])
            dfs(to);
    }
    vs.emplace_back(now);
}

void rdfs(int now, int scc_num) {
    vis[now] = true;
    save[now] = scc_num;
    for(auto t : reverse_edge[now]) {
        int to = t.first;
        if(! vis[to])
            rdfs(to, scc_num);
    }
}

int scc(int n) {
    memset(vis, 0, sizeof vis);
    vs.clear();
    for(int i = 1; i <= n; i ++)
        if(! vis[i]) dfs(i);
    memset(vis, 0, sizeof vis);
    int scc_num = 0;
    for(int i = vs.size() - 1; i >= 0; i --)
        if(! vis[ vs[i] ])
            rdfs(vs[i], ++ scc_num);
    return scc_num;
}


int cost[N];

int main() {
    int n, m;
    while(~ scanf("%d %d", &n, &m)) {
        for(int i = 0; i <= n; i ++) {
            edge[i].clear();
            reverse_edge[i].clear();
            save[i] = 0;
        }
        int l, r, v;
        for(int i = 0; i < m; i ++) {
            scanf("%d %d %d", &l, &r, &v);
            l ++, r ++;
            add_edge(l, r, v);
        }

        int scc_num = scc(n);

        if(scc_num == 1) {
            printf("0\n");
            continue;
        }

        memset(cost, inf, sizeof(int) * (scc_num + 2));

        int to, val;
        for(int i = 1; i <= n; i ++)
            for(auto p : edge[i]) {
                to = p.first;
                val = p.second;
                if(save[i] != save[to]) {
                    cost[ save[to] ] = min(cost[ save[to] ], val);
                }
            }
        int ans = 0;
        for(int i = 1; i <= scc_num; i ++)
            ans += cost[i] == inf ? 0 : cost[i];
        printf("%d\n", ans);
    }
    return 0;
}
