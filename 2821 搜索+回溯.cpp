/*
 * @Samaritan_infi
 */
///注意细节，wa了5次
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 30;

int n, m;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
char str[] = "LRUD";

char ans[10500];
char temp[maxn];
int pic[maxn][maxn];
int tot;

bool check(int x, int y) {
    if(x < 0 || x >= n || y < 0 || y >= m) return false;
    return true;
}

bool dfs(int x, int y, int deep) {
    if(deep == tot) {
        ans[deep] = 0; return true;
    }
    for(int i = 0; i < 4; i ++) {
        int a = x + dx[i], b = y + dy[i];
        if(!check(a, b) || pic[a][b]) continue;
        while(true) {
            a += dx[i], b += dy[i];
            if(! check(a, b) || pic[a][b]) break;
        }
        if(! check(a, b)) continue;
        int now = pic[a][b];
        pic[ a + dx[i] ][ b + dy[i] ] += now - 1;
        pic[a][b] = 0;
        ans[deep] = str[i];
        if(dfs(a, b, deep + 1)) return true;
        pic[a][b] = now;
        pic[ a + dx[i] ][ b + dy[i] ] -= (now - 1);
    }
    return false;
}

void work() {
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            if(! pic[i][j] && dfs(i, j, 0)) {
                printf("%d\n%d\n%s\n", i, j, ans);
                return;
            }
        }
    }
}

int main() {
    while(~ scanf("%d %d", &m, &n)) {
        memset(pic, 0, sizeof pic);
        tot = 0;
        for(int i = 0; i < n; i ++) {
            scanf("%s", temp);
            for(int j = 0; j < m; j ++) {
                if(temp[j] == '.') pic[i][j] = 0;
                else pic[i][j] = temp[j] - 'a' + 1, tot += pic[i][j];
            }
        }
        work();
    }
    return 0;
}
