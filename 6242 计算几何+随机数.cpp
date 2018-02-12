/*
 * @Samaritan_infi
 */
///由于题目求一半的点距离某个点的距离相等，且一定存在
///反过来想，如果随机从给出的点任取一个点，即它在圆上的概率大于1/2
///所以每次任意取出3个点，不在圆上的概率为7/8，那么大约100次后，概率为1e-6
///注意点数小于等于4时特判，因为此时只要两个点距离相等就行，所以不一定存在圆
#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;

const double eps = 1e-6 ;
const int maxn = 1e5 + 5 ;

struct Point{
    double x , y ;
    Point() {} ;
    Point(double _x,double _y):x(_x),y(_y) {};
    Point operator -(const Point &b) const{
        return Point(x - b.x,y - b.y);
    }
    double operator *(const Point &b)const{
        return x*b.x + y*b.y;
    }
};
Point save[maxn] ;

//两点距离
double Distance(Point a,Point b){
    return sqrt((a-b)*(a-b));
}
//三角形的外心
Point CircumCenter(Point a , Point b , Point c){
    Point cp;
    double a1 = b.x-a.x,b1 = b.y-a.y,c1 = (a1*a1 + b1*b1)/2;
    double a2 = c.x-a.x,b2 = c.y-a.y,c2 = (a2*a2 + b2*b2)/2;
    double d = a1*b2 - a2*b1;
    cp.x = a.x + (c1*b2-c2*b1)/d;
    cp.y = a.y + (a1*c2-a2*c1)/d;
    return cp;
}

int random(int n){
    return ((rand() % n) + (rand() % n) + n) % n ;
}

bool check(Point center , int n , double r){
    int num = 0 ;
    for(int i = 0 ; i < n ; i ++){
        if(fabs(Distance(center , save[i]) - r) < eps) num ++ ;
    }
    return num >= (n + 1) >> 1 ;
}

void output(double a , double b , double c){
    printf("%.12f %.12f %.12f\n" , a , b , c) ;
}

int main(){
    int kase ; scanf("%d" , &kase) ;
    while(kase --){
        int n ; scanf("%d" , &n) ;
        for(int i = 0 ; i < n ; i ++){
            scanf("%lf %lf" , &save[i].x , &save[i].y) ;
        }
        if(n == 1){
            output(save[0].x , save[0].y , 0) ;
            continue ;
        }
        if(n <= 4){
            double x = (save[0].x + save[1].x) / 2 ;
            double y = (save[0].y + save[1].y) / 2 ;
            double r = Distance(save[0] , save[1]) / 2 ;
            output(x , y , r) ;
            continue ;
        }
        while(true) {
            int x = random(n) , y = random(n) , z = random(n) ;
            while(y == x) y = random(n) ;
            while(z == x || z == y) z = random(n) ;
            Point center = CircumCenter(save[x] , save[y] , save[z]) ;
            if(center.x > 1e9 || center.y > 1e9) continue ;
            double r = Distance(save[x] , center) ;
            if(check(center , n , r)) {
                output(center.x , center.y , r) ;
                break ;
            }
        }
    }
    return 0 ;
}
