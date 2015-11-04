#include <iostream>

using namespace std;


unsigned DefBetweenMaxMin(const int arr[],int lenght);
unsigned FindMax(const int arr[],int lenght);
unsigned FindMin(const int arr[],int lenght);

int main()
{
    int numbers[] = {1,2,3,4,0,6,7,8,9,10};
    cout << DefBetweenMaxMin(numbers,10) << endl;
    return 0;
}
unsigned DefBetweenMaxMin(const int arr[], int lenght)
{
    int max_element = FindMax(arr,lenght);
    int min_element = FindMin(arr,lenght);
    return max_element - min_element;
}
unsigned FindMax(const int arr [], int lenght)
{
    int max = arr[0];
    for(int i = 1;i < lenght;i++)
    {
        if(max < arr[i])
        {
            max = arr[i];
        }
    }
    return max;
}
unsigned FindMin(const int arr[],int lenght)
{
    int min = arr[0];
    for(int i = 1;i < lenght;i++)
    {
        if(min > arr[i])
        {
            min = arr[i];
        }
    }
    return min;
}

