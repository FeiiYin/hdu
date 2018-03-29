/*
 * @Samaritan_infi
 */
/// 注意不能只能判断当前位置最大的回文串情况，可能有较小的回文串能实现而被忽略，暴力处理一下
/// 优化一下常数
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100000 + 5;

void show(int a[], int len) {
for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}

int now[maxn << 1];
int p[maxn << 1];
int Manacher(int s[], int len) {

    for(int i = 0; i < len; i ++) now[1 + (i << 1)] = -1, now[2 + (i << 1)] = s[i];
    now[len = (len << 1) + 1] = -1;
    int R = 0, pos = 0;
    for(int i = 0; i < len; i ++) {
        if(i <= R) p[i] = min(p[- i + (pos << 1)], R - i);
        else p[i] = 1;
        while(1 <= i - p[i] && i + p[i] <= len && now[i + p[i]] == now[i - p[i]]) p[i] ++;
        if(i + p[i] > R) R = i + p[i], pos = i;
    }
//    show(p, len);
//    show(now, len);
    int ans = 0;
    for(int i = 1; i < len; i += 2) {
        if(now[i] != -1) continue;
        int i_r = (p[i] - 1);
        for( ; (i_r >> 1) > ans; i_r -= 2) {
            int j = i + i_r;
            if(j > len) {
                i_r = len - i;
                continue;
            }
                
            int j_r = p[j] - 1;
            if(j - j_r <= i) {
                ans = max(ans, (i_r >> 1));
                break;
            }
        }
    }
    return ans * 3;
}

int read[maxn];

int main() {
    int kase; scanf("%d", &kase);
    int tt = 1;
    while(kase --) {
        int n; scanf("%d", &n);
        for(int i = 0; i < n; i ++) scanf("%d", &read[i]);
        printf("Case #%d: %d\n", tt ++, Manacher(read, n));
    }
    return 0;
}
