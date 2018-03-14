/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

int ex_gcd(int a , int b , int &x , int &y) {
    if(b == 0) {
        x = 1 ; y = 0 ;
        return a ;
    }
    int r = ex_gcd(b , a % b , x , y) ;
    int t = x ; x = y ; y = t - a / b * y ;
    return r ;
}

int main() {
    int kase ; scanf("%d" , &kase) ;
    while (kase --) {
        int n ,b , m = 9973, x , y ;
        scanf("%d %d" , &n , &b) ;
        ex_gcd(b , m , x , y) ;
        x = (x % m + m) % m ;
        cout << (x * n) % m << endl ;
    }
    return 0 ; 
}
