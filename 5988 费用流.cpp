///因为求概率，所以费用时将其转换成log，输出时再变回e的次数
///这个板子是从0开始的

#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<vector>
using namespace std;
typedef long long ll;
typedef pair<double,int> P;
#define PI acos(-1.0)
const int maxn=200,maxm=1e5+100,inf=0x3f3f3f3f,mod=1e9+7;
const ll INF=1e18+7;
const double eps=0.000001;
struct edge
{
    int from,to;
    int cap;
    double cost;
    int rev;
};
int NN;
vector<edge>G[maxn];
double h[maxn];
///顶点的势，取h(u)=(s到u的最短距离)，边e=(u,v)的长度变成d`(e)=d(e)+h(u)-h(v)>=0
double dist[maxn];
int prevv[maxn],preve[maxn];///前驱结点和对应的边
void addedge(int u,int v,int cap,double cost)
{
    edge e;
    e.from=u,e.to=v,e.cap=cap,e.cost=cost,e.rev=G[v].size();
    G[u].push_back(e);
    e.from=v,e.to=u,e.cap=0,e.cost=-cost,e.rev=G[u].size()-1;
    G[v].push_back(e);
}
double min_cost_flow(int s,int t,int f)
{
    double res=0.0;
    fill(h,h+NN,0.0);
    while(f>0)
    {
        priority_queue<P,vector<P>,greater<P> >q;
        fill(dist,dist+NN,inf);
        dist[s]=0.0;
        q.push(P(dist[s],s));
        while(!q.empty())
        {
            P p=q.top();
            q.pop();
            int u=p.second;
            if(dist[u]<p.first) continue;
            for(int i=0; i<G[u].size(); i++)
            {
                edge e=G[u][i];
                if(e.cap>0&&dist[e.to]-(dist[u]+e.cost+h[u]-h[e.to])>=eps)
                {
                    dist[e.to]=dist[u]+e.cost+h[u]-h[e.to];
                    prevv[e.to]=u;
                    preve[e.to]=i;
                    q.push(P(dist[e.to],e.to));
                }
            }
        }
        if(fabs(dist[t]-inf)<=eps) return res;
        for(int i=0; i<NN; i++) h[i]+=dist[i];
        int d=f;
        for(int i=t; i!=s; i=prevv[i])
            d=min(d,G[prevv[i]][preve[i]].cap);
        f-=d;
        res+=d*h[t];
        //cout<<d<<" "<<h[t]<<" "<<d*h[t]<<endl;
        for(int i=t; i!=s; i=prevv[i])
        {
            //cout<<i<<" ";
            edge &e=G[prevv[i]][preve[i]];
            e.cap-=d;
            G[i][e.rev].cap+=d;
        }
        //cout<<s<<endl;
    }
    return res;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        int s=0,t=n+1,f;
        NN=t+1;
        for(int i=1; i<=n; i++)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            int x=min(a,b);
            a-=x,b-=x;
            if(a>0) addedge(s,i,a,0);
            else if(b>0) addedge(i,t,b,0);
        }
        for(int i=1; i<=m; i++)
        {
            int u,v,cap;
            double cost;
            scanf("%d%d%d%lf",&u,&v,&cap,&cost);
            if(cap>0) addedge(u,v,1,0);
            if(cap-1>0) addedge(u,v,cap-1,-1*log(1.0-cost));
        }
        double sum=min_cost_flow(s,t,inf);
        printf("%.2f\n",1.0-exp(-1.0*sum));
        for(int i=0; i<NN; i++) G[i].clear();
    }
    return 0;
}
