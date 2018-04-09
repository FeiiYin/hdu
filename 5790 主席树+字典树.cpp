/// 哎 算了
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
const int maxn=100005;
struct pi{
    int sum;
    int lson;
    int rson;
}pp[maxn*23];
int root[maxn],tot;
void build(int cnt,int l,int r){
    pp[cnt].sum=0;
    if(l==r) return;
    pp[cnt].lson=tot+1;
    tot++;
    build(tot,l,(l+r)/2);
    pp[cnt].rson=tot+1;
    tot++;
    build(tot,(l+r)/2+1,r);
}
void merg(int qq,int cnt,int n,int p,int k){
    int le,ri,mid;
    le=1;
    ri=n;
    while(le<=ri){
        mid=(le+ri)/2;
        pp[cnt]=pp[qq];
        pp[cnt].sum+=k;
        if (le==ri) break;
        if(p<=mid){
            pp[cnt].lson=tot+1;
            tot++;
            ri=mid;
            cnt=tot;
            qq=pp[qq].lson;
        }
        else{
            pp[cnt].rson=tot+1;
            tot++;
            le=mid+1;
            cnt=tot;
            qq=pp[qq].rson;
        }
    }
}
int query(int cnt,int le,int ri,int l,int r){
    int s=0;
    int mid;
    if(le>=l&&ri<=r){
        return pp[cnt].sum;
    }
    mid=(le+ri)/2;
    if(l<=mid) s+=query(pp[cnt].lson,le,mid,l,r);
    if(r>mid) s+=query(pp[cnt].rson,mid+1,ri,l,r);
    return s;
}
int ch[maxn][26];
int en[maxn];
vector<char>g[maxn];
char c[maxn];
int main()
{
    int n;
    while (scanf("%d",&n)!=EOF) {
        int m=0;
        int cnt=0;
        tot=0;
        for(int i=1;i<=n;i++){
            g[i].clear();
            scanf("%s",c);
            int p=strlen(c);
            m+=p;
            for(int j=0;j<p;j++) g[i].push_back(c[j]);
        }
        for(int i=0;i<=m;i++){
            memset(ch[i],0,sizeof(ch[i]));
        }
        build(0,1,m);
        for(int i=1;i<=n;i++){
            int p=0;
            int pre=root[i-1];
            int no=tot+1;
            tot++;
            for(char v:g[i]){
                if(ch[p][v-'a']){
                    p=ch[p][v-'a'];
                    merg(pre,no,m,en[p],-1);
                    pre=no;
                    no=tot+1;
                    tot++;
                    en[p]=i;
                }
                else{
                    ch[p][v-'a']=++cnt;
                    en[cnt]=i;
                    p=cnt;
                }
            }
            merg(pre,no,m,i,g[i].size());
            root[i]=no;
        }
        int q;
        scanf("%d",&q);
        int ans=0;
        for(int i=0;i<q;i++){
            int l,r;
            scanf("%d%d",&l,&r);
            int x=l;
            l=min((ans+l)%n,(ans+r)%n)+1;
            r=max((ans+x)%n,(ans+r)%n)+1;
            int w=query(root[r],1,m,l,r);
            printf("%d\n",w);
            ans=w;
        }
    }
}
