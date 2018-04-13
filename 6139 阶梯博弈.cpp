/*
 * @Samaritan_infi
 */
/// NIM博弈  当面对抑或和为0的时候是必败局面
/// 切比雪夫距离 max(|x1-x2|,|y1-y2|) 棋盘距离
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

int sg[maxn];
///1.可选步数为1~m的连续整数，直接取模即可，SG(x) = x % (m+1);
///2.可选步数为任意步，SG(x) = x;
///3.可选步数为一系列不连续的数，用GetSG()计算



///如果SG[ stone[i] ] 抑或和为0 为必败状态


int main() {
    int kase = read();
    while(kase --) {
        int n, m, t;
        //int n = read(), m = read(), t = read();
        scanf("%d %d %d", &n, &m, &t);
        int ans = 0, k = (n ^ m) % 2, x, y, z;
        while(t --) {
            //x = read(), y = read(), z = read();
            scanf("%d %d %d", &x, &y, &z);
            if((x ^ y ^ k) & 1) ans ^= z;
        }
        t = read(); while(t --) scanf("%d %d", &x, &y); //x = read(), y = read();
        t = read(); while(t --) scanf("%d %d", &x, &y); //x = read(), y = read();
        printf("%s\n", ans ? "win" : "lose");
    }
    return 0;
}
