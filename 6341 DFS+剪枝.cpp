/*
 * @Samaritan_infi
 */
/// 经典dfs
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int ord(char c) {
    if (isdigit(c)) return c - '0';
    return c - 'A' + 10;
}

char str(int c) {
    if (c < 10) return c + '0';
    return c + 'A' - 10;
}

int row[16][16], column[16][16];
int a[16][16];
int b[4][4];
char s[16];
int ret;

void add(int ip, int jp, int v) {
    for (int i = ip * 4; i < (ip + 1) * 4; ++i) {
        for (int j = jp * 4; j < (jp + 1) * 4; ++j) {
            row[i][a[i][j]] += v;
            column[j][a[i][j]] += v;
        }
    }
}

bool rot(int ip, int jp) {
    for (int i = ip * 4; i < (ip + 1) * 4; ++i) {
        for (int j = jp * 4; j < (jp + 1) * 4; ++j) {
            --row[i][a[i][j]]; --column[j][a[i][j]];
            b[j - jp * 4][(ip + 1) * 4 - i - 1] = a[i][j];
        }
    }
    bool succ = true;
    for (int i = ip * 4; i < (ip + 1) * 4; ++i) {
        for (int j = jp * 4; j < (jp + 1) * 4; ++j) {
            a[i][j] = b[i - ip * 4][j - jp * 4];
            if ((++row[i][a[i][j]] > 1) || (++column[j][a[i][j]] > 1)) succ = false;
        }
    }
    return succ;
}

void dfs(int ip, int jp, int now) {
    if (ip == 4 && jp == 0) {
        ret = min(ret, now);
        return;
    }
    add(ip, jp, 1);
    if (now >= ret) return;
    for (int i = 1; i <= 4; ++i) {
        if (rot(ip, jp))
            dfs(jp == 3 ? ip + 1 : ip, jp == 3 ? 0 : jp + 1, now + (i & 3));
    }
    add(ip, jp, -1);
}

void solve () {
    for (int i = 0; i < 16; ++i) {
        scanf("%s", s);
        for (int j = 0; j < 16; ++j)
            a[i][j] = ord(s[j]);
    }
    memset(row, 0, sizeof(row));
    memset(column, 0, sizeof(column));
    ret = 16 * 4;
    dfs(0, 0, 0);
    printf("%d\n", ret);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}
