#include<bits/stdc++.h>
#define rson m+1,r,rt<<1|1
#define lson l,m,rt<<1
#define FIN freopen("input.txt","r",stdin);
using namespace std;
typedef unsigned long long ULL;
typedef long long LL;
const int  MX = 2e5 + 5;
typedef pair<int, int> PII;
int n, m, a[MX];
int ch[MX][2], pre[MX], clr[MX];
bool root[MX];
void init() {
    for (int i = 0; i <= n; i++) {
        ch[i][0] = ch[i][1] = clr[i] = 0;
        pre[i] = 0;
        root[i] = 1;
    }
}
void Rotate(int x) {
    int y = pre[x], kind = ch[y][1] == x;
    ch[y][kind] = ch[x][!kind];
    pre[ch[y][kind]] = y;
    pre[x] = pre[y];
    pre[y] = x;
    ch[x][!kind] = y;
    if (root[y]) root[y] = 0, root[x] = 1;
    else ch[pre[x]][ch[pre[x]][1] == y] = x;
}
int t;
void Splay(int x) {
    while (!root[x]) {
        int f = pre[x], ff = pre[f];
        if (!root[f]) {
            if ((ch[ff][1] == f) == (ch[f][1] == x)) Rotate(f);
            else Rotate(x);
        }
        Rotate(x);
    }
}
int Access(int x) {
    int y = 0;
    t = x;
    while (x) {
        Splay(x);
        root[ch[x][1]] = 1;     //在辅助树中切除右子树(曾经的偏爱子节点)
        root[ch[x][1] = y] = 0;
        x = pre[y = x];
    }
    return y;
}
 
int findroot(int x) {
    Access(x);
    Splay(x);
    while (ch[x][0]) x = ch[x][0];
    Splay(x);
    return x;
}
 
void cut(int v) {
    Access(v);
    Splay(v);
    pre[ch[v][0]] = pre[v];
    pre[v] = 0;
    root[ch[v][0]] = 1;
    ch[v][0] = 0;
}
void link(int u, int v) {
    Access(v);
    Splay(v);
    pre[v] = u;
}
void Link(int u, int v) {
    int rt = findroot(v);
    if (rt == v) clr[rt] = 0;
    else cut(v);
    if (clr[rt] && findroot(clr[rt]) != rt) {
        link(clr[rt], rt);
        clr[rt] = 0;
    }
    if(u==0) return;
    if (findroot(u) == v) clr[v] = u;
    else link(u, v);
}
int main() {
    //freopen("in.txt", "r", stdin);
    while (~scanf("%d%d", &n, &m)) {
        init();
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++) if (a[i]) Link(a[i], i);
        for (int i = 1; i <= m; i++) {
            int op, x, y;
            scanf("%d", &op);
            if (op == 1) {
                scanf("%d%d", &x, &y);
                Link(y, x);
            } else {
                scanf("%d", &x);
                x = findroot(x);
                printf("%d\n", clr[x] ? -1 : x);
            }
        }
    }
    return 0;
}
