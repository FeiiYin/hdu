#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=11111;
const int mod=1e8+7;
char s[maxn];
int num[maxn],dp[maxn];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",s);
        int n=strlen(s);
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;i++)
            num[i+1]=s[i]-'0';
        memset(dp,0,sizeof(dp));
       ll ans=0;
       for(int i=0;i<=num[1];i++)
       {
           dp[1]=i;
           if(i>2)break;
           int j;
           for(j=2;j<=n;j++)
           {
               int k=num[j-1]-dp[j-1]-dp[j-2];
               if(k>2||k<0)
                break;
               dp[j]=k;
           }
           if(j<=n)continue;
           if(dp[n-1]+dp[n]!=num[n])continue;
           ll res=1;
           for(int i=1;i<=n;i++)
           {
               if(dp[i]==0||dp[i]==2)
                  res*=1;
               else
                  res*=2;
               res%=mod;
           }
           ans+=res;
           ans%=mod;
       }
       printf("%d\n",ans);
    }
    return 0;
}
