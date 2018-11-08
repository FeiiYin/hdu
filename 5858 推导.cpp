#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<math.h>
using namespace std;
const double PI=acos(-1.0);
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        double l;
        scanf("%lf",&l);
        double ans=acos((double)(5*sqrt(2)*1.0)/8.0);
        ans=ans*1.0/PI*180.0;
        ans*=2;
        double shan1=ans*1.0/360*1.0*PI*l*l;
        double sanjiaoxing=sqrt(7*1.0/32*1.0)*5*sqrt(2.0)/8.0*l*l;
        double xiaogongxing=shan1-sanjiaoxing;
        double ans2=acos((double)(-sqrt(2)*1.0/4.0));
        ans2=ans2/PI*180.0;
        ans2=180-ans2;
        ans2*=2;
        double shan2=ans2*1.0/360*1.0*PI*(l*1.0/2*1.0)*(l*1.0/2*1.0);
        double sanjiaoxing2=sqrt(7*1.0/32*1.0)*sqrt(1*1.0/32*1.0)*l*l;
        double dagongxing=(shan2-sanjiaoxing2);
        printf("%.2lf\n",2*(dagongxing-xiaogongxing));
    }
}
