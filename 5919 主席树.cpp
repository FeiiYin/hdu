/*
 * @Samaritan_infi
 */
 /// 先处理区间上有多少个不同的数
 /// 由于要最先出现的位置，所以要前缀树，所以从后往前更新。
 /// 查到后就可以当线段树处理了
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template <class T>
void show(T a[], int len) {
    for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}

inline int read() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

const int maxn = 2e5 + 5;
const int max_tree = 2e6 + 5;

struct node {
    int l, r;
    int sum;
    node() {sum = 0;}
    node(int a, int b, int c) {l = a, r = b, sum = c;}
};
node tree[maxn * 36]; /// 以后主席树就开 *36了， 不然会T
int cnt;
int root[maxn];

struct value {
    int x, id;
    value() {}
    value(int a, int b) {x = a, id = b;}
    bool operator < (const value &k) const {
        return x < k.x;
    }
} ;//Value[maxn];
int origin[maxn];
int hash_list[200005], hash_pos;


void init() {
    tree[0] = node(0, 0, 0);
    cnt = 1;
    root[0] = 0;
}

void update(int k, int pre_tree, int &now_tree, int l, int r, int val) {

    now_tree = cnt ++;
    tree[now_tree] = tree[pre_tree];
    tree[now_tree].sum += val;
    //cout << now_tree << " " << tree[now_tree].sum << " " << k << endl;
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(k <= mid)    update(k, tree[pre_tree].l, tree[now_tree].l, l, mid, val);
    else        update(k, tree[pre_tree].r, tree[now_tree].r, mid + 1, r, val);
}

int query(int rt, int l, int r, int L, int R) {
    if(L <= l && r <= R) return tree[rt].sum;
    if(r < L || l > R) return 0;
    int mid = (l + r) >> 1;
    int res = 0;
    if(L <= mid ) res += query(tree[rt].l, l, mid, L, R);
    if(mid < R) res += query(tree[rt].r, mid + 1, r, L, R);
    return res;
}

int find_k(int rt, int l, int r, int k) {
    if(l == r) return l;
    int mid = (l + r) >> 1;
    if(tree[tree[rt].l].sum >= k) return find_k(tree[rt].l, l, mid, k);
    else return find_k(tree[rt].r, mid + 1, r, k - tree[ tree[rt].l ].sum);
}

int main() {
    int kase = read(), tt = 1;
    while(kase --) {
        int n = read(), op = read(), x;
        for(int i = 1; i <= n; i ++) {
            x = read();
            origin[i] = x;
        }
        init();
        root[n + 1] = 0;

        memset(hash_list, 0, sizeof hash_list);
        for(int i = n; i >= 1; i --) {
            update(i, root[i + 1], root[i], 1, n, 1);
            if(hash_list[ origin[i] ]) {
                update(hash_list[ origin[i] ], root[i], root[i], 1, n, -1);
            }
            hash_list[ origin[i] ] = i;
        }

        int l, r;
        int pre = 0;
        printf("Case #%d:", tt ++);
        while(op --) {
            l = read(), r = read();
            l = (l + pre) % n + 1, r = (r + pre) % n + 1;
            if(r < l) swap(l, r);
            int num = query(root[l], 1, n, l, r);
            num = (num + 1) / 2;
            printf(" %d", pre = find_k(root[l], 1, n, num));
        }   puts("");
    }
    return 0;
}
