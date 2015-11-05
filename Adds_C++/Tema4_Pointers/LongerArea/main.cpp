#include <iostream>

using namespace std;

int main()
{
    int lenght = 17;
    int numbers[] = {1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5};

    int temp_count = 1;
    int count_longer_area = 1;
    int count_all_area = 1;
    for (int i = 0;i < lenght-1;i++)
    {
        if(numbers[i] == numbers[i+1])
        {
            temp_count++;
        }
        else if(numbers[i] != numbers[i+1])
        {
            count_all_area++;
            temp_count = 1;
        }
        if(temp_count > count_longer_area)
        {
            count_longer_area = temp_count;
        }
    }
    cout << count_longer_area << " " << count_all_area << endl;
    return 0;
}
