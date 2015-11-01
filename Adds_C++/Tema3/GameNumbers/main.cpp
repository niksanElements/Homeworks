#include <iostream>

using namespace std;

int main()
{
    short number;
    cout << "Enter number with 3 digits:";
    cin >> number;
    short digit1 = ((number/100) * 10) + ((number/10) % 10);
    short digit2 = ((number/100) * 10) + (number%10);
    short digit3 = (((number/10)%10)*10)+ (number%10);
    cout << digit1 << ", " << digit2 << ", " << digit3 << endl;;
    int i = 0;
    while(i < 3)
    {
        int sum = digit1 + digit2;
        if(sum == digit3)
        {
            cout << digit1 << " + " << digit2 << " = " << digit3 << endl;
            break;
        }
        else
        {
            int temp2 = digit1;
            int temp3 = digit3;
            digit1 = digit2;
            digit2 = temp3;
            digit3 = temp2;
        }
        i++;
    }
    return 0;
}
