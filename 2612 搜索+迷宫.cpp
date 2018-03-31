/*
 * @Samaritan_infi
 */

///注意搜索路径的时候两个起点各自搜的路径不能经过对方路径，把对方先变成墙，再搜
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 210;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
char str[] = "LRUD";

int pic[maxn][maxn];
int num_a[maxn][maxn], num_b[maxn][maxn];

char temp[maxn];

struct node {
    int a, b, v;
    node() {}
    node(int i, int j, int c) {a = i, b = j, v = c;}
};
int n, m;
bool check(int i, int j) {
    if(i < 0 || j < 0 || i >= n || j >= m) return false;
    return true;
}

bool vis[maxn][maxn];
void bfs(int a, int b, int num[][maxn]) {
    queue<node> pq;
    memset(vis, 0, sizeof vis);
    vis[a][b] = true;
    pq.push(node(a, b, 0));
    while(! pq.empty()) {
        node now = pq.front(); pq.pop();
        for(int i = 0; i < 4; i ++) {
            int x = now.a + dx[i], y = now.b + dy[i];
            if(! check(x, y) || pic[x][y] == 1 || vis[x][y]) continue;
            vis[x][y] = true;
            num[x][y] = now.v + 1;
            pq.push(node(x, y, now.v + 1));
        }
    }
}
vector< pair<int, int> > save;
int main() {

    while(~ scanf("%d %d", &n, &m)) {
        pair<int, int> point_a, point_b;
        memset(pic, 0, sizeof pic);
        memset(num_a, 0, sizeof num_a);
        memset(num_b, 0, sizeof num_b);
        save.clear();
        for(int i = 0; i < n; i ++) {
            scanf("%s", temp);
            for(int j = 0; j < m; j ++) {
                if(temp[j] == 'Y') point_a = make_pair(i, j);
                else if(temp[j] == 'M') point_b = make_pair(i, j);
                else if(temp[j] == '#') pic[i][j] = 1;
                else if(temp[j] == '@') save.push_back(make_pair(i, j));
            }
        }
        pic[point_b.first][point_b.second] = 1;
        bfs(point_a.first, point_a.second, num_a);
        pic[point_b.first][point_b.second] = 0;
        pic[point_a.first][point_a.second] = 1;
        bfs(point_b.first, point_b.second, num_b);
        int ans = 1e9;
        for(int i = 0; i < save.size(); i ++) {
            int a = save[i].first, b = save[i].second;
            if((!num_a[a][b]) || (!num_b[a][b])) continue;
            ans = min(ans, num_a[a][b] + num_b[a][b]);
        }
        printf("%d\n", ans * 11);
    }
    return 0;
}
