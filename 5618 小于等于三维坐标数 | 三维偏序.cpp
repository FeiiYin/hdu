/*
 * @Samaritan_infi
 */
/// 题意: 三维坐标(x, y, z)每个点求每一维都比自己小于等于的坐标数
/// 三位偏序，一维排序，二维CDQ，三维BIT
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e5 + 5, TREE_SIZE = 1e5 + 5;
struct node {
    int id, type, val;
    int x, y, z;
    node () {}
    node (int _id, int _t, int _x, int _y, int _z)
      : id(_id), type(_t), x(_x), y(_y), z(_z), val(0) {}
    bool operator < (const node & k) const {
        if (x == k.x && y == k.y) return z < k.z;
        if (x == k.x) return y < k.y;
        return x < k.x;
    }
    bool operator == (const node & k) const {
        return x == k.x && y == k.y && z == k.z;
    }
};
bool cmp_by_id (node a, node b) { return a.id < b.id; }
node arr[N], brr[N];
/// BIT
int tree[TREE_SIZE], tree_top;
inline int low_bit (int x) { return x & (-x); }
void add (int x, int val) {
    for (; x <= tree_top; x += low_bit(x)) tree[x] += val;
}
int query (int x) {
    int ans = 0;
    for (; x; x -= low_bit(x)) ans += tree[x];
    return ans;
}
/// CDQ分治，必须离线处理，常数较大，只考虑左块对右块的影响,意味着右块不能更新BIT!!!
/// 三维偏序问题 套树状数组
void CDQ (int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1, cnt = 0;
    CDQ(l, mid); CDQ(mid + 1, r);
    int cur1 = l, cur2 = mid + 1, sum = 0;
    for (int i = l; i <= r; i++) {
        /// 注意题目中允许等于，如果分散在两边那么在左边的是无法加上右边的影响的
        /// 这里要保证相等的时候是左边先放
        if (cur1 <= mid && arr[cur1].y <= arr[cur2].y || cur2 > r) {
            brr[i] = arr[cur1++];
            add(brr[i].z, 1);
        } else {
            brr[i] = arr[cur2++];
            brr[i].val += query(brr[i].z);
        }
    }
    for (int i = l; i <= mid; i++) add(arr[i].z, -1);
    for (int i = l; i <= r; i++) arr[i] = brr[i];
}
int main () {
    int kase; scanf("%d", &kase); while (kase --) {
        tree_top = 0;
        int n, x, y, z; scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d %d %d", &x, &y, &z);
            tree_top = max(tree_top, z);
            arr[i] = node(i, 1, x, y, z);
        }
        sort (arr+1, arr+1+n);
        for (int i = n - 1; i >= 1; i--) if (arr[i] == arr[i+1])
            arr[i].val = arr[i+1].val + 1;
        CDQ(1, n);
        sort (arr+1, arr+1+n, cmp_by_id);
        for (int i = 1; i <= n; i++) printf("%d\n", arr[i].val);
    }
    return 0;
}
