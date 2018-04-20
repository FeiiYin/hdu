/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

inline int read() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

const int maxn = 1e5 + 5;
const int mod = 998244353;

int s_2[maxn], s_3[maxn];

ll quick_pow(ll a, ll b) {
    ll ans = 1;
    while(b) {
        if(b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return ans;
}

int main() {
    int kase = read();
    while(kase --) {
        int n = read(), op = read();
        memset(s_2, 0, sizeof s_2);
        memset(s_3, 0, sizeof s_3);

        int a, b, c;
        while(op --) {
            a = read(); b = read(); c = read();
            if(c == 2) {
                s_2[a] ++;
                s_2[b + 1] --;
            } else {
                s_3[a] ++;
                s_3[b + 1] --;
            }
        }
        int index_2 = maxn, index_3 = maxn;
        int pre_2 = 0, pre_3 = 0;
        for(int i = 1; i <= n; i ++) {
            pre_2 += s_2[i];
            pre_3 += s_3[i];
            index_2 = min(index_2, pre_2);
            index_3 = min(index_3, pre_3);
        }
        //cout << index_2 << " " << index_3 << endl;
        ll ans = quick_pow((ll)2, (ll)index_2) * quick_pow((ll)3, (ll)index_3);
        printf("%lld\n", ans % mod);
    }
    return 0;
}
