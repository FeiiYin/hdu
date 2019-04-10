/**
`* @Samaritan
 */
/// 题目求 一颗树上 到每一个点的最远距离
/// dfs第一遍搜每一个点子树的最大深度，次大深度与对应孩子
/// dfs第二遍更新父亲 非经过自己 的最大深度， 如果自己是最大深度即父亲的次大深度，如果自己不是即父亲的最大深度
/// 二者取max 这样是O(n)
/// 直径做的话搜到链的最近距离，好像复杂度就高了，但是不太会算 大概在 O(n)-O(n2)之间
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define PII pair<int, int>
#define mp make_pair
#define pb push_back
#define INF 0x3f3f3f3f
#define fi  first
#define se second

const int N = 1e4 + 5;

struct Edge {
    int u, v, next;
    LL val;
    Edge () {}
    Edge (int _u, int _v, int _next, LL _val)
    : u(_u), v(_v), next(_next), val(_val) {}
    void show () {
        printf("u: %d v: %d next: %d val: %lld\n", u, v, next, val);
    }
    bool operator < (const Edge &k) const {
        return val < k.val;
    }
};
Edge edge[N << 1];
int head[N], pos;
inline void add_edge (int u, int v, LL val) {
    edge[++pos] = Edge(u, v, head[u], val);
    head[u] = pos;
}

LL dp[N][3];
int son[N][3];
/// dp[x][0] x 节点子树的最远点距离
/// dp[x][1] x 节点子树的次远点距离
/// dp[x][2] x 节点的父亲部的最远点距离
/// son 为对应节点
void work_dp (int x, int par) {
    for (int i = head[x]; i != 0; i = edge[i].next) {
        int to = edge[i].v;
        if (to == par) continue;
        // edge[i].show();
        work_dp(to, x);
        /// 更新 当前节点的 最远距离 = 这颗子树的最远距离 + 孩子到当前节点的距离
        if (dp[x][0] < dp[to][0] + edge[i].val) {
            son[x][1] = son[x][0];
            son[x][0] = to;
            dp[x][1] = dp[x][0];
            dp[x][0] = dp[to][0] + edge[i].val;
        }
        else if (dp[x][1] < dp[to][0] + edge[i].val) {
            dp[x][1] = dp[to][0] + edge[i].val;
            son[x][1] = to;
        }
    }
}

void dfs (int x, int par) {
    for (int i = head[x]; i != 0; i = edge[i].next) {
        int to = edge[i].v;
        if (to == par) continue;
        /// 如果 最深不经过这个孩子，那么孩子的父亲最远肯定不经过这个孩子
        if (son[x][0] != to)
            dp[to][2] = max(dp[x][0], dp[x][2]) + edge[i].val;
        /// 如果 最深经过这个孩子，那么次深一定不经过它
        else
            dp[to][2] = max(dp[x][1], dp[x][2]) + edge[i].val;
        dfs(to, x);
    }
}

int main () {
    int n; while (~ scanf("%d", &n)) {
        memset(head, 0, sizeof (head[0]) * (n + 3));
        pos = 0;

        int to; LL val;
        for (int i = 2; i <= n; ++i) {
            scanf("%d %lld", &to, &val);
            add_edge(i, to, val);
            add_edge(to, i, val);
        }
        memset(dp, 0, sizeof dp);
        memset(son, 0, sizeof son);
        /// root = 1
        work_dp(1, 0);

//        for (int i = 1; i <= n; ++i) {
//            for (int j = 0; j <3; ++j)
//                cout << dp[i][j] <<" ";
//            cout << endl;
//        }

        dp[1][2] = dp[1][1];
        dfs(1, 0);
        for (int i = 1; i <= n; ++i)
            printf("%lld\n", max(dp[i][0], dp[i][2]));
    }
    return 0;
}
