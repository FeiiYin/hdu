/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn=1e6+50;
char str[5*maxn];
bitset<1005> s[20];
bitset<1005> ans;

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<20;i++)
        s[i].reset();
        ans.reset();
        for(int i=0;i<n;i++)
        {
            int N,temp;
            scanf("%d",&N);
            for(int j=0;j<N;j++)
            {
                scanf("%d",&temp);
                s[temp][i] = 1;
            }
        }
        getchar();
        gets(str);
        int len=strlen(str);
        for(int i=0;i<len;i++)
        {
            ans=ans<<1;
            ans[0]=1;
            ans&=s[str[i]-'0'];
            if(ans[n-1]==1)
            {
                char temp=str[i+1];
                str[i+1]='\0';
                puts(str+i-n+1);
                str[i+1]=temp;
            }
        }
    }
    return 0;
}
