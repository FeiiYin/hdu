/*
 * @Samaritan_infi
 */

/// 最大权闭合图
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}

const int maxn = 1005, maxm = 2e5 + 5;
const int inf = 2147483640;

struct Edge {
    int v, next, u, cap;
}edge[maxm << 1];
int k, head[maxn], dist[maxn], que[maxn], n, m, st, ed, current[maxn];

void init() {
    memset(head, -1, sizeof head);
    k = -1; /// very important cannot change
}

void add_edge(int u, int v, int cap) {
    edge[++k].u = u;
    edge[k].v = v;
    edge[k].cap = cap;
    edge[k].next = head[u];
    head[u] = k;
    edge[++k].u = v;
    edge[k].v = u;
    edge[k].cap = 0;
    edge[k].next = head[v];
    head[v] = k;
}
bool bfs() {
    int fro, top;
    memset(dist, 0, sizeof(dist));
    dist[st] = 1;
    fro = top =1;
    que[fro] = st;
    while(fro <= top)
    {
        int p = que[fro++];
        for(int kk = head[p]; ~kk; kk = edge[kk].next)
        {
            int v = edge[kk].v, cap = edge[kk].cap;
            if(cap && !dist[v])
            {
                dist[v] = dist[p] + 1;
                que[++top] = v;
                if(v == ed) return 1;
            }
        }
    }
    return 0;
}
int dfs(int u, int maxflow) {
    if(u == ed || maxflow == 0) return maxflow;
    int t = 0;
    for(int& kk = current[u]; ~kk; kk = edge[kk].next)
    {
        int v =  edge[kk].v, cap = edge[kk].cap;
        if(cap && dist[v] ==  dist[u] + 1)
        {
            int f = dfs(v, min(cap, maxflow - t));
            t += f;
            edge[kk].cap -= f;
            edge[kk ^ 1].cap += f;
            if(t == maxflow) return t;
        }
    }
    if(t == 0) dist[u] = -1;
    return t;
}
ll dinic() {
    ll maxnflow = 0, t;
    while(bfs()) {
        for(int i = 0; i <= ed; ++i) current[i] = head[i];
        while(t = dfs(st, inf))
            maxnflow += t;
    }
    return maxnflow;
}

const int block = 1000;

int main() {
    int kase = read();
    int tt = 1;
    while(kase --) {
        int n = read(), m = read();
        init();
        st = 0, ed = n - 1;
        int x, l, r, cap, f;
        while(m --) {
            l = read(), r = read(), cap = read(), f = read();
            add_edge(l, r, cap*block+1);
            if(f) add_edge(r, l, cap*block+1);
        }

        ll sum = dinic();

        printf("Case %d: %d\n", tt ++, sum % block);
    }
    return 0;
}
