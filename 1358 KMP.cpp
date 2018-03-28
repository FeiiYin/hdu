/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6 + 5;
int kmp_next[maxn];
char read[maxn];

void get_next(char s[], int len) {
    int i = 0, j = -1;
    kmp_next[i] = j;
    ///sb 数据，给的串有问题
    while(i < len) {
        if(j == -1 || s[i] == s[j])
            i ++, j ++, kmp_next[i] = j;
        else
            j = kmp_next[j];
    }
}

int main() {
    int n;
    int ca = 1;
    while(scanf("%d", &n) && n) {
        scanf("%s", read);
        get_next(read, n);
        printf("Test case #%d\n", ca ++);
//        for(int i = 0; i <= strlen(read); i ++)
//            cout << kmp_next[i] << " "; cout << endl;
		for(int i = 2; i <= n; i ++) {
            if(i % (i - kmp_next[i])==0&&i/(i-kmp_next[i])!=1) {
                printf("%d %d\n", i, i/(i-kmp_next[i]));
            }
		}
		puts("");
    }
    return 0;
}
