/*
 * @Samaritan_infi
 */
/// 题目求每一个位置在排序过程中，最左边和最右边的最大值
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100000 + 5;

int read[maxn];
int pos[maxn];

int tree[maxn];
int low_bit(int x) { return x & (- x); }
int sum(int x) {
    int ans = 0;
    for( ; x > 0; x -= low_bit(x)) ans += tree[x];
    return ans;
}
int n;
void update(int x, int val) {
    for( ; x <= n; x += low_bit(x)) tree[x] += val;
}

int rig[maxn];
int main() {
    int kase; scanf("%d", &kase);
    int tt = 1;
    while(kase --) {
        scanf("%d", &n);
        memset(tree, 0, sizeof tree);
        for(int i = 1; i <= n; i ++) {
            scanf("%d", &read[i]);
            pos[ read[i] ] = i;
        }
        for(int i = n; i >= 1; i --) {
            ///右边比i小的数的个数
            rig[ read[i] ] = sum( read[i] );
            update(read[i], 1);
        }
        printf("Case #%d:", tt ++);
//        for(int i = 1; i <= n; i ++) cout << pos[i] << " "; cout << endl;
//        for(int i = 1; i <= n; i ++) cout << rig[i] << " "; cout << endl;
        for(int i = 1; i <= n; i ++) {
            /// 可能原来比现在还在左边，所以要取小
            /// 他会向右移动比它小的次数
            printf(" %d", rig[i] + pos[i] - min(pos[i], i));
        } puts("");
    }
    return 0;
}

