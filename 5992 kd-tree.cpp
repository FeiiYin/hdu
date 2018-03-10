//k-d tree 
#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <cmath>
#include <algorithm>
#include <stack>
#pragma comment(linker, "/STACK:102400000,102400000")
#define Clear(x,y) memset (x,y,sizeof(x))
#define Close() ios::sync_with_stdio(0)
#define Open() freopen ("more.in", "r", stdin)
#define get_min(a,b) a = min (a, b)
#define get_max(a,b) a = max (a, b);
#define fi first
#define se second
#define pii pair<int, int>
#define pli pair<long long, int>
#define pll pair<long long, long long>
#define pb push_back
#define pl c<<1
#define pr (c<<1)|1
#define lson tree[c].l,tree[c].mid,pl
#define rson tree[c].mid+1,tree[c].r,pr
#define mod 1000000007
template <class T>
inline bool scan (T &ret) {
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0; //EOF
    while (c != '-' && (c < '0' || c > '9') ) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}
using namespace std;
#define maxn 200005

struct node {
    long long d[3];
    int l, r, id;//节点的点的坐标 左右孩子
    long long Max[3], Min[3];//节点中点x的最值 y的最值
}tree[maxn<<1], tmp;
int n, m;
int root, cmp_d;
struct Point {
    long long x, y, c;
    int id;
}p1[maxn], p2[maxn], pre[maxn];

bool cmp (const node &a, const node &b) {
    for (int i = 0; i < 3; i++) if (a.d[i] != b.d[i]) return a.d[i] < b.d[i];
    return a.id < b.id;
}

void push_up (int p, int pp) {
    for (int i = 0; i < 3; i++) {
        get_min (tree[p].Min[i], tree[pp].Min[i]);
        get_max (tree[p].Max[i], tree[pp].Max[i]);
    }
}

int build_tree (int l, int r, int D) {
    int mid = (l+r)>>1;
    tree[mid].l = tree[mid].r = 0;
    cmp_d = D;
    nth_element (tree+l+1, tree+mid+1, tree+1+r, cmp);
    //按照cmp把第mid元素放在中间 比他小的放左边 比他大的放右边
    for (int i = 0; i < 3; i++) {
        tree[mid].Max[i] = tree[mid].Min[i] = tree[mid].d[i];
    }
    if (l != mid) tree[mid].l = build_tree (l, mid-1, (D+1)%3);
    if (r != mid) tree[mid].r = build_tree (mid+1, r, (D+1)%3);
    if (tree[mid].l) push_up (mid, tree[mid].l);
    if (tree[mid].r) push_up (mid, tree[mid].r);
    return mid;
}

void insert (int now) {
    int D = 0, p = root;
    while (1) {
        push_up (p, now);//先更新p节点
        if (tree[now].d[D] >= tree[p].d[D]) {
            if (!tree[p].r) {
                tree[p].r = now;
                return ;
            }
            else p = tree[p].r;
        }
        else {
            if (!tree[p].l) {
                tree[p].l = now;
                return ;
            }
            else p = tree[p].l;
        }
        D ^= 1;
    }
    return ;
}

#define INF 0x3f3f3f3f3f3f
#define sqr(a) (a)*(a)
pli ans;
long long x, y, z;
long long dis (int p) {//点(x,y)在p的管辖范围内的可能最小值
    long long ans = 0;
    if (z < tree[p].Min[2]) return INF;
    //if (z > tree[p].Max[2]) return sqr (z-tree[p].Max[2]);
    if (x < tree[p].Min[0]) ans += sqr (tree[p].Min[0]-x);
    if (x > tree[p].Max[0]) ans += sqr (x-tree[p].Max[0]);
    if (y < tree[p].Min[1]) ans += sqr (tree[p].Min[1]-y);
    if (y > tree[p].Max[1]) ans += sqr (y-tree[p].Max[1]);
    return ans;
}

void query (int p) {
    pli dl = make_pair (INF, 1), dr = make_pair (INF, 1);
    long long d0 = INF;
    if (z >= tree[p].d[2])
        d0 = sqr (tree[p].d[0]-x) + sqr (tree[p].d[1]-y);//初始答案
    get_min (ans, make_pair (d0, tree[p].id));
    if (tree[p].l) dl = make_pair (dis (tree[p].l), tree[tree[p].l].id);
    if (tree[p].r) dr = make_pair (dis (tree[p].r), tree[tree[p].r].id);
    if (dl < dr) {
        if (dl < ans) query (tree[p].l);
        if (dr < ans) query (tree[p].r);
    }
    else {
        if (dr < ans) query (tree[p].r);
        if (dl < ans) query (tree[p].l);
    }
}

int main () {
    //Open ();
    int t; scan (t);
    while (t--) {
        scan (n), scan (m);
        for (int i = 1; i <= n; i++) {
            scan (pre[i].x); scan (pre[i].y); scan (pre[i].c); pre[i].id = i;
            p1[i] = pre[i];
            tree[i].d[0] = pre[i].x, tree[i].d[1] = pre[i].y, tree[i].d[2] = pre[i].c;
            tree[i].id = i;
        }
        for (int i = 1; i <= m; i++) {
            scan (p2[i].x); scan (p2[i].y); scan (p2[i].c);
        }
        root = build_tree (1, n, 0);
        for (int i = 1; i <= m; i++) {
            ans = make_pair (INF, 0); x = p2[i].x, y = p2[i].y, z = p2[i].c;
            query (root); int id = ans.se;
            printf ("%lld %lld %lld\n", pre[id].x, pre[id].y, pre[id].c);
        }
    }
    return 0;
}
