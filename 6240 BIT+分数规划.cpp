/*
 * @Samaritan_infi
 */
///分数规划出mid
///求最小值，所以如果存在一组ai，bi使 ai-mid*bi <= 0 即说明 mid >= 最小值，因为最小值可以取 ai/bi
///然后找出该ai，bi，贪心，选取所有的负的，然后是个dp用BIT维护，找出剩下的正的值能覆盖剩下的区间
///金牌题
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 100007 ;
const double eps = 1e-4 ;
const int inf = 0x3f3f3f3f ;
struct node{
    int a , b , s , t ;
    bool vis ;
    bool operator < (const node & k) const {
        if(s == k.s) return t < k.t ;
        return s < k.s ;
    }
};
node save[maxn] ;
double val[maxn] ;

int n , t ;

double tree[maxn] ;
int low_bit(int x){
    return x & (-x) ;
}

void update(int i , double val){
    for( ; i > 0 ; i -= low_bit(i)) tree[i] = min(tree[i] , val) ;
}

double query(int i){
    if(i == 0) return 0 ; ///注意特判， 因为low_bit(0) = 0 会死循环
    double ans = 1e9 ;
    for( ; i <= t ; i += low_bit(i)) ans = min(ans , tree[i]) ;
    return ans ;
}

bool check(double mid){
    double sum = 0.0 ;
    int start = 0 ;
    for(int i = 1 ; i <= n ; i ++){
        val[i] = save[i].a - save[i].b * mid ;
        if(val[i] <= 0){
            sum += val[i] ;
            save[i].vis = true ;
            if(save[i].s - 1 <= start)
                start = max(start , save[i].t) ;
        }else
            save[i].vis = false ;
    }
    if(start == t) return true ;

    ///memset(tree , inf , sizeof(tree)) ; double 不能memset 注意
    for(int i = 1 ; i <= t ; i ++) tree[i] = 1e9 ;
    update(start , 0) ;

    //for(int i = 0 ; i <= n ; i ++) cout << tree[i] << " "; cout << endl ;
    double temp ;
    for(int i = 1 ; i <= n ; i ++){
        if(save[i].vis == true){
            temp = query(save[i].s - 1) ;
            update(save[i].t , temp) ;
        }else{
            temp = query(save[i].s - 1) + val[i] ;
            update(save[i].t , temp) ;
        }
    }
    temp = query(t) ;
    return sum + temp <= 0 ;
}
int main(){

    int kase ; scanf("%d" , &kase) ;
    while(kase --){
        scanf("%d %d" , &n , &t) ;
        for(int i = 1 ; i <= n ; i ++){
            scanf("%d %d %d %d" , &save[i].s, &save[i].t, &save[i].a, &save[i].b) ;
        }
        sort(save + 1 , save + n + 1) ;
        //for(int i = 1 ; i <= n ; i ++) cout << save[i].s << " " << save[i].t << endl ;

        double l = 0 , r = 1001 ;
        while(r - l > eps){
            double mid = (l + r) / 2 ;
            if(check(mid)) r = mid ;
            else l = mid ;
        }
        printf("%.3f\n" , l) ;
    }
    return 0 ;
}
