/*
 * @Samaritan_infi
 */
///注意查询的时候是L[r], R[r], 如果是BIT的话，就是L[r-1], R[r]
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf=0x3f3f3f3f3f3f3f3f;
const int maxn=100010;
vector<int>G[maxn];
ll max1[maxn*4],lazy[maxn*4],val[maxn];
int L[maxn],R[maxn],cost[maxn];
int idx;
void dfs(int u,int f,ll vv){
    L[u]=++idx;
    for(unsigned int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(v==f) continue;
        dfs(v,u,(ll)cost[v]+vv);
    }
    R[u]=idx;
    val[L[u]]=vv;
}
void pushup(int node){
    max1[node]=max(max1[node<<1],max1[node<<1|1]);
}
void pushdown(int node){
    if(lazy[node]){
        lazy[node<<1]+=lazy[node];
        lazy[node<<1|1]+=lazy[node];
        max1[node<<1]+=lazy[node];
        max1[node<<1|1]+=lazy[node];
        lazy[node]=0;
    }
}
void buildtree(int le,int ri,int node){
    if(le==ri){
        max1[node]=val[le];
        return ;
    }
    int t=(le+ri)>>1;
    buildtree(le,t,node<<1);
    buildtree(t+1,ri,node<<1|1);
    pushup(node);
}
void update(int l,int r,int x,int le,int ri,int node){
    if(l<=le&&ri<=r){
        lazy[node]+=(ll)x;
        max1[node]+=(ll)x;
        return ;
    }
    pushdown(node);
    int t=(le+ri)>>1;
    if(l<=t) update(l,r,x,le,t,node<<1);
    if(r>t) update(l,r,x,t+1,ri,node<<1|1);
    pushup(node);
}
ll query(int l,int r,int le,int ri,int node){
    if(l<=le&&ri<=r) return max1[node];
    pushdown(node);
    ll ans=-inf;
    int t=(le+ri)>>1;
    if(l<=t) ans=max(ans,query(l,r,le,t,node<<1));
    if(r>t) ans=max(ans,query(l,r,t+1,ri,node<<1|1));
    return ans;
}
int main(){
    int T,cas=1,n,m,a,b,c;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=0;i<maxn;i++) G[i].clear();
        for(int i=0;i<n-1;i++){
            scanf("%d%d",&a,&b);
            a++;b++;
            G[a].push_back(b);
            G[b].push_back(a);
        }
        for(int i=1;i<=n;i++) scanf("%d",&cost[i]);
        idx=0;dfs(1,0,(ll)cost[1]);
        buildtree(1,n,1);
        memset(lazy,0,sizeof(lazy));
        printf("Case #%d:\n",cas++);
        while(m--){
            scanf("%d",&a);
            if(a==0){
                scanf("%d%d",&b,&c);b++;
                update(L[b],R[b],c-cost[b],1,n,1);
                cost[b]=c;
            }else{
                scanf("%d",&b);b++;
                ll answe=query(L[b],R[b],1,n,1);
                printf("%I64d\n",answe);
            }
        }
    }
    return 0;
}
