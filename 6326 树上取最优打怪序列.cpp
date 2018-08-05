/*
 * @Samaritan_infi
 */
/// 堆 + 并差集优化
/// 得到不在树上的最优序列后，然后在树上将，孩子优先打的时候和父亲相融合考虑
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 5;

struct node {
    int id;
    int version = 0;
    ll damage, regen;
    bool judge;
    node() {}
    node(int i, ll d, ll r) {
        id = i;
        damage = d;
        regen = r;
        judge = damage >= regen ? true : false;
        version = 0;
    }
    bool operator < (const node & k) const {
//        judge = damage >= regen ? true : false;
//        if(judge != k.judge) {
//            return judge > k.judge;
//        }
//        if(judge) {
//            return regen < k.regen;
//        }
//        return damage > k.damage;
        int sgn1 = damage < regen, sgn2 = k.damage < k.regen;
        if(sgn1 != sgn2) return sgn1 < sgn2;
        if(damage < regen) return damage > k.damage;
        return regen < k.regen;
    }

    void show() {
        cout << id << " " << damage << " " << regen << " " << version << endl;
    }
};

/// 合并操作很有讲究
void conbine(node &a, node &b) {
    ll damage = max(a.damage, a.damage + b.damage - a.regen);
    ll regen = a.regen + b.regen - a.damage - b.damage + damage;
    //cout << " ?? " << damage << " " << regen << endl;
    a.damage = damage;
    a.regen = regen;
}

node arr[N];
vector<int> edge[N];
int par[N];
bool del[N];
priority_queue<node> que;

void init(int n) {
    while(! que.empty())
        que.pop();
    for(int i = 0; i <= n; i ++) {
        edge[i].clear();
        par[i] = 0;
        del[i] = false;
    }
}

void dfs(int now, int pre) {
    par[now] = pre;
    for(int to : edge[now]) {
        if(to == pre) continue;
        dfs(to, now);
    }
}

int get_par(int x) {
    if(! del[ par[x] ]) return par[x];
    return par[x] = get_par(par[x]);
}

int main() {
    int kase;
    scanf("%d", &kase);
    while(kase --) {
        int n;
        scanf("%d", &n);
        init(n);
        ll l, r;
        arr[1] = node(1, 0, 0);
        for(int i = 2; i <= n; i ++) {
            scanf("%lld %lld", &l, &r);
            arr[i] = node(i, l, r);
            que.push(arr[i]);
        }

        for(int i = 2; i <= n; i ++) {
            scanf("%lld %lld", &l, &r);
            edge[l].emplace_back(r);
            edge[r].emplace_back(l);
        }
        dfs(1, 0);

        while(! que.empty()) {
            node top = que.top();
            //top.show();
            que.pop();
            if(del[top.id]) continue;
            if(top.version != arr[top.id].version) continue;
            int father = get_par(top.id);

            del[top.id] = true;
            conbine(arr[father], arr[top.id]);
            arr[father].version ++;
            //arr[1].show();
            if(father > 1)
                que.push(arr[father]);
        }

        printf("%lld\n", arr[1].damage);
    }
    return 0;
}
/*
2
5
3 6
6 3
1 1
2 1
1 2
1 3
1 5
3 4
5
1 1
2 2
4 5
3 3
1 2
1 3
1 5
3 4
*/
