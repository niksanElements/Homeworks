#include <iostream>

using namespace std;
unsigned NumbersOfDevision(unsigned num);
int* GetArrDevisions(unsigned number,int* lenght);

int main()
{
    int lenght = 0;
    int* arr_dev = GetArrDevisions(120,&lenght);
    for(int i = 0;i < lenght;i++)
        cout << arr_dev[i] << " ";
    return 0;
}

int* GetArrDevisions(unsigned number,int* lenght)
{
    int tmp_lenght = NumbersOfDevision(number);
    *lenght = tmp_lenght;
    int* arr_dev = new int[*lenght];
    int count_dev = 1;
    for(int i = 0;i < *lenght;count_dev++)
    {
        if(number%count_dev == 0)
        {
            arr_dev[i] = count_dev;
            i++;
        }
    }
    return arr_dev;
}
unsigned NumbersOfDevision(unsigned num)
{
    unsigned count = 0;
    unsigned devision = 2;
    unsigned result = 1;
    while(num != 1)
    {
        if(num%devision == 0)
        {
            num /= devision;
            count++;
        }
        else
        {
            result *= (count+1);
            devision++;
            count = 0;
        }
    }
    return result*(count+1);
}
