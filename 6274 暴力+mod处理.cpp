/*
 * @Samaritan_infi
 */
 /// 用BIT会t
 #include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=100100;
int a[N],b[N],num[1010][1010],n; //num[x][y]表示对于所有a[i]==x时的b[i]%a[i]余数大于等于y的数目
bool check(LL x,LL s) 
{
    LL ret=0;
    for(int i=1; i<=1000; i++)
    {
        ret+=x/i*num[i][0]; //num[i][0]为a数组中等于i的数的个数
        ret-=num[i][x%i+1];  //减掉所有 c2<c1 的情况
    }
    if(s<=ret)
        return true;
    return false;
}
LL solve(LL x)
{
    LL l=1,r=1e13,mid;
    while(l<r)
    {
        mid=(l+r)>>1;
        if(check(mid,x))
            r=mid;
        else
            l=mid+1;
    }
    return l;
}
int main()
{
    int TA,T,x,y,z;
    LL ret;
    scanf("%d",&TA);
    while(TA--)
    {
        scanf("%d%d",&n,&T);
        ret=0;
        for(int i=1; i<=1000; i++)
            for(int j=0; j<i; j++)
                num[i][j]=0;
        for(int i=1; i<=n; i++)
            scanf("%d",&a[i]);
        for(int i=1; i<=n; i++)
            scanf("%d",&b[i]),ret+=(b[i]/a[i]),num[a[i]][b[i]%a[i]]++;
        for(int i=1; i<=1000; i++)
            for(int j=i-1; j>=0; j--)
                num[i][j]+=num[i][j+1];
        while(T--)
        {
            scanf("%d%d",&z,&x);
            if(z==1)
            {
                scanf("%d",&y);
                for(int i=b[x]%a[x]; i>=0; i--)
                    num[a[x]][i]--;
                for(int i=b[x]%y; i>=0; i--)
                    num[y][i]++;
                ret-=(b[x]/a[x]);
                ret+=(b[x]/y);
                a[x]=y;
            }
            else if(z==2)
            {
                scanf("%d",&y);
                for(int i=b[x]%a[x]; i>=0; i--)
                    num[a[x]][i]--;
                for(int i=y%a[x]; i>=0; i--)
                    num[a[x]][i]++;
                ret-=(b[x]/a[x]);
                ret+=(y/a[x]);
                b[x]=y;
            }
            else
            {
                printf("%lld\n",solve(ret+x));
            }
        }
    }
}
// #include<bits/stdc++.h>
//using namespace std;
//typedef long long ll;
//
//const int maxn = 1e5 + 5;
//
//int a[maxn], b[maxn];
//
//int tree[1050][2050];

//int low_bit(int x) {return x & (-x);}
//
//void add(int pos, int tree_pos, int val) {
//    for(; pos <= 1000; pos += low_bit(pos)) tree[tree_pos][pos] += val;//, cout << pos << endl;
//}
//int query(int pos, int tree_pos) {
//    int ans = 0;
//    for(; pos > 0; pos -= low_bit(pos)) ans += tree[tree_pos][pos];
//    return ans;
//}
//
//int num[1050][1050];
//bool check(ll x, ll v) {
//    ll ans = 0;
//
//    for(int i = 1; i <= 1000; i ++) {
//        if(! num[i]) continue;
//        int k;
//        if(x % i) k = x % i;
//        else k = 0;
//        k = query(1000, i) - query(k, i);
//        ans = ans + x/i * num[i] - k;
//    }
//    return ans >= v;
//}
//
//int main() {
//    int kase; scanf("%d", &kase);
//    while(kase --) {
//        //memset(tree, 0, sizeof tree);
//        memset(num, 0, sizeof num);
//        int n, m;
//        ll ret = 0;
//        scanf("%d %d", &n, &m);
//        for(int i = 1; i <= n; i ++) scanf("%d", &a[i]), num[ a[i] ] ++;
//        for(int i = 1; i <= n; i ++) scanf("%d", &b[i]);
//
//        for(int i = 1; i <= n; i ++) {
//            ret += (ll)(b[i] / a[i]);
//            if(b[i] % a[i])
//            add(b[i] % a[i], a[i], 1);
//        }
//        //cout << "??" << endl;
//        while(m --) {
//            int op, x, y;
//            scanf("%d", &op);
//            if(op == 3) {
//                scanf("%d", &x);
//                ll l = 1, r = 1e12, mid;
//                while(l < r) {
//                    mid = (l + r) >> 1;
//                    if(check(mid, ret + x)) r = mid;
//                    else l = mid + 1;
//                }
//
//                printf("%lld\n", l);
//                continue;
//            }
//            scanf("%d %d", &x, &y);
//            if(op == 1) {
//                int pre = a[x];
//                a[x] = y;
//                ret = ret - b[x]/pre + b[x]/y;
//
//                num[pre] --; num[y] ++;
//                if(b[x] % pre)
//                    add(b[x] % pre, pre, -1);
//                if(b[x] % y)
//                    add(b[x] % y, y, 1);
//            } else {
//                int pre = b[x];
//                b[x] = y;
//                ret = ret - (pre/a[x]) + (y/a[x]);
//
//                if(pre % a[x])
//                    add(pre % a[x], a[x], -1);
//                if(y % a[x])
//                    add(y % a[x], a[x], 1);
//            }
//        }
//    }
//    return 0;
//}
/*
2
4 6
2 4 6 8
1 3 5 7
1 2 3
2 3 3
3 15
1 3 8
3 90
3 66
8 5
2 4 8 3 1 3 6 24
2 2 39 28 85 25 98 35
3 67
3 28
3 73
3 724
3 7775
*/
