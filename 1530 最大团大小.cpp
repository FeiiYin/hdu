/*
 * @Samaritan_infi
 */
/// 最大团大小，搜索+dp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}

const int maxn = 110, maxm = 3e4 + 5;
const int inf = 2147483640;

int pic[maxn][maxn];
int dp[maxn]; /// i to n 最大团的结点数
int clique_size;
int que[maxn][maxn];
int n;
void dfs(int pos, int deep) {
    if(! pos) {
        clique_size = max(clique_size, deep);
//        for(int i = 0; i <= n; i ++) {
//            for(int j = 0; j <= n; j ++)
//                cout << que[i][j]<< " ";
//            cout << endl;
//        }
        return;
    }
    for(int i = 0; i < pos; i ++) {
        int k = que[deep][i];
        if(deep + n + 1 - k <= clique_size) return;
        if(deep + dp[k] <= clique_size) return;

        int cnt = 0;
        for(int j = i + 1; j < pos; j ++)
            if(pic[k][ que[deep][j] ])
                que[deep + 1][cnt ++] = que[deep][j];
        dfs(cnt, deep + 1);
    }
}

void work() {
    clique_size = 1;
    dp[n] = 1;
    for(int i = n - 1; i >= 1; i --) {
        int pos = 0;
        for(int j = i + 1; j <= n; j ++)
            if(pic[i][j]) que[1][pos ++] = j;
        dfs(pos, 1);
        dp[i] = clique_size;

    }
}

int main() {

    while(~ scanf("%d", &n) && n) {
        for(int i = 1; i <= n; i ++) {
            for(int j = 1; j <= n; j ++) {
                pic[i][j] = read();
            }
        }
        work();
        printf("%d\n", clique_size);
    }
    return 0;
}
