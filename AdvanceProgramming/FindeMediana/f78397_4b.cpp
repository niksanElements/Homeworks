#include <iostream>
#include <algorithm>

using namespace std;

int Compare_My (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main()
{
    unsigned number_of_input = 0;
    cin >> number_of_input;
    for(unsigned curent_input = 0;curent_input < number_of_input;curent_input++)
    {
        unsigned length_arr = 0;
        cin >> length_arr;
        int *arr = new int[length_arr];
        for(unsigned i = 0;i < length_arr;i++)
            cin >> arr[i];
        qsort(arr,length_arr,sizeof(int),Compare_My);
        cout <<((length_arr % 2)? arr[length_arr/2]: arr[(length_arr/2)- 1])<< endl;
        delete []arr;
    }
    return 0;
}
