/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const int maxn = 200000 + 5;
///空间开小可能会T
ll tree[maxn << 2];
void push_up(int node) {
    tree[node] = tree[node << 1] + tree[node << 1 | 1];
}

void build(int l, int r, int node) {
    if(l == r) {
        scanf("%lld", &tree[node]);
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, node << 1);
    build(mid + 1, r, node << 1 | 1);
    push_up(node);
}

void update(int l, int r, int L, int R, int node) {
    if(l == r) {
        tree[node] = sqrt(tree[node]);
        return;
    }
    ///如果区间内全为1，就不用往下递归了
    if(L <= l && r <= R && tree[node] == r - l + 1) return;
    int mid = (l + r) >> 1;
    if(L <= mid) update(l, mid, L, R, node << 1);
    if(mid + 1 <= R) update(mid + 1, r, L, R, node << 1 | 1);
    push_up(node);
}
ll query(int l, int r, int L, int R, int node) {
    if(L <= l && r <= R) return tree[node];
    int mid = (l + r) >> 1;
    ll ans = 0;
    if(L <= mid) ans += query(l, mid, L, R, node << 1);
    if(mid + 1 <= R) ans += query(mid + 1, r, L, R, node << 1 | 1);
    return ans;
}
int main() {
    int n, tt = 1;
    while(~ scanf("%d", &n)) {
        build(1, n, 1);
        int m; scanf("%d", &m);
        int v, a, b, x, y;
        printf("Case #%d:\n", tt ++);
        while(m --) {
            scanf("%d %d %d", &v, &x, &y);
            a = min(x, y), b = max(x, y);
            if(! v) update(1, n, a, b, 1);
            else printf("%lld\n", query(1, n, a, b, 1));
        }
        puts("");
    }
    return 0;
}
