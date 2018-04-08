/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
#define test cout << "  test  " ;
using namespace std ;
typedef long long ll ;

inline bool scan(int &num) {
    char in; bool IsN = false;
    in = getchar();
    if(in == EOF) return false;
    while(in != '-' && (in < '0' || in > '9')) in = getchar();
    if(in == '-'){ IsN = true; num = 0;}
    else num = in - '0';
    while(in = getchar(), in >= '0' && in <= '9'){
        num *= 10, num += in - '0';
    }
    if(IsN) num = -num;
    return true;
}

const int maxn = 1e5 + 25;
const int max_node = 2e6 + 5;
struct node {
    int l, r;
    int sum;
    node() {sum = 0;}
    node(int a, int b, int c) {l = a, r = b, sum = c;}
};
node tree[max_node];
int root[maxn];
int cnt;

struct value {
    int x, id;
    value() {}
    value(int a, int b) {x = a, id = b;}
    bool operator < (const value &k) const {
        return x < k.x;
    }
} Value[maxn];
int hash_list[maxn];

void init() {
    cnt = 1;
    root[0] = 0;
    tree[0] = node(0, 0, 0);
}

void update(int val, int &rt, int l, int r) {
    tree[cnt ++] = tree[rt];
    rt = cnt - 1;
    tree[rt].sum ++;
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(val <= mid)  update(val, tree[rt].l, l, mid);
    else            update(val, tree[rt].r, mid + 1, r);
}
///找区间第k小的位置
int query_pos(int i, int j, int k, int l, int r) {
    if(l == r) return l;
    int d = tree[ tree[j].l ].sum - tree[ tree[i].l ].sum;
    int mid = (l + r) >> 1;
    if(k <= d) return query_pos(tree[i].l, tree[j].l, k, l, mid);
    else return query_pos(tree[i].r, tree[j].r, k - d, mid + 1, r);
}

///总的第k小在区间上小于它的个数
int query(int i, int j, int k, int l, int r) {
    if(l == r) return tree[j].sum - tree[i].sum;
    int mid = (l + r) >> 1, ret = 0;
    if(k <= mid) ret += query(tree[i].l, tree[j].l, k, l, mid);
    else {
        ret += tree[ tree[j].l ].sum - tree[ tree[i].l ].sum;
        ret += query(tree[i].r, tree[j].r, k, mid + 1, r);
    }
    return ret;
}

int main() {
    int kase, tt = 1; scan(kase);
    while(kase --) {
        int n, op, x;
        scan(n); scan(op);
        for(int i = 1; i <= n; i ++) {
            scan(x);//scan(read[i]);
            Value[i] = value(x, i);
        }
        sort(Value + 1, Value + 1 + n);
        for(int i = 1; i <= n; i ++) hash_list[ Value[i].id ] = i;
        init();
        for(int i = 1; i <= n; i ++) {
            root[i] = root[i - 1];
            update(hash_list[i], root[i], 1, n);
        }
        int l, r;
        printf("Case %d:\n", tt ++);
        while(op --) {
            scan(l); scan(r); scan(x);
            l ++, r ++;
            //int min_pos = query_pos(root[l - 1], root[r], 1, 1, n);
            //if(Value[min_pos].x > x) {puts("0"); continue;}
            int pos = upper_bound(Value + 1, Value + 1 + n, value(x, 0)) - (Value + 1);
            //cout << pos << endl;

            if(pos)
            printf("%d\n", query(root[l - 1], root[r], pos, 1, n));
            else        puts("0");
        }
    }
    return 0;
}
