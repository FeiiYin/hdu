/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100000 + 5;
const int mod = 100000007;

int s[maxn];
int pre[maxn];
void show(int a[], int len) {
    for(int i = 1; i <= len; i ++) {
        printf("%d%c", a[i], i == len ? '\n' : ' ');
    }
}
int main() {
    int n;
    while(~ scanf("%d", &n) && n) {
        int a, b;
        memset(pre, 0, sizeof pre);
        for(int i = 0; i < n; i ++) {
            scanf("%d %d", &a, &b);
            pre[a] ++;
            pre[b + 1] --;
        }
        //show(pre, n);
        for(int i = 1; i <= n; i ++)
            pre[i] += pre[i - 1];
        show(pre, n);
    }
    return 0;
}
