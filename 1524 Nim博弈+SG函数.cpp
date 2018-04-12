/*
 * @Samaritan_infi
 */
/// NIM博弈  当面对抑或和为0的时候是必败局面
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

template <class T>
void show(T a[], int len) {
    for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}

inline int read() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int maxn = 1005;
vector<int> edge[maxn];

int sg[maxn];
///1.可选步数为1~m的连续整数，直接取模即可，SG(x) = x % (m+1);
///2.可选步数为任意步，SG(x) = x;
///3.可选步数为一系列不连续的数，用GetSG()计算

void cal_sg(int x) {
    if(sg[x] != -1) return;
    sg[x] = 0;
    bool vis[maxn];
    memset(vis, 0, sizeof vis);
    for(int i = 0; i < edge[x].size(); i ++) {
        int to = edge[x][i];
        cal_sg(to);
        vis[ sg[to] ] = true;
    }
    for(int i = 0; i <= 1000; i ++) {
        if(! vis[i]) {
            sg[x] = i;
            return;
        }
    }
}

///如果SG[ stone[i] ] 抑或和为0 为必败状态


int main() {
    int n;
    while(~ scanf("%d", &n)) {
        memset(sg, -1, sizeof sg);
        int t, x;
        for(int i = 0; i < n; i ++) {
            t = read();
            edge[i].clear();
            while(t --) edge[i].push_back(read());
        }
        //cal_sg();
        int q;
        while(~ scanf("%d", &q)) {
            if(! q) break;
            int x, ans = 0;
            while(q --) {
                x = read();
                cal_sg(x);
                ans ^= sg[x];
            }
            if(! ans) puts("LOSE");
            else puts("WIN");
        }
    }
    return 0;
}
