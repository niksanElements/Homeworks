#include <iostream>
#include <cmath>

using namespace std;

int ChangeDigit(int num)
{
    int temp = num;
    int count_n = 0;
    while(temp)
    {
       count_n++;
       temp /= 10;
    }
    int first_digit = num / pow(10,count_n-1);
    num += (first_digit * pow(10,count_n));
    return num;
}

void Swap(int &num1,int &num2)
{
    num1 ^= num2;
    num2 ^= num1;
    num1 ^= num2;
}

int main()
{
    int lenght = 5;

    int numbers[] = {12,232,33,4343,5214};
    int *point_bigin = &numbers[0];
    int *point_end = &numbers[lenght - 1];
    while(point_bigin <  point_end)
    {
        Swap(*point_bigin,*point_end);
        point_bigin++;
        point_end--;
    }

    for(int i = 0;i < lenght;i++)
        numbers[i] = ChangeDigit(numbers[i]);

    for(int i = 0;i < lenght;i++)
        cout << numbers[i] << " ";
    cout << endl;
    return 0;
}
