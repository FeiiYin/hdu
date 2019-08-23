1 pos, a[pos] += INF
2 pos, k, query ans != (1, pos)'s val && ans >= k
    -> query ans : k <= ans <= n+1 && ans_pos > pos

/**
`* @Samaritan
 */
#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;
#define PII pair<int, int>
#define mp make_pair
#define pb push_back
#define INF 0x3f3f3f3f
#define fi  first
#define se second

inline int get_rand_int (int low, int up) {
  int dif = up - low;
  int a = rand() % dif;
  return low + a;
}

#define enlarge 1000000
inline LL get_rand_ll (LL low, LL up) {
  LL dif = up - low;
  LL a = (LL)rand() * enlarge % dif;
  return low + a;
}

struct node {
    int x, y;
    int id;
    node () {}
    node (int x, int y, int id) : x(x), y(y), id(id) {}
    bool operator < (const node &k) const {
      return x < k.x;
    }
};

#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r
const int N = 1e5 + 5;
int arr[N], ori[N];
int tree[N << 2];
void push_up (int rt) {
  tree[rt] = max(tree[rt<<1], tree[rt<<1|1]);
}
void build (int rt, int l, int r) {
  if (l == r) {
    tree[rt] = arr[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(lson);
  build(rson);
  push_up(rt);
}

/// delete a, make a INF
void update (int rt, int l, int r, int pos) {
  if (l == r) {
    tree[rt] = INF;
    return;
  }
  int mid = (l + r) >> 1;
  if (pos <= mid)
    update(lson, pos);
  else
    update(rson, pos);
  push_up(rt);
}
/// (1 - R) not appear, Kth
int ans;
void query (int rt, int l, int r, int pos, int L, int R) {
  if (l == r) {
    ans = min(l, ans);
    return;
  }
  int mid = (l + r) >> 1;
  if (mid >= L && tree[rt<<1] > pos) {
    query(lson, pos, L, R);
  }
  if (ans == INF && mid < R && tree[rt<<1|1] > pos) {
    query(rson, pos, L, R);
  }
}


int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int n, q, x;
    scanf("%d %d", &n, &q);
    n++;
    for (int i = 1; i < n; ++i) {
      scanf("%d", &ori[i]);
      arr[ ori[i] ] = i;
    }
    arr[n] = INF;
    build(1, 1, n);

    int lastans = 0;
    while (q--) {
      int op;
      scanf("%d", &op);
      if (op == 1) {
        int pos;
        scanf("%d", &pos);
        pos ^= lastans;
//        cout << "pos: " << pos << endl;
        update(1, 1, n, ori[pos]);
      } else {
        int r, k;
        scanf("%d %d", &r, &k);
        r ^= lastans;
        k ^= lastans;
//        cout << "r,k: " << r << " " << k << endl;
        ans = INF;
        query(1, 1, n, r, k, n);
        printf("%d\n", ans);
        lastans = ans;
      }
    }
  }
  return 0;
}
/*

 */
