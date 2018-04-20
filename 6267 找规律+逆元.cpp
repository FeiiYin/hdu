/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

inline ll read() {
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

const int maxn = 1e5 + 5;
const int mod = 998244353;

ll inv[maxn];
ll jie[maxn];
ll k[maxn];
void init() {
    inv[1] = 1;
    jie[0] = jie[1] = 1;
    k[1] = 2;
    for(int i = 2; i < maxn; i ++) {
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        jie[i] = (jie[i - 1] * i) % mod;
        k[i] = i + 2;
    }
}


//
//bool vis[1000000];
//int par[10];
//int deep[10];
//int post[10];
//vector<int> ans;
//
//
//void dfs(int rt, int dp, int num) {
//    deep[rt] = dp;
//    for(int i = 1; i <= num; i ++) {
//        if(par[i] == rt) {
//            dfs(i, dp + 1, num);
//        }
//    }
//}
//
//void get_a(int i, int num) {
//
//        for(int j = 1; j < i; j ++) {
//            par[i] = j;
//            if(i == num) {
//                dfs(1, 1, num);
//                for(int k = 1; k <= num; k ++) {
//                    post[k] += deep[k];
//                }
//            } else {
//                get_a(i + 1, num);
//            }
//        }
//}

void gcd(ll a, ll b, ll &d, ll &x, ll &y) {
    if(! b) {d = a; x = 1; y = 0;}
    else {gcd(b, a % b, d, y, x); y -= x * (a / b); }
}

ll ni(ll a, ll n) {
    ll d, x, y;
    gcd(a, n, d, x, y);
    return d == 1 ? (x + n) % n: -1;
}

int main() {
    init();
//    memset(vis, 0, sizeof vis);
////    int kase = read();
////    while(kase --) {
//    for(int num = 2; num <= 7; num ++) {
//        //memset(par, 0, sizeof par);
//        memset(post, 0, sizeof post);
//        par[1] = 0;
//        get_a(2, num);
//        for(int i = 1; i <= num; i ++) {
//            cout << post[i] << " ";
//        }cout << endl;
//    }

    int kase = read();
    while(kase --) {
        int n;// =read();
        scanf("%d", &n);
        ll x, ans = 0;
        ll fi = jie[n - 1], se = fi;
        for(int i = 1; i <= n; i ++) {
            //x = read();
            scanf("%lld", &x);
            //cout << fi << " " ;
            ans = (ans + fi * x ) % mod;
            fi = (fi + se * inv[i]) % mod;// (i);

        }//puts("");
        ans = ans * ni(jie[n], mod) % mod;
        cout << ans << endl;
    }
    return 0;
}
