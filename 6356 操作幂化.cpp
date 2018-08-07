/*
 * @Samaritan_infi
 */
/// 所有的操作区间都变为2的幂次，即 (l, r) --> (l, l + 2^d) & (r - 2^d, r) (d 尽可能的大)
/// 然后更新完成后从最上面一层一层的向下，这样复杂度是 nlogn 的
/// 向下的时候 因为上面一层是下面一层的两倍，所以 更新 a[i-1][j] a[i-1][j + (1<<(i-1))]
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5, maxd = 17;

int Log[N], a[maxd][N];

unsigned int X, Y, Z;
unsigned int rng61() {
	X ^= X << 11;
	X ^= X >> 4;
	X ^= X << 5;
	X ^= X >> 14;
	unsigned int tmp = X ^ Y ^ Z;
	X = Y;
	Y = Z;
	Z = tmp;
	return Z;
}

inline void upd(int &x, int y) {
	if(x < y)
        x = y;
}

int main() {
	for(int i = 2; i < N; ++i)
		Log[i] = Log[i >> 1] + 1;
    int kase;
	scanf("%d", &kase);
	while(kase --) {
		int n, m;
		scanf("%d %d %u %u %u", &n, &m, &X, &Y, &Z);
		int mx;
		for(mx = 0; 1 << mx <= n; ++mx);
		while(m --) {
			int L = rng61() % n + 1, R = rng61() % n + 1, v = rng61() & ((1 << 30) - 1);
			if(L > R)
				swap(L, R);
			int d = Log[R - L + 1];
			upd(a[d][L], v);
			upd(a[d][R - (1 << d) + 1], v);
		}
		for(int i = mx - 1; i > 0; --i)
			for(int j = 1; j + (1 << i) - 1 <= n; ++j) {
				upd(a[i - 1][j], a[i][j]);
				upd(a[i - 1][j + (1 << (i - 1))], a[i][j]);
				a[i][j] = 0;
			}
		ll ans = 0;
		for(int i = 1; i <= n; ++i) {
			ans ^= (ll)i * a[0][i];
			a[0][i] = 0;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
