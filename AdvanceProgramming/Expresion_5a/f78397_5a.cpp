#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double f(double x)
{
    return 2*x*x*x - 7*x - 97;   //f78397
}

bool biseccion(double a, double b, double tolerancia)
 {
        double c = 0;
        do
        {
            c=(a+b)/2;
            if(f(a)*f(c)<0)
            {
               b=c;
            }
            else if(f(b)*f(c) < 0)
            {
               a=c;
            }
            else
            {
                cout << "NO SOLUTION";
                return false;
            }
         }
         while(abs(f(c)) > tolerancia);
         cout << setprecision(11) << c  << ' '
        << setprecision(11) << fixed << f(c) << endl;
         return true;
}

int main()
{
    double tolerance = 10e-10;
    biseccion(-10,10,tolerance);
;
}
