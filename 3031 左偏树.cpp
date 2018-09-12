/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
/// 左偏树
struct node {
    int l, r, dis, val;
    /// dis 表示当前结点到叶子的最短距离
    /// l, r左右儿子, val结点值
} tree[N];
/// 合并两棵左偏树, (x, y):左偏树编号，输出新左偏树编号
int Merge (int x, int y) {
    //cout << x << " " << y << endl;
    if (!x) return y;
    if (!y) return x;
    if (tree[x].val < tree[y].val) swap(x, y); /// 设置根堆
    tree[x].r = Merge(tree[x].r, y);
    if (tree[tree[x].l].dis < tree[tree[x].r].dis)
        swap(tree[x].l, tree[x].r);
    if (tree[x].r) tree[x].dis = tree[tree[x].r].dis + 1;
    else tree[x].dis = 0;
    return x;
}

///插入操作(push)将插入的元素看成一棵只有一个节点的左偏树，然后merge

/// 删除操作(pop)根节点的左右子树合并，然后再将根节点删掉
int Pop (int x) {
    int l = tree[x].l, r = tree[x].r;
    tree[x].l = tree[x].r = tree[x].dis = 0;
    return Merge(l, r);
}
int tot; /// 左偏树node数

const int M = 105;
int pile[M], pile_num[M];
/// pile[i]是左偏树的根节点, 树里面每一个结点是tree[i]

inline void init() {
    tot = 1;
    memset(tree, 0, sizeof tree);
    memset(pile, 0, sizeof pile);
}

int main () {
    int kase; scanf("%d", &kase);
    char op[10];
    int n, m, x, happy = 0, wolf = 0;
    while (kase --) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= m; i ++) scanf("%d", &pile_num[i]);
        init();
        for (int i = 1; i <= m; i ++) {
            for (int j = 1; j <= pile_num[i]; j ++) {
                scanf("%d", &x);
                /// 插入结点
                tree[tot].l = tree[tot].r = tree[tot].dis = 0;
                tree[tot].val = x;
                pile[i] = Merge(pile[i], tot ++);
            }
        }
        int root[2]; ///root[0] happy, root[1] wolf
        int num[2]; /// 牌数
        root[0] = root[1] = num[0] = num[1] = 0;
        for (int i = 0; i < n; i ++) {
            scanf("%s", op);
            if (op[0] == 'T') {
                /// 抽取一堆牌
                scanf("%d", &x);
                root[i & 1] = Merge(pile[x], root[i & 1]);
                num[i & 1] += pile_num[x];
                pile[x] = pile_num[x] = 0;
            } else if (op[0] == 'C') {
                /// 最大值小的一方给另一方所有
                int max_id = tree[root[0]].val > tree[root[1]].val ? 0 : 1;
                root[max_id] = Merge(root[max_id], root[max_id ^ 1]);
                num[max_id] += num[max_id ^ 1];
                root[max_id ^ 1] = num[max_id ^ 1] = 0;
            } else if (op[0] == 'L') {
                /// 删除当前最大
                root[i & 1] = Pop(root[i & 1]);
                num[i & 1] --;
            } else if (op[0] == 'A') {
                /// 增加最大值
                scanf("%d", &x);
                tree[root[i & 1]].val += x;
            } else if (op[0] == 'E') {
                /// 修改最大值，可能变小
                scanf("%d", &x);
                int temp = Pop(root[i & 1]);
                tree[temp].val = x;
                root[i & 1] = Merge(temp, root[i & 1]);
            }
        }
        printf("%d:%d\n", num[0], num[1]);
        if (num[0] > num[1]) wolf ++;
        else happy ++;
    }
    printf("%s\n", happy > wolf ? "I will be back!!" : "Hahaha...I win!!");
    return 0;
}
