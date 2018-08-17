/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000007;
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

const int N=50100;
int _,n,c[N],d[N],m[N],p[N],e[N],E[N],R[N];
ll solve() {
    /// 自动排序，支持修改
    multiset<pair<ll,int> > w;
    /// 当前库存电脑数 | 电脑累计的存储成本
    ll s=0; ll ss=0;
    ll ans=0;
//    rep(i,0,n) {
//        printf("%d %d %d %d %d\n",p[i],m[i],e[i],E[i],d[i]);
//    }
    rep(i,0,n) {
        w.insert(mp(m[i]-ss,p[i]));
        /// 假设库存中的所有都从第 1 个月开始存储，所以存入的时候减去截止到当前月的存储成本
        s+=p[i]-d[i];
        /// 贪心选取当前工厂里成本最低的电脑
        while (!w.empty()&&d[i]>0) {
            auto c=*w.begin(); w.erase(w.begin());
            if (c.se<=d[i]) {
                ans+=(ll)(c.fi+ss)*c.se;
                d[i]-=c.se;
            } else {
                ans+=(ll)(c.fi+ss)*d[i];
                c.se-=d[i]; d[i]=0;
                w.insert(c);
            }
        }
        if (d[i]) return -1;
        ss+=E[i+1];
        ll req=s-e[i+1];
        s=min(s,(ll)e[i+1]);        
        /// 将当前成本最高的电脑丢弃，因为只能存储 computer_num[i + 1] 台
        while (req>0) {
            auto c=*(--w.end()); w.erase(--w.end());
            if (c.se<=req) {
                req-=c.se;
            } else {
                c.se-=req; req=0;
                w.insert(c);
            }
        }
//        puts("gg");
//        for (auto p:w) printf("%lld %d\n",p.fi+ss,p.se);
    }
    return ans;
}
int main() {
    for (scanf("%d",&_);_;_--) {
        scanf("%d",&n);
        rep(i,0,n) {
            scanf("%d%d%d%d",c+i,d+i,m+i,p+i);
        }
        /// 原材料数量获得不限，贪心选取当前月的最小原材料成本，并入电脑成本中
        rep(i,1,n) {
            scanf("%d%d%d",e+i,R+i,E+i);
            c[i]=min(c[i],c[i-1]+R[i]);
            m[i]+=c[i];
        }
        m[0]+=c[0];
        printf("%lld\n",solve());
    }
}
