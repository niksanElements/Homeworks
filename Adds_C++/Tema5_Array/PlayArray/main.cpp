#include <iostream>

using namespace std;
int* MergeSort(int [],unsigned);
int PrintArr(const int[],unsigned);
int FindeArea(const int[], unsigned);

int main()
{
    int* arr =new int[23]{5,7,3,6,2,1,15,45,4,3,6,3,76,234,6,6,6,6,6,6,876,234,867};
    unsigned length = 23;
    arr = MergeSort(arr,length);
    PrintArr(arr,length);
    int index = FindeArea(arr,length);
    cout << arr[index] << " on " << index;
    return 0;
}

int* Merge(int* left,unsigned l_length,int* right,unsigned r_length)
{
    int len = l_length + r_length;
    int* arr = new int[len];
    unsigned l_index = 0, r_index = 0, m_index = 0;
    while(l_index < l_length && r_index < r_length)
    {
        if(left[l_index] < right[r_index])
            arr[m_index++] = left[l_index++];
        else
            arr[m_index++] = right[r_index++];
    }
    while(l_index < l_length)
        arr[m_index++] = left[l_index++];
    while(r_index < r_length)
        arr[m_index++] = right[r_index++];
    return arr;
}


int* GetSubArr(int* arr,int first_index,int second_index)
{
    int* temp_arr = new int[(second_index - first_index) + 1];
    for(int i = first_index,index = 0;i <= second_index;i++,index++)
        temp_arr[index] = arr[i];
    return temp_arr;
}
int* MergeSort(int* arr,unsigned length)
{
    if(length <= 1)
        return arr;
    int middle_element = length/2;
    int* left_arr = GetSubArr(arr,0,middle_element - 1);
    int* right_arr = GetSubArr(arr,middle_element,length - 1);
    int left_length = middle_element;
    int right_length = length - middle_element;
    left_arr = MergeSort(left_arr,left_length);
    right_arr = MergeSort(right_arr,right_length);
    return Merge(left_arr,left_length,right_arr,right_length);
}
int PrintArr(const int arr[], unsigned length)
{
    for(int i = 0;i < length;i++)
    {
        cout << arr[i] << "\t";
    }
    cout << endl;
    return 0;
}
int FindeArea(const int arr[],unsigned length)
{
    int index_area = 0;
    int max_area = 0;
    int temp_area = 1;
    for(int i = 0;i < length - 1;i++)
    {
        if(arr[i] == arr[i+1])
            temp_area++;
        else
        {
            if(temp_area > max_area)
            {
                index_area = i - (temp_area - 1);
                max_area = temp_area;
            }
            temp_area = 1;
        }
    }
    return index_area;
}
