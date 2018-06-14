/*
 * @Samaritan_infi 
 */
/// 题目实际上 数据错误 即为0..
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;

int a[110];
int calc() {
	if (a[3] + a[5] - a[6] > a[0]) return 0;
	if (a[3] + a[4] - a[6] > a[1]) return 0;
	if (a[4] + a[5] - a[6] > a[2]) return 0;
	if (a[6] > min(a[3], min(a[4], a[5]))) return 0;
	return a[0] + a[1] + a[2] - a[3] - a[4] - a[5] + a[6];
}

int main() {
	int kase;
	scanf("%d", &kase);
	int ans = 0;
	while (kase--) {
		int n;
		scanf("%d", &n);
		ans = 0;
		for (int i = 0; i < n; i++) {
			for (int i = 0; i < 7; i++)
				scanf("%d", &a[i]);
			ans = max(ans, calc());
		}
		printf("%d\n", ans);
	}
	return 0;
}
