/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 5;

inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;if(ch==EOF) return x;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int a[N];
ll sum[N << 2];
int mx[N << 2], se[N << 2], max_count[N << 2];

inline void push_up(int node) {
    sum[node] = sum[node << 1] + sum[node << 1 | 1];
    mx[node] = max(mx[node << 1], mx[node << 1 | 1]);
    se[node]=max(se[node << 1], se[node << 1 | 1]);
    max_count[node] = 0;
    if(mx[node << 1] != mx[node << 1 | 1])
        se[node]=max(se[node], min(mx[node << 1], mx[node << 1 | 1]));
    if(mx[node] == mx[node << 1])
        max_count[node] += max_count[node << 1];
    if(mx[node]==mx[node << 1 | 1])
        max_count[node]+=max_count[node << 1 | 1];
}

inline void dec_tag(int node, int value){
    if(value >= mx[node]) return;

    sum[node] += 1LL * (value - mx[node]) * max_count[node];
    mx[node] = value;
}
inline void push_down(int node){
    dec_tag(node << 1, mx[node]);
    dec_tag(node << 1 | 1, mx[node]);
}
void build(int node, int l, int r){
    if(l == r){
        sum[node] = mx[node] = a[l];
        max_count[node] = 1;
        se[node]=-1;
        return;
    }
    int mid = (l + r) >> 1;
    build(node << 1, l, mid);
    build(node << 1 | 1, mid + 1, r);
    push_up(node);
}

void change(int node, int l, int r, int L, int R, int value){
    if(r < L || l > R) return;
    if(value >= mx[node]) return;
    if(L <= l && r <= R && value > se[node]){
        dec_tag(node, value);
        return;
    }
    push_down(node);

    int mid = (l + r) >> 1;
    if(L <= mid) change(node << 1, l, mid, L, R, value);
    if(R > mid) change(node << 1 | 1, mid + 1, r, L, R, value);
    push_up(node);
}

int query_max(int node, int l, int r, int L, int R) {
    if(r < L || l > R) return -1;
    if(L <= l && r <= R)
        return mx[node];
    push_down(node);
    int mid = (l + r) >> 1;
    int ans = 0;
    if(L <= mid) ans = max(ans, query_max(node << 1, l, mid, L, R));
    if(R > mid)  ans = max(ans, query_max(node << 1 | 1, mid+1, r, L, R));
    return ans;
}

ll query_sum(int node, int l, int r, int L, int R) {
    if(r < L || l  > R) return 0;
    if(L <= l && r <= R) return sum[node];
    push_down(node);
    int mid = (l + r) >> 1;
    ll ans = 0;
    if(L <= mid) ans += query_sum(node << 1, l, mid, L, R);
    if(R > mid) ans += query_sum(node << 1 | 1, mid+1, r, L, R);
    return ans;
}

inline void work(){
    int n = read(), m = read();
    for(int i = 1; i <= n; i ++)
        a[i] = read();
    build(1, 1, n);
    for(int i = 1, opt, x, y, z; i <= m; i ++){
        opt = read(); x = read(); y = read();
        if(opt == 0)    z = read(), change(1, 1, n, x, y, z);
        else if(opt==1) printf("%d\n", query_max(1, 1, n, x, y));
        else            printf("%lld\n", query_sum(1, 1, n, x, y));
    }
}
int main(){
    for(int kase=read(); kase --;) work();
    return 0;
}
