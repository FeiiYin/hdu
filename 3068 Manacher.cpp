/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6 + 5;
//int kmp_next[maxn];
//int kmp[maxn];
//
//
//void get_next(int s[], int len) {
//    int i = 0, j = -1;
//    kmp_next[i] = j;
//    while(i < len) {
//        if(j == -1 || s[i] == s[j])
//            i ++, j ++, kmp_next[i] = j;
//        else
//            j = kmp_next[j];
//    }
//}
//
//void work_kmp(int s[], int t[], int s_len, int t_len) {
//    int i = 0, j = 0;
//    while(i < s_len) {
//        if(j == -1 || s[i] == t[j])
//            i ++, j ++, kmp[i] = j;
//        else
//            j = kmp_next[j];
//    }
//}
//
//void show(char a[], int len) {
//for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
//}


char now[maxn * 2];
int p[maxn * 2]; //palindrome
int Manacher(char s[], int len) {
    //int len = strlen(s);
    for(int i = 0; i < len; i ++) now[1 + (i << 1)] = '#', now[2 + (i << 1)] = s[i];
    now[len = 1 + (len << 1)] = '#';
    int R = 0, pos = 0;
    for(int i = 1; i < len; i ++) {
        if(i < R) {
            p[i] = min(R - i, p[-i + (pos << 1)]);
        } else {
            p[i] = 1;
        }
        while(1 <= i - p[i] && i + p[i] <= len && now[ i - p[i] ] == now[ i + p[i] ]) p[i] ++;
        if(i + p[i] > R) R = i + p[i], pos = i;
    }
    int ans = 0;
    for(int i = 1; i < len; i ++) ans = max(ans, p[i] - 1);
    return ans;
}


char read[maxn];

int main() {
    //int kase; scanf("%d", &kase);
    while(~ scanf("%s", read) ) {
        int len = strlen(read);
        printf("%d\n", Manacher(read, len));
    }
    return 0;
}
