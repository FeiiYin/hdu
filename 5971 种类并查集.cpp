/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = 1005;

int N, M, X, Y;
int a, b;
int ok;
struct node {
    int father, rel;
}F[maxn];
bool vis[maxn];
int kind[maxn];

void init() {
    ok=1;
    memset(kind, -1, sizeof(kind));
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= N; i ++){
        F[i].father = i;
        F[i].rel = 0;
    }
}
int Find(int x) {
    if(F[x].father == x) return x;
    int temp = F[x].father;
    F[x].father = Find(F[x].father);
    F[x].rel = F[x].rel ^ F[temp].rel;
    return F[x].father;
}
bool Uion(int x, int y) {
    int fa, fb;
    fa = Find(x);
    fb = Find(y);
    F[fa].rel = F[x].rel ^ F[y].rel ^ 1;
    if(fa == fb && F[fa].rel != 0) return false;
    if(fa != fb) F[fa].father = fb;
    return true;
}
bool go(int x) {
    int fa = Find(x);
    if(kind[fa] >= 0){
        return kind[fa] ^ kind[x] == F[x].rel;
    }
    else {
        kind[fa]=kind[x]^F[x].rel;
    }
}

int main()
{
    while(~scanf("%d%d%d%d",&N,&M,&X,&Y)){
        init();
        while(M--) {
             scanf("%d%d",&a,&b);
             ok = (ok && Uion(a,b));
             vis[a] = vis[b] = 1;
        }
        while(X--) {
            scanf("%d",&a);
            vis[a] = 1;
            if(kind[a] == 1) ok=0;
            else {
                kind[a]=0;
                ok=(ok&&go(a));
            }
        }
        while(Y--){
            scanf("%d",&a);
            vis[a]=1;
            if(kind[a] == 0)ok=0;
            else {
                kind[a] = 1;
                ok=ok&&go(a);
            }
        }
        for(int i=1;i<=N;i++){
            ok=(ok&&vis[i]);
        }
        if(ok){
              printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }
    return 0;
}
