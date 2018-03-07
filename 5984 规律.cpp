#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 505 ;

int main(){
    int kase ;
    scanf("%d" , &kase) ;
    while(kase --){
        double a , b ;
        scanf("%lf %lf" , &a , &b) ;
        if(a <= b) printf("%.6f\n" , 0) ;
        else printf("%.6f\n" , log(a / b) + 1) ;
    }
    return 0 ;
}
