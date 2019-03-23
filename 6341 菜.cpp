/**
`* @Samaritan
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define PII pair<int, int>
#define mp make_pair
#define pb push_back
#define INF 0x3f3f3f3f
#define fi  first
#define se second

const int N = 20;

int p[N][N], tp[N][N];
char read[N];
/// left up corner (x, y)
//void rot (int x, int y) {
//    for (int i = x; i < x + 4; ++i) {
//        for (int j = y; j < y + 4; ++j) {
//            tp[x+3-j][i] = p[i][j];
//        }
//    }
//    for (int i = x; i < x + 4; ++i) {
//        for (int j = y; j < y + 4; ++j) {
//            p[i][j] = tp[i][j];
//        }
//    }
//}
void rot(int x, int y)//顺时针旋转
{
    int t[5][5];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            t[j][3 - i] = p[x + i][y + j];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            p[x + i][y + j] = t[i][j];
}
void rot_re (int x, int y) {
    for (int i = x; i < x + 4; ++i) {
        for (int j = y; j < y + 4; ++j) {
            tp[j][y+3-i] = p[i][j];
        }
    }
    for (int i = x; i < x + 4; ++i) {
        for (int j = y; j < y + 4; ++j) {
            p[i][j] = tp[i][j];
        }
    }
}
void show (int x, int y) {
    for (int i = x; i < x+4; ++i) {
        for (int j = y; j < y+4; ++j)
            printf("%02d ", p[i][j]);
        printf("\n");
    }
    printf("\n");
}

bool vis[N];
inline bool check (int x, int y) {
    for (int i = x; i < x + 4; ++i) {
        memset(vis, 0, sizeof vis);
        for (int j = 0; j < y + 4; ++j) {
            if (vis[ p[i][j] ]) return false;
            vis[ p[i][j] ] = true;
        }
    }
    for (int j = y; j < y + 4; ++j) {
        memset(vis, 0, sizeof vis);
        for (int i = 0; i < x + 4; ++i) {
            if (vis[ p[i][j] ]) return false;
            vis[ p[i][j] ] = true;
        }
    }
    return true;
}


int ans;


void dfs (int x, int y, int step) {
    //cout << x << " " << y << endl;
    if (x >= 16) {
        ans = min(ans, step);
        return;
    }
    if (step >= ans)
        return;
    /// rotate
    for (int i = 0; i < 4; ++i) {
        if (! check(x, y)) {//cout <<"here: "<< x << " " << y << endl;
            rot(x, y);
            continue;
        }

        if (y + 4 < 16)
            dfs(x, y + 4, step + i);
        else
            dfs(x + 4, 0, step + i);

        rot(x, y);
    }
    /// back
}



int main(){
    int n; scanf("%d", &n);
    while (n--) {
        for (int i = 0; i < 16; ++i) {
            scanf("%s", read);
            for (int j = 0; j < 16; ++j) {
                if (read[j] >= '0' && read[j] <= '9')
                    p[i][j] = read[j] - '0';
                else
                    p[i][j] = read[j] - 'A' + 10;
            }
        }
        ans = 1000;
        dfs(0, 0, 0);
        printf("%d\n", ans);
//        /// test
//        show(0, 0);
//        rot(0, 0);
//        show(0, 0);
//        rot_re(0, 0);
//        show(0, 0);
    }
    return 0;
}
/*
1
681D5A0C9FDBB2F7
0A734B62E167D9E5
5C9B73EF3C208410
F24ED18948A5CA63
39FAED5616400B74
D120C4B7CA3DEF38
7EC829A085BE6D51
B56438F129F79C2A
5C7FBC4E3D08719F
AE8B1673BF42A58D
60D3AF25619C30BE
294190D8EA57264C
C7D1B35606835EAB
AF52A1E019BE4306
8B36DC78D425F7C9
E409492FC7FA18D2
*/

