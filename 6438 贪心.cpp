/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

priority_queue< pair<int, int> > pq;

int main() {
    int kase; scanf("%d", &kase);
    while (kase --) {
        int n, val; scanf("%d", &n);
        ll ans = 0, step = 0;
        for (int i = 0; i < n; i ++) {
            scanf("%d", &val);
            pq.push(make_pair(-val, 1)); /// 买入
            pq.push(make_pair(-val, 2)); /// 卖出  先弹2
            ans += val + pq.top().first;
            //cout << val << " " << pq.top().first << endl;
            if (pq.top().second == 1) step += 2;
            pq.pop();
        }
        while (! pq.empty()) pq.pop();
        printf("%lld %lld\n", ans, step);
    }
    return 0;
}
