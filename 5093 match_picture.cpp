/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
//#include <cstdio>
using namespace std;
typedef long long LL;

const int N = 1e2 + 5;
const int INF = 0x3f3f3f3f;

#define PII pair<int, int>
#define fi first
#define se second
#define pb push_back


int x[N][N], y[N][N];
char pic[N][N];

const int M = 3e3 + 5;
vector <int> edge[M];

int mark[M], match[M];
bool dfs (int x) {
    for (int to : edge[x]) {
        if (mark[to]) continue;
        mark[to] = true;
        if (match[to] == -1 || dfs(match[to])) {
            match[to] = x;
            match[x] = to;
            return true;
        }
    }
    return false;
}

int hag (int n, int m) {
    int tot = n + m;
    int siz = sizeof (match[0]) * (tot + 3);
    memset(match, -1, siz);
    int ans = 0;
    // cout << n << " " << m << endl;
    for (int i = 1; i <= n; ++i) {
        if (match[i] == -1) {
            memset(mark, 0, siz);
            if (dfs(i))
                ans++;
        }
    }

//    for (int i = 1; i <= n; ++i)
//        cout << match[i] << " "; cout << endl;
    return ans;
}

int main () {
    int kase; scanf("%d", &kase);
    while (kase--) {
        int n, m;
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; ++i) {
            scanf("%s", &pic[i]);
//            for (int j = 0; j < m; ++j) {
//                if (arr[j] == '*')
//                    pic[i][j] = 1;
//                else if (arr[j] == '#')
//                    pic[i][j] = 2;
//                else
//                    pic[i][j] = 0;
//            }
        }

        int x_cnt = 1;
        bool flag = false;
        memset(x, 0, sizeof x);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (pic[i][j] == '#' && flag) {
                    x_cnt++, flag = false;
                }
                else if (pic[i][j] == '*')
                    x[i][j] = x_cnt, flag = true;
            }
            if (flag)
                x_cnt++, flag = false;
        }

        int y_cnt = 1;
        memset(y, 0, sizeof y);
        flag = false;
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i) {
                if (pic[i][j] == '#' && flag)
                    y_cnt++, flag = false;
                else if (pic[i][j] == '*')
                    y[i][j] = y_cnt, flag = true;
            }
            if (flag)
                y_cnt++, flag = false;
        }

        for (int i = 1; i <= x_cnt; ++i)
            edge[i].clear();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (pic[i][j] == '*')
                    edge[ x[i][j] ].push_back(x_cnt + y[i][j]);
            }
        }

//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < m; ++j) {
//                cout << x[i][j] << " ";
//            }cout << endl;
//        }
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < m; ++j) {
//                cout << y[i][j] << " ";
//            }cout << endl;
//        }
        int ans = hag(x_cnt - 1, y_cnt - 1);
        printf("%d\n", ans);
    }
    return 0;
}
