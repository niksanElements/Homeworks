#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int number  = 0;
    cin >> number;
    int step = 1;
    int sum = 0;
    cout << number << " = ";
    do
    {
        sum += pow(2,step);
        int check = number - sum;
        if(check <= 1)
        {
            cout <<"2^" << step << " + ";
            number -= pow(2,step);
            step = 0;
            sum = 0;
        }
        step++;
    }while(number > 1);
    if(1 == number)
    {
        cout << "2^0";
    }
    else
    {
        cout << "0";
    }
    cout << endl;
    return 0;
}
