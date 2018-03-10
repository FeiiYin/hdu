/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const double pi = acos(- 1.0) ;
const double epx = 1e-10 ;
double check(double x) {
    double y = acos(2 * tan(x) - 1) ;
    double a1 , a2 ;
    a1 = pi * cos(y) - y * cos(y) + sin(y) - (1.0 / 3) * sin(y) * sin(y) * sin(y) ;
    y = pi ;
    a2 = pi * cos(y) - y * cos(y) + sin(y) - (1.0 / 3) * sin(y) * sin(y) * sin(y) ;
    return (1.0 / tan(x)) * (a1 - a2) ;
}
double work(double L) {
    double l = 0.0 , r = pi / 4.0 ;
    double mid ;
    while (r - l > epx) {
        mid = (l + r) / 2 ;
        if(check(mid) > L) r = mid ;
        else l = mid ;
    }
    return mid ;
}
int main(){
    int kase ;
    scanf("%d" , &kase) ;
    while (kase --) {
        double a , b , c , x , y ;
        scanf("%lf" , &a) ;
        if(a == 0) printf("%.5f\n" , 0.0) ;
        else if( a >= 1.0 ) {
            b = 2.0 - a ;
            b = sqrt(1 + b * b) ;
            printf("%.5f\n" , b * pi) ;
        } else {
            x = work(a * pi) ;
            y = acos(2 * tan(x) - 1) ;
            y = pi - y + cos(y) * sin(y) ;
            printf("%.5f\n" , y / sin(x)) ;
        }
    }
    return 0;
}
