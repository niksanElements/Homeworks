#include <iostream>

using namespace std;

double GetAverige(const int arr[],int lenght);
int *Delete(int *arr,int &lenght,int smaller_element);


int main()
{
    int lenght;
    cin >> lenght;

    int *arr_numbers= new int[lenght];
    for(int i = 0;i < lenght;i++)
        cin >> arr_numbers[i];
    int averige = GetAverige(arr_numbers,lenght);
    arr_numbers = Delete(arr_numbers,lenght,averige);

    for(int i = 0;i < lenght;i++)
        cout << arr_numbers[i] << " ";
    cout << endl;
    delete []arr_numbers;
    return 0;
}

double GetAverige(const int arr[],int lenght)
{
    int sum = 0;
    for(int i = 0;i < lenght;i++)
        sum += arr[i];
    return sum/lenght;
}
int *Delete(int *arr, int &lenght, int smaller_element)
{
    int count_lenght = 0;
    for(int i = 0;i < lenght;i++)
        if(smaller_element <= arr[i])
            count_lenght++;
    int *temp_arr = new int[count_lenght];
    int temp_index = 0;
    for(int i = 0;i < lenght;i++)
    {
        if(arr[i] >= smaller_element)
        {
            temp_arr[temp_index] = arr[i];
            temp_index++;
        }
    }
    lenght = count_lenght;
    return temp_arr;
}
