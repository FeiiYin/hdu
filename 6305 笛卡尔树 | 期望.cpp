#include<bits/stdc++.h>
using namespace std;
 
typedef long long LL;
 
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MX = 1e6 + 5;
 
struct node {
    int val, sz;
    int l, r, pre;
} t[MX];
stack<int>st;
void init (int n) {
    for (int i = 0; i <= n; i++) t[i].l = t[i].r = t[i].pre = t[i].sz = 0;
    t[0].val = INF;
    while (!st.empty() ) st.pop();
    st.push (0);
}
void build (int n) { //从右端插入
    for (int i = 1; i <= n; i++) {
        while (!st.empty() && t[st.top()].val < t[i].val) st.pop();
        int pre = st.top();
        t[i].pre = pre;
        t[i].l = t[pre].r;
        t[t[pre].r].pre = i;
        t[pre].r = i;
        st.push (i);
    }
}
void dfs (int u) {
    if (u == 0) return;
    t[u].sz = 1;
    dfs (t[u].l);
    dfs (t[u].r);
    t[u].sz += t[t[u].l].sz + t[t[u].r].sz;
}
 
LL inv[MX];
void init() {
    inv[1] = 1;
    for (int i = 2; i < MX; i++) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
}
 
int main() {
    //freopen ("in.txt", "r", stdin);
    int T, n; cin >> T;
    init();
    while (T--) {
        scanf ("%d", &n);
        init (n);
        for (int i = 1; i <= n; i++) scanf ("%d", &t[i].val);
        build (n);
        dfs (t[0].r);
 
        LL ans = n * inv[2] % mod;
        for (int i = 1; i <= n; i++) ans = ans * inv[t[i].sz] % mod;
        printf ("%lld\n", ans);
    }
    return 0;
}
