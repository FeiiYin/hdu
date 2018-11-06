#include<iostream>
#include<stdio.h> 
#include<algorithm>
#include<string.h>
#include<vector>
#include<set>
#include<math.h>
#include<queue>
#include<map>
#include<stack>
#define go(i,a,b) for (int (i)=(a);(i)<=(b);(i)++)
#define ll long long
#define N 100005
using namespace std;
 
typedef pair<int,int> pii;
vector<pii>e[N];
int a[N],ans;
void dfs(int x, int fx, int y, int fy){
	 if (a[x]!=a[y]) return;
	 if (x<=y) ans++;
	 int j=0;
	 int k=0;
	 go(i,0,e[x].size()-1){
	 	int nx=e[x][i].second;
	 	int ax=e[x][i].first;
	 	if (nx!=fx){
	 		while (j<e[y].size()&&e[y][j].first<ax) j++;
	 		while (k<e[y].size()&&e[y][k].first<=ax)k++;
	 		go(h,j,k){
	 			if (e[y][h].first==ax&&e[y][h].second!=nx&&e[y][h].second!=fy) dfs(nx,x,e[y][h].second,y);
			 }
		 }
	 }
}
int main(){
	int T,n,u,v;
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		go(i,1,n){scanf("%d",&a[i]); e[i].clear(); }
		go(i,1,n-1){
			scanf("%d%d",&u,&v);
			e[u].push_back(make_pair(a[v],v));
			e[v].push_back(make_pair(a[u],u));
		}
		go(i,1,n) sort(e[i].begin(),e[i].end()) ;
		ans=0;
		go(i,1,n){
			dfs(i,0,i,0);
			go(j,0,e[i].size()-1){
				if (a[i]==e[i][j].first) dfs(i,e[i][j].second,e[i][j].second,i);
			}
		}
		printf("%d\n",ans);
	} 
}
