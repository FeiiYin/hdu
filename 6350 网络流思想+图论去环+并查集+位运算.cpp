/*
 * @Samaritan_infi
 */
/// 题意：给出一个任意两点之间不重复路径不超过的图，求sum（s^t^flow(s,t)); 
/// 做法：有一个结论，就是对于这样的图，那么一条边最多只会出现在一个环里面，那么只需要把环里面的最短边去掉，
/// 然后把环里剩余的边都加上这个边的权值，那么不会影响任意两点的最大流，对所有的环都这样操作，
/// 那么现在剩下的这个树上，任意两个节点的最大流，就是两点间边上最小的权值，那么把边的权值按照从大到小的顺序插入到图中，
/// 维护并查集，每次合并两个集合，nlogn复杂度。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;
vector< pair<int, int> > edge[N];

struct Edge {
    int u, v, flow;
    Edge() {}
    Edge(int x, int y, int z)
        : u(x), v(y), flow(z) {}
    bool operator < (const Edge & p) const {
        return flow > p.flow;
    }
};

vector<Edge> new_edge;

bool vis[N];
int visit_time[N], visit_number;
int father[N], father_flow[N];
void dfs(int now) {
    visit_time[now] = ++ visit_number;
    vis[now] = true;
    for(auto pr : edge[now]) {
        int to = pr.first;
        if(to == father[now] ||
           /// 代表第二条路径访问该结点，非环
           (vis[to] && visit_time[to] > visit_time[now]))
            continue;
        /// 环
        if(vis[to]) {
            int circle_min_flow = pr.second;
            int cur = now;
            while(cur != to) {
                circle_min_flow = min(circle_min_flow, father_flow[cur]);
                cur = father[cur];
            }
            bool flag = true;
            cur = now;
            if(pr.second == circle_min_flow) flag = false;
            else new_edge.emplace_back(Edge(now, to, pr.second + circle_min_flow));

            while(cur != to) {
                if(flag && father_flow[cur] == circle_min_flow) {
                    flag = false;
                    father_flow[cur] = -1;
                } else {
                    new_edge.emplace_back(Edge(father[cur], cur, father_flow[cur] + circle_min_flow));
                    father_flow[cur] = -1;
                }
                cur = father[cur];
            }
        }
        /// 路
        else {
            father[to] = now;
            father_flow[to] = pr.second;
            dfs(to);
        }
    }
}

void dislodge_circle(int n) {
    memset(vis, 0, sizeof(vis[0]) * (n + 2));
    memset(father_flow, -1, sizeof(int) * (n + 2));
    new_edge.clear();
    visit_number = 0;
    dfs(1);
    /// 非环的边还未加入
    for(int i = 1; i <= n; i ++) {
        if(father_flow[i] != -1)
            new_edge.emplace_back(Edge(father[i], i, father_flow[i]));
    }
    sort(new_edge.begin(), new_edge.end());
}

/// 并查集每一个集合中每一位的个数
int num[N][32];
int parent[N];
/// 并查集中以i为根的集合中的元素个数
/// 因为每次加入的是值最小的边，所以链接的两个并查集
/// 中的两边的所有元素的最大流都被更新为当前该最小的值
int set_cnt[N];

int find_par(int x) {
    if(parent[x] == x) return x;
    return parent[x] = find_par(parent[x]);
}

void cal_ans(int n) {
    for(int i = 1; i <= n; i ++)
        parent[i] = i, set_cnt[i] = 1;
    for(int i = 1; i <= n; i ++) {
        for(int j = 0; j < 31; j ++)
            num[i][j] = (i >> j) & 1;
    }

    unsigned long long ans = 0;
    for(Edge eg : new_edge) {
        int flow = eg.flow;
        int u_parent = find_par(eg.u), v_parent = find_par(eg.v);
        for(int i = 0; i < 31; i ++) {
            unsigned long long t = (flow>>i) & 1;
            /// 抑或时考虑每一位
            /// u 集合中第 i 位 1 的个数是 num[u][i]个
            /// 总数为 set_cnt[u]
            /// 第 i 位 0 的个数是 set_cnt[u] - num[u][i]个
            /// t ^ 1 ^ 1
            ans += (t << i) * num[u_parent][i] * num[v_parent][i];
            /// t ^ 1 ^ 0
            ans += ((t^1)<< i) * num[u_parent][i] * (set_cnt[v_parent] - num[v_parent][i]);
            /// t ^ 0 ^ 1
            ans += ((t^1)<< i) * (set_cnt[u_parent] - num[u_parent][i]) * num[v_parent][i];
            /// t ^ 0 ^ 0
            ans += (t<< i) * (set_cnt[u_parent] - num[u_parent][i]) * (set_cnt[v_parent] - num[v_parent][i]);
            /// 合并
            num[u_parent][i] += num[v_parent][i];
        }
        set_cnt[u_parent] += set_cnt[v_parent];
        parent[v_parent] = u_parent;
    }
    printf("%llu\n", ans);
}

int main() {
    int kase;
    scanf("%d", &kase);
    while(kase --) {
        int n, m;
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; i ++)
            edge[i].clear();
        int u, v, w;
        for(int i = 1; i <= m; i ++) {
            scanf("%d %d %d", &u, &v, &w);
            edge[u].emplace_back(make_pair(v, w));
            edge[v].emplace_back(make_pair(u, w));
        }
        dislodge_circle(n);
        cal_ans(n);
    }
    return 0;
}
