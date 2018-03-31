/*
 * @Samaritan_infi
 */


#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 10;

const int n = 7, m = 8;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
char str[] = "LRUD";

char temp[maxn];
int pic[maxn][maxn];
int num;

struct node {
    int a, b;
    char v;
    node() {}
    node(int i, int j, char c) {a = i, b = j, v = c;}
};
node ans[maxn * 100];
int ans_num;

bool check(int i, int j) {
    if(i < 0 || j < 0 || i >= n || j >= m) return false;
    return true;
}

void show() {
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++)
            cout << pic[i][j] << " "; cout << endl;
    }
}

bool dfs(int a, int b, int deep) {
    //cout << a << " " << b << " " << deep << endl;
    if(deep == num - 1) {
        return true;
    }
    pic[a][b] = 0;
    for(int i = 0; i < 4; i ++) {
        int x = a + dx[i], y = b + dy[i];
        if(! check(x, y) || pic[x][y]) continue;

        int box_num = 0;
        int now_x, now_y;
        for(now_x = x, now_y = y; check(now_x, now_y); now_x += dx[i], now_y += dy[i]) {
            //cout << x << " " << y << " " << now_x << " " << now_y << endl;
            if(pic[now_x][now_y]) {
                box_num ++;
                pic[ now_x - dx[i] ][ now_y - dy[i] ] = 1;
                pic[now_x][now_y] = 0;
            }
        }
        if(! box_num) continue;

        ans[ans_num ++] = node(a, b, str[i]);

        for(int in_i = 0; in_i < n; in_i ++) {
            for(int in_j = 0; in_j < m; in_j ++) {
                if(! pic[in_i][in_j]) continue;
                if(dfs(in_i, in_j, deep + 1)) return true;
            }
        }


        ans_num --;
        /// 不能只判断now_x或者now_y，可能同一行
        for( ; now_x != x || now_y != y; now_x -= dx[i], now_y -= dy[i]) {
            if(pic[ now_x - dx[i] ][ now_y - dy[i] ]) {
                pic[now_x][now_y] = 1;
                pic[ now_x - dx[i] ][ now_y - dy[i] ] = 0;
            }
        }
    }
    pic[a][b] = 1;
    return false;
}

int main() {
    int tt = 1;
    while(~ scanf("%s", temp)) {
        memset(pic, 0, sizeof pic);
        queue< pair<int, int> > pq;
        num = 0;
        ans_num = 0;
        for(int i = 0; i < m; i ++) {
            if(temp[i] == 'O')  pic[0][i] = 1, pq.push(make_pair(0, i)), num ++;
        }
        for(int i = 1; i < n; i ++) {
            scanf("%s", temp);
            for(int j = 0; j < m; j ++) {
                if(temp[j] == 'O') pic[i][j] = 1, pq.push(make_pair(i, j)), num ++;
            }
        }



        while(! pq.empty()) {
            pair<int, int> node = pq.front();
            pq.pop();
            if(dfs(node.first, node.second, 0)) {
                break;
            }
        }
        if(tt > 1) puts("");
        printf("CASE #%d:\n", tt ++);
        for(int i = 0; i < ans_num; i ++) {
            printf("%d %d %c\n", ans[i].a, ans[i].b, ans[i].v);
        }
    }
    return 0;
}
