/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

inline int read() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

const int maxn = 1e5 + 5;
const int mod = 998244353;


int main() {
    int kase = read();
    while(kase --) {
        int n = read(), op = read();
        int num_1 = 0, num_2 = 0, x;
        for(int i = 1; i <= n; i ++) {
            x = read();
            if(x == 1) num_1 ++;
            else num_2 ++;
        }
        if(num_1 == n) {
            if(op == 1) {
                if(n % 3 == 0) puts("No");
                else puts("Yes");
            } else {
                if(n % 3 == 1) puts("No");
                else puts("Yes");
            }
        } else if(num_1 == n - 1) {
            if(op == 2 && n % 3 == 2) puts("Yes");
            if(op == 1) puts("Yes");
            else puts("No");
        } else {
            puts("Yes");
        }
    }
    return 0;
}
