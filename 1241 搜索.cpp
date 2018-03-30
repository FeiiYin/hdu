/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;

char s[maxn][maxn];
bool vis[maxn][maxn];
int ans;
int n, m;

int dx[] = {0, 0, -1, 1, -1, 1, -1, 1};
int dy[] = {-1, 1, 0, 0,  1, 1, -1, -1};
void bfs(int a, int b) {
    queue< pair<int, int> > pq;
    pq.push(make_pair(a, b));
    while(!pq.empty()) {
        pair<int, int> t = pq.front();
        pq.pop();
        for(int i = 0; i < 8; i ++) {
            int x = t.first + dx[i];
            int y = t.second + dy[i];
            if(x < 0 || y < 0 || x >= n || y >= m) continue;
            if(vis[x][y] || s[x][y] == '*') continue;
            vis[x][y] = true;
            pq.push(make_pair(x, y));
        }
    }
}

int main() {
    while(~ scanf("%d %d", &n, &m)) {
        if(n == 0 && m == 0) break;
        memset(vis, 0, sizeof vis);
        ans = 0;
        for(int i = 0; i < n; i ++) {
            scanf("%s", s[i]);
        }
        for(int i = 0; i < n; i ++) {
            for(int j = 0; j < m; j ++) {
                if(s[i][j] == '*' || vis[i][j]) continue;
                ans ++;
                bfs(i, j);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
