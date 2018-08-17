/*
 * @Samaritan_infi
 * hdu 6406 更新后求最大递增长度 | 主席树（在线）.cpp
 * 先预习处理前缀最大值和到这里的长度，在用单调栈处理出从i这里开始的递增序列长度。
 * 然后从n~1倒着建立主席树维护区间的最小下标。这样就可以询问后面开始的最小位置。
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}

const int N = 1e5 + 5;
const int M = 6e6 + 5;

int n;

int lson[M], rson[M], t_pos[M];
int root[N];
int cnt;

inline void init() {
    cnt = 1;
    root[0] = 0;
}
void update(int &now, int pre, int l, int r, int val, int pos) {
    now = cnt ++;
    lson[now] = lson[pre], rson[now] = rson[pre];
    t_pos[now] = min(t_pos[pre], pos);
    if(l == r) return;
    int mid = l + r >> 1;
    if(val <= mid) update(lson[now], lson[pre], l, mid, val, pos);
    else update(rson[now], rson[pre], mid + 1, r, val, pos);
}
int query(int now, int l, int r, int val) {
    if(! now || val > r) return n + 1;
    if(val <= l) return t_pos[now];
    int mid = l + r >> 1;
    if(val <= mid) return min(query(lson[now], l, mid, val), query(rson[now], mid + 1, r, val));
    else return query(rson[now], mid + 1, r, val);
}

int height[N];
int max_height[N], max_height_pos[N], increment_num[N];
int que[N], length_from_i[N]; /// 单调队列 | i及i之后的递增长度
int father[N]; /// 下一个比i大的位置

inline void work_on_increment_length(int n, int m) {
    int top = 0, ed = 0;
    for(int i = n; i >= 1; i--) {
        while(top > ed && height[ que[top] ] <= height[i])
            top--;
        que[++top] = i;
        length_from_i[i] = top - ed;
        if(top > 1) father[i] = que[top - 1];
        else father[i] = n + 1;
    }
    length_from_i[n + 1] = 0;
}

void solve(int n, int m) {
    init();
    root[n + 1] = 0, t_pos[0] = n + 1;
    lson[0] = rson[0] = 0;
    for(int i = n; i >= 1; i--)
        update(root[i], root[i + 1], 1, 1e9, height[i], i);

    int pos, val, ans;
    while(m --) {
        scanf("%d %d", &pos, &val);
        if(pos == 1) {
            ans = 1 + length_from_i[query(root[2], 1, 1e9, val + 1)];
        } else {
            int pre = max_height_pos[pos - 1];
            if(father[pre] == pos) {
                //cout << query(root[pos + 1], 1, 1e9, val + 1) << endl;
                if(val > height[pre]) ans = increment_num[pre] + 1 + length_from_i[query(root[pos + 1], 1, 1e9, val + 1)];
                else ans = increment_num[pre] + length_from_i[query(root[pos + 1], 1, 1e9, height[pre] + 1)];
            } else {
                if(val > height[pre]) ans = increment_num[pre] + 1 + length_from_i[query(root[pos + 1], 1, 1e9, val + 1)];
                else ans = increment_num[n];
            }
        }
        printf("%d\n", ans);
    }
}

int main() {
    int kase = read();
    while(kase --) {
        n = read();int m = read();
        for(int i = 1; i <= n; i ++)
            scanf("%d", &height[i]);
        for(int i = 1; i <= n; i ++)
            if(height[i] > max_height[i - 1]) {
                max_height[i] = height[i];
                max_height_pos[i] = i;
                increment_num[i] = increment_num[i - 1] + 1;
            } else {
                max_height[i] = max_height[i - 1];
                max_height_pos[i] = max_height_pos[i - 1];
                increment_num[i] = increment_num[i - 1];
            }
        work_on_increment_length(n, m);
        solve(n, m);
    }
    return 0;
}
