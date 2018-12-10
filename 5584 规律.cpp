/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define PII pair<int, int>
#define fi first
#define se second
#define mp make_pair

int main(){
    int kase, _ = 1;
    scanf("%d", &kase);
    while (kase--) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (x < y) 
            swap(x,y);
        int k = __gcd(x,y), cnt = 1;
        while (x % (y + k) == 0) {
            cnt++;
            x = x / (y / k + 1);
            if (x < y) 
                swap(x, y);
        }
        printf("Case #%d: %d\n", _++, cnt);
    }
    return 0;
}
