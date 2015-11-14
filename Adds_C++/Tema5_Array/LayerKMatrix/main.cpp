#include <iostream>

using namespace std;
int FindeSumLayer(const int[][6], unsigned, unsigned);

int main()
{
    int matrix[6][6] =
    {
        {12,3,5,6,7,4},
        {12,3,5,6,7,4},
        {12,3,5,6,7,4},
        {12,3,5,6,7,4},
        {12,3,5,6,7,4},
        {12,3,5,6,7,4}
    };
    int sum = FindeSumLayer(matrix,6,1);
    for (int i = 2;i <= 3;i++)
    {
        int temp_sum = FindeSumLayer(matrix,6,i);
        if(temp_sum != sum)
        {
            cout << "NO";
            return 0;
        }
    }
    cout << "Yes";

    return 0;
}

int FindeSumLayer(const int arr[][6],unsigned length,unsigned k)
{
    int index_layer = k - 1;
    int sum = 0;
    for(unsigned i = index_layer;i < length-(index_layer);i++)
    {
        sum += arr[i][index_layer];
        sum += arr[i][length-1-index_layer];
    }
    for(unsigned i = index_layer;i < length-(index_layer);i++)
    {
        sum += arr[index_layer][i];
        sum += arr[length - index_layer - 1][i];
    }
    return sum;
}
