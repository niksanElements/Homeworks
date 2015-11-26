#include <iostream>
#include <iomanip>

using namespace std;

void GenerateMegicSquer(int **matrix,int n)
{
    if (n % 2 == 0)
    {
        cout << "It can't be done!!" << endl;
        return;
    }
    int i = n/2;
    int j = n-1;

    // One by one put all values in magic square
    for (int num=1; num <= n*n; )
    {
        if (i==-1 && j==n) //3rd condition
        {
            j = n-2;
            i = 0;
        }
        else
        {
            //1st condition helper if next number goes to out of square's right side
            if (j >= n)
                j = 0;
            //1st condition helper if next number is goes to out of square's upper side
            if (i < 0)
                i=n-1;
        }
        if (matrix[i][j]) //2nd condition
        {
            j -= 2;
            i++;
            continue;
        }
        else
            matrix[i][j] = num++; //set number

        j++;  i--; //1st condition
    }
}

int main()
{
    int n;
    cin >> n;
    int **matrix = new int*[n];
    for(int i = 0;i < n;i++)
    {
        matrix[i] = new int[n];
        for(int j = 0;j < n;j++)
        {
            matrix[i][j] = 0;
        }

    }
    GenerateMegicSquer(matrix,n);
    for(int i = 0;i < n;i++)
    {
        for(int j = 0;j < n;j++)
            cout << setw(2) << matrix[i][j] << ' ';
        cout << endl;
    }
    for(int i = 0;i < n;i++)
        delete []matrix[i];
    delete []matrix;
    return 0;
}
