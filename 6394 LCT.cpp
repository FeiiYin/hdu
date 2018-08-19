#include <algorithm>
#include <iostream>
#include <vector>
const int MAXN=1e5+10; 
#define ll long long
using namespace std;
vector<int>vec[MAXN];
struct FastIO
{
    static const int S=200;
    int wpos;
    char wbuf[S];
    FastIO():wpos(0){}
    inline int xchar()
    {
        static char buf[S];
        static int len=0,pos=0;
        if(pos==len) pos=0,len=fread(buf,1,S,stdin);
        if(pos==len) exit(0);
        return buf[pos++];
    }
    inline int read()
    {
        int s=1,c=xchar(),x=0;
        while(c<=32) c=xchar();
        if(c=='-') s=-1,c=xchar();
        for(;'0'<=c&&c<='9';c=xchar()) x=x*10+c-'0';
        return x*s;
    }
    ~FastIO()
    {
        if(wpos) fwrite(wbuf,1,wpos,stdout),wpos=0;
    }
}io;
bool rt[MAXN];int ch[MAXN][2],size[MAXN],pre[MAXN],fa[MAXN][21],n,a[MAXN];
int dep[MAXN];
void dfs(int v,int f,int deep){
  fa[v][0]=f;dep[v]=deep+1;
  for(int i=0;i<vec[v].size();i++){
      if(vec[v][i]!=f){
          dfs(vec[v][i],v,deep+1);
      }
  }
}
void dfs1(int v){
    for(int i=1;i<=20;i++)fa[v][i]=fa[fa[v][i-1]][i-1];
    for(int i=0;i<vec[v].size();i++)if(vec[v][i]!=fa[v][0])dfs1(vec[v][i]);
}
int Lca(int v,int k){
    for(int i=0;i<=20;i++)if((k&(1<<i)))v=fa[v][i];
    return v;
}
void P(int r){
    if(!rt[r]) P(pre[r]);//传标记 
}
void up(int x){
    size[x]=size[ch[x][0]]+size[ch[x][1]]+1;
}
void rotate(int x,int kind){
    int y=pre[x];
    ch[y][!kind]=ch[x][kind];
    pre[ch[x][kind]]=y;
    if(rt[y]) rt[y]=false,rt[x]=true;
    else ch[pre[y]][ch[pre[y]][1]==y]=x;
    pre[x]=pre[y];ch[x][kind]=y;pre[y]=x;
    up(y);
}
void splay(int x){
    //P(x);
    while(!rt[x]){
        if(rt[pre[x]]) rotate(x,ch[pre[x]][0]==x);
        else{
            int y=pre[x];
            int kind=(ch[pre[y]][0]==y);
            if(ch[y][kind]==x){
                rotate(x,!kind);rotate(x,kind);
            }
            else{
                rotate(y,kind);rotate(x,kind);
            }
        }
    }
    up(x);
}
int access(int u){
    int y=0;int x=u;
    while(u){
        splay(u);
        if(ch[u][1]) rt[ch[u][1]]=1,pre[ch[u][1]]=u,ch[u][1]=0;
        ch[u][1]=y;pre[y]=u;
        up(u); 
        if(y) rt[y]=false;
        up(u);
        y=u;u=pre[u];
    }
    splay(x);
    return size[ch[x][0]]+1;
}
void Cut(int u,int v){
    splay(u);
    if(ch[u][0]) pre[ch[u][0]]=pre[u],rt[ch[u][0]]=1,ch[u][0]=0;
    up(u);
    pre[u]=v; 
}
int main(){
    int _=io.read();
    while(_--){
    n=io.read();
    int u,v;
    for(int i=1;i<n;i++)u=io.read(),vec[u].push_back(i+1);
    dfs(1,0,0);dfs1(1);
    for(int i=1;i<=n;i++){
        a[i]=io.read();
        rt[i]=1;ch[i][0]=ch[i][1]=0;size[i]=1;
    }
    for(int i=1;i<=n;i++){
        if(dep[i]-a[i]>=0) pre[i]=Lca(i,a[i]);
        else pre[i]=0;
    }
    int m;m=io.read();
    int op,t1,t2;
    for(int i=1;i<=m;i++){
        op=io.read();
        if(op==1) t1=io.read(),printf("%d\n",access(t1));
        else{
            t1=io.read();t2=io.read();
            if(dep[t1]-t2>=0) Cut(t1,Lca(t1,t2));
            else Cut(t1,0);
        }
    }
    for(int i=1;i<=n;i++)vec[i].clear();
}
    return 0;
}
