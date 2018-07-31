/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 55;
const int maxm = 105;
const int inf = 1000000000;

int n;
int f[maxn][maxn], a[maxm][maxn][maxn], b[maxm][maxn][maxn], d[maxn][maxn];
int graph[maxn][maxn];

inline void update(int &a, int b) { if(a > b) a = b; }

inline void mul(int a[][maxn], int b[][maxn], int c[][maxn]){
    static int f[maxn][maxn];
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < n; j ++) {
            f[i][j] = inf;
            for(int k = 0; k < n; k ++)
                update(f[i][j], a[i][k] + b[k][j]);
        }
    }
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
            c[i][j] = f[i][j];
}

int main(){
    int kase;
    scanf("%d", &kase);
    while(kase --) {
        int m;
        scanf("%d %d", &n, &m);
        for(int i = 0; i < n; i ++) {
            for(int j = 0; j < n; j ++)
                graph[i][j] = inf;
        }
        int l, r, x;
        while(m --) {
            scanf("%d %d %d", &l, &r, &x);
            l --; r --;
            update(graph[l][r], x);
        }
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < n; j ++)
                a[0][i][j] = b[0][i][j] = (i == j ? 0 : inf);

        /// a 现在是恰好经过i条边的最短路，b 是恰好经过i百条边的最短路
        for(int i = 1; i < maxm; i ++)
            mul(a[i - 1], graph, a[i]);
        for(int i = 1; i < maxm; i ++)
            mul(b[i - 1], a[100], b[i]);

        for(int i = 0; i < n; i ++)
            for(int j = 0; j < n; j ++)
                d[i][j] = (i == j ? 0 : graph[i][j]);

        /// floyd
        for(int k = 0; k < n; k ++)
            for(int i = 0; i < n; i ++)
                for(int j = 0; j < n; j ++)
                    update(d[i][j], d[i][k] + d[k][j]);
        
        /// 这里a和b 求至少皆可，因为答案是枚举的
        /// 计算至少x条边的最短路，即为恰好x条边在做一次floyd
        for(int x = 0; x < maxm; x ++) {
            for(int i = 0; i < n; i ++)
                for(int j = 0; j < n; j ++)
                    f[i][j] = inf;

            /// 不直接用b进行floyd， 是因为a的每一个是恰好的，而d是至少的，得到的不是正确结果
            for(int i = 0; i < n; i ++)
                for(int j = 0; j < n; j ++)
                    for(int k = 0; k < n; k ++)
                        update(f[i][j], a[x][i][k] + d[k][j]);

            for(int i = 0; i < n; i ++)
                for(int j = 0; j < n; j ++)
                    a[x][i][j] = f[i][j];
        }


        int op;
        scanf("%d", &op);
        while(op --) {
            scanf("%d %d %d", &l, &r, &x);
            l --, r --;
            int A = x % 100, B = x / 100;
            int ans = inf;
            for(int i = 0; i < n; i ++)
                update(ans, a[A][l][i] + b[B][i][r]);
            if(ans >= inf) ans = -1;
            printf("%d\n", ans);
        }
    }
}
