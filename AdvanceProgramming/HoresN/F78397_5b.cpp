#include <iostream>
#include <iomanip>

using namespace std;

int **table;
short  n;
bool is_done;
short x_position[] = {-1, 1, 2,2,1,-1,-2,-2};
short y_position[] = {-2,-2,-1,1,2, 2, 1,-1};
const int basic_movments = 8;
void Print()
{
    for(int i = 0;i < n;i++)
    {
        for(int j = 0;j < n;j++)
        {
            cout << setw(2) << table[i][j] << ' ';
        }
        cout << endl;
    }
}
void FindeMoves(int x, int y,int count_moves)
{
    if(!is_done)
    {
        if(x < n && x >= 0 && y < n && y >= 0)
        {
            if(count_moves == (n*n) + 1)
            {
                Print();
                is_done = true;
            }
            if(table[y][x] == 0)
            {
                table[y][x] = count_moves;
                for(int i = 0;i < basic_movments;i++)
                    FindeMoves(x+x_position[i],y+y_position[i],count_moves +1);
                table[y][x] = 0;
            }
        }
    }
}

int main()
{
    int x,y;
    while(cin >> n >> y >> x)
    {
        is_done = false;
        table = new int*[n];
        for(int i = 0;i < n;i++)
        {
            table[i] = new int[n]{};
        }
        FindeMoves(x -1,y - 1,1);
        if(!is_done)
        {
            for(int i = 0;i < n;i++)
            {
                for(int j = 0;j < n;j++)
                {
                    cout << setw(2) << 0 << ' ';
                }
                cout << endl;
            }
        }
    }
    return 0;
}
