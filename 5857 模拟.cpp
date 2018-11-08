#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 111111
int T,n,m,A[maxn],l1,l2,r1,r2,l,a,b,mid1,mid2;
double ans;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)scanf("%d",&A[i]);
        while(m--)
        {
            scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
            l=r1-l1+1+r2-l2+1;
            if(l2<l1)swap(l1,l2),swap(r1,r2);
            if(l2>r1)
            {
                a=r1-l1+1;
                if(l&1)
                {
                    mid1=l/2+1;
                    if(mid1>a)ans=A[l2+mid1-a-1];
                    else ans=A[l1+mid1-1];
                }
                else
                {
                    mid1=l/2,mid2=l/2+1;
                    double t1,t2;
                    if(mid1>a)t1=A[l2+mid1-a-1];
                    else t1=A[l1+mid1-1];
                    if(mid2>a)t2=A[l2+mid2-a-1];
                    else t2=A[l1+mid2-1];
                    ans=(t1+t2)/2;
                }
            } 
            else
            {
                if(r1>r2)swap(r1,r2);
                a=l2-l1,b=r1-l2+1;
                if(l&1)
                {
                    mid1=l/2+1;
                    if(mid1<=a)ans=A[l1+mid1-1];
                    else if(mid1<=a+2*b)ans=A[l2+(mid1-a+1)/2-1];
                    else ans=A[r1+mid1-a-2*b];
                }
                else
                {
                    mid1=l/2,mid2=l/2+1;
                    double t1,t2;
                    if(mid1<=a)t1=A[l1+mid1-1];
                    else if(mid1<=a+2*b)t1=A[l2+(mid1-a+1)/2-1];
                    else t1=A[r1+mid1-a-2*b];
                    if(mid2<=a)t2=A[l1+mid2-1];
                    else if(mid2<=a+2*b)t2=A[l2+(mid2-a+1)/2-1];
                    else t2=A[r1+mid2-a-2*b];
                    ans=(t1+t2)/2;
                }
            }
            printf("%.1f\n",ans);
        }
    }
    return 0;
}
