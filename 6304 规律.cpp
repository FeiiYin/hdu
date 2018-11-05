#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MOD = 1e9+7;
const int inv2 = 500000004;
int T;
LL n;
LL calc(LL n) {
    if(n<=1) return n;
    else return calc(n/2)+n;
}
void solve() {
    LL l=n/2-30,r=n/2+30,m,p=-1;
    //需要预先估计上下界减少二分次数,否则会TLE.
    while(l<=r) {
        m = (l+r)/2;
        if(calc(m)>n) r=m-1;
        else l=m+1,p=m;
    }
    LL rest = ((n - calc(p))%MOD+MOD)%MOD;
    LL ans = 0, s, t, e, k, c=1, x, y;
    for(LL i=1;; i<<=1,c++) {
        if(i>p) break;
        x = i%MOD;
        y = 2*i%MOD;
        s = x;
        k = ((p-i)/(2*i)+1)%MOD;
        e = (y*(k-1)%MOD+i)%MOD;
        ans = (ans+c*(s+e)%MOD*k%MOD*inv2%MOD)%MOD;
    }
    ans = (ans + rest*((p+1)%MOD)%MOD)%MOD;
    printf("%lld\n",ans+1);
}
int main() {
    scanf("%d",&T);
    while(T--) {
        scanf("%lld",&n);
        n--; //偏移一项
        solve();
    }
    return 0;
}
