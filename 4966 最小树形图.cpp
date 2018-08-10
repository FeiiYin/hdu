/*
 * @Samaritan_infi
 */
/// DAG 有向图的最小生成树 贪心选择每个顶点入边值最小即可

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 25100;
const int M = 2000000;
const int inf = 0x3f3f3f3f;

struct edge{
    int u,v,w;
    edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
}e[N + M];

int sum[N],a[N],tot,in[N],pre[N],id[N],vis[N];
void add(int u,int v,int w) {
    e[tot++]=edge(u,v,w);
}

int Directed_MST(int root,int numv,int nume)//建有向图的最小生成树，其所有边的权值和酒是答案,复杂度O(VE)
{
    int i,j,k,u,v,ans=0;
    while(true)
    {
        for(i=0;i<numv;i++)in[i]=inf;
        for(i=0;i<nume;i++) {
            u=e[i].u;
            v=e[i].v;
            if(e[i].w<in[v]&&u!=v)
            {
                pre[v]=u;
                in[v]=e[i].w;
            }
        }
        for(i=0;i<numv;i++)
        {
            if(i==root)continue;
            if(in[i]==inf)return -1;//无法成树
        }
        //找环，合成一个新的顶点
        int t=0;
        memset(id, -1, sizeof (id[0]) * (numv + 3));
        memset(vis, -1, sizeof (vis[0]) * (numv + 3));
        in[root]=0;
        //标记每个环
        for(i=0;i<numv;i++)
        {
            ans+=in[i];
            v=i;
            while(vis[v]!=i&&id[v]==-1&&v!=root)
            {
                vis[v]=i;
                v=pre[v];
            }
            if(v!=root&&id[v]==-1)//存在环，标记相同的id
            {
                for(u=pre[v];u!=v;u=pre[u])
                    id[u]=t;
                id[v]=t++;
            }
        }
        if(t==0)break;//无环
        for(i=0;i<numv;i++)
            if(id[i]==-1)id[i]=t++;
        //缩点,重新标记序号
        for(i=0;i<nume;i++)
        {
            v=e[i].v;
            e[i].u=id[e[i].u];
            e[i].v=id[e[i].v];
            if(e[i].u!=e[i].v)
                e[i].w-=in[v];
        }
        numv=t;
        root=id[root];
    }
    return ans;
}

int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        if(n==0&&m==0)break;
        int i,j,k;
        sum[0]=tot=0;
        for(i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            a[i]++;             //等级从1到a[i]开始
            sum[i+1]=sum[i]+a[i];
        }
        //将所有等级作为一个节点，对于等级i,可以建一条对等级i-1的边，边权为0
        //其中sum[n]为虚拟的跟，指向所有的课程的level0的点。
        for(i=0;i<n;i++)
        {
            for(j=sum[i+1]-1;j>sum[i];j--)add(j,j-1,0);
            add(sum[n],sum[i],0);
        }
        int c,d,l1,l2,money;
        for(i=0;i<m;i++)
        {
            scanf("%d%d%d%d%d",&c,&l1,&d,&l2,&money);
            add(sum[c-1]+l1,sum[d-1]+l2,money);
        }
        printf("%d\n",Directed_MST(sum[n],sum[n]+1,tot));
    }
    return 0;
}
