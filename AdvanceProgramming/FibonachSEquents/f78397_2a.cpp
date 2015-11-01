#include <iostream>
#include <vector>

using namespace std;




 unsigned int fib(unsigned int n, unsigned int a , unsigned int b)
{
     if(n <= 1) return 1;
     else return a*fib(n-1,a,b) + b*fib(n-2,a,b);
}
void GenerateFib(vector<int> &fib_set,unsigned int a, unsigned int b)
{
    unsigned fib_num = 0;
    for(unsigned int i = 0;fib_num < 10000000;i++)
    {
        fib_num = fib(i,a,b);
        fib_set.push_back(fib_num);
    }
}
int GetFib(vector<int> & fib,int num,int a,int b)
{
    for( unsigned int i = 0;i < fib.size();i++)
    {
        if(fib[i] == num)
        {
            return i;
        }
    }
    return 0;
}
int main()
{
    int a,b;
    while(cin >> a >> b)
    {
        unsigned int elements;
        cin >> elements;
        unsigned int *numbers = new unsigned int[elements];
        unsigned big_num = 0;
        for(unsigned int i = 0;i < elements;i++)
        {
            cin >> numbers[i];
            if(numbers[i] > big_num)
                big_num = numbers[i];
        }
        vector<int> fib;
        fib.push_back(0);
        GenerateFib(fib,a,b);
        for(int  i = 0;i < fib.size();i++)
            cout << fib[i] << " ";
        cout << endl;

        vector<int> fib_1;
        unsigned fib_1_num1 = 1l;
        unsigned fib_1_num2 = 1l;
        cout << fib_1_num1 << " " << fib_1_num2 << " ";
        for(int i = 0;i < 100;i++)
        {
            int temp = (b*fib_1_num1) + (a * fib_1_num2);
            fib_1_num1 = fib_1_num2;
            fib_1_num2 = temp;
            cout << fib_1_num2 << " ";
        }
        cout << endl;


        for(unsigned i = 0;i < elements;i++)
        {
            int result = GetFib(fib,numbers[i],a,b);
            cout << result << endl;
        }
    }
}
