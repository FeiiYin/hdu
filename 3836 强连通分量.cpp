/*
 * @Samaritan_infi
 */
/// 联通块为1 时不需要加边， 否则加 max(num(in[i] = 0), num(out[i] = 0));
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e4 + 5;

vector<int> edge[N];
vector<int> reverse_edge[N];
vector<int> vs;
/// 记录属于第几个联通块
int save[N];
bool vis[N];

void add_edge(int l, int r) {
    edge[l].emplace_back(r);
    reverse_edge[r].emplace_back(l);
}

void dfs(int now) {
    vis[now] = true;
    for(int to : edge[now])
        if(! vis[to])
            dfs(to);
    vs.emplace_back(now);
}

void rdfs(int now, int scc_num) {
    vis[now] = true;
    save[now] = scc_num;
    for(int to : reverse_edge[now])
        if(! vis[to])
            rdfs(to, scc_num);
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

int in_degree[N];
int out_degree[N];

int work(int n, int scc_num) {
    for(int i = 1; i <= n; i ++) {
        for(int to : edge[i])
            if(save[i] != save[to]) {
                out_degree[ save[i] ] ++;
                in_degree[ save[to] ] ++;
            }
    }
    int in = 0, out = 0;
    for(int i = 1; i <= scc_num; i ++) {
        if(! in_degree[i]) in ++;
        if(! out_degree[i]) out ++;
    }
    return max(in, out);
}

int main() {
    int n, m;
    while(~ scanf("%d %d", &n, &m)) {
        for(int i = 0; i <= n; i ++) {
            edge[i].clear();
            reverse_edge[i].clear();
            save[i] = 0;
            in_degree[i] = out_degree[i] = 0;
        }
        int l, r;
        for(int i = 0; i < m; i ++) {
            scanf("%d %d", &l, &r);
            add_edge(r, l);
        }

        int scc_num = scc(n);

        if(scc_num == 1) printf("0\n");
        else printf("%d\n", work(n, scc_num));
    }
    return 0;
}
