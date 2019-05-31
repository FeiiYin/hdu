/// reference: http://www.matrix67.com/blog/archives/5900
/**
 * @Samaritan
 */
#include <bits/stdc++.h>
using namespace std;
#define PII pair<int, int>
#define fi first
#define se second

const int N = 2e3 + 5;
const int M = 20;
const int INF = 0x7fffffff;

int main ()
{
    int n, m, kase;
    scanf("%d", &kase);
    while (kase--) {
        scanf("%d %d", &n, &m);
        int r = n % m;
        if (n < m) {
            /// zero 
            r = n*n;
        } else if (r <= m/2) {
            r *= r;
        } else {
            /// (r+m)*(r+m) -> (m-r)*(m-r)
            /**
                5 3
                ---||
                ---||
                ||*||
                ||---
                ||---
            */
            r = (m-r)*(m-r);
        }
        printf("%d\n", n*n-r);
    }
    return 0;
}


