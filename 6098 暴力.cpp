#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn = 1e5+10;
struct node
{
    ll m;
    int x;
}a[maxn];
inline bool cmp(node a, node b)
{
    return a.m > b.m;
}
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n;
        ll maxn,mm;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) scanf("%lld", &mm),a[i].x = i,a[i].m = mm;
        maxn = 0;
        for(int i = 1; i <= n; i+=2)
        {
            maxn = max(maxn, a[i].m);
        }
        printf("%lld", maxn);
        sort(a + 1,a + n + 1, cmp);
        for(int i = 3; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                if(a[j].x % i != 0) {printf(" %lld",a[j].m);break;}
            }
        }
        printf("\n");
    }
    return 0;
}
