#include <iostream>

using namespace std;

struct pir
{
    int num1;
    unsigned int num2;
};

int NOK(int num1,int num2)
{
    if(num1 % num2 == 0)
    {
        return num2;
    }
    return NOK(num2,num1 % num2);
}

pir SumFaction(pir frac_1,pir frac_2)
{
    pir result;
    result.num2 = frac_1.num2 * frac_2.num2;
    result.num1 = (frac_1.num1 * frac_2.num2) + (frac_2.num1 *frac_1.num2);
    int result_nok = NOK(result.num1,result.num2);
    result.num1 /= result_nok;
    result.num2 /= result_nok;
    return result;
}

int main()
{
    pir fraction_1,fraction_2;
    char c;
    while(cin >> fraction_1.num1>>c>>fraction_1.num2>>c>>fraction_2.num1>>c>>fraction_2.num2)
    {
        pir result = SumFaction(fraction_1,fraction_2);
        if(result.num2 == 1)
        {
            cout << result.num1 << endl;
        }
        else
        {
            cout << result.num1 << "/" << result.num2<<endl;
        }
    }
}
