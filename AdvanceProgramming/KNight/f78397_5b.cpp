#include <iostream>
#include <tuple>
#include <algorithm>
#include <vector>
#include <array>
#include <iomanip>

using namespace std;

int N;
pair<int,int> moves[8] = {make_pair(2, 1), make_pair(1, 2), make_pair(-1, 2), make_pair(-2, 1),
    make_pair(-2, -1), make_pair(-1, -2), make_pair(1, -2), make_pair(2, -1)};
int **board;

array<int,8> sortMoves(int x, int y)
{
    array<tuple<int,int>,8> counts;
    for(int i = 0; i < 8; ++i)
        {
            int dx = get<0>(moves[i]);
            int dy = get<1>(moves[i]);

            int c = 0;
            for(int j = 0; j < 8; ++j)
            {
                int x2 = x + dx + get<0>(moves[j]);
                int y2 = y + dy + get<1>(moves[j]);

                if (x2 < 0 || x2 >= N || y2 < 0 || y2 >= N)
                    continue;
                if(board[y2][x2] != 0)
                    continue;

                c++;
            }

            counts[i] = make_tuple(c, i);
        }

        // Shuffle to randomly break ties
        random_shuffle(counts.begin(), counts.end());

        // Lexicographic sort
        sort(counts.begin(), counts.end());

        array<int,8>out;
        for(int i = 0; i < 8; ++i)
            out[i] = get<1>(counts[i]);
        return out;
    }

    bool solve(int x, int y)
    {
        for(int v = 0; v < N; ++v)
            for(int u = 0; u < N; ++u)
                board[v][u] = 0;

        int x0 = x;
        int y0 = y;
        board[y0][x0] = 1;

       vector<tuple<int, int, int, array<int,8>>> order(N*N);
        order[0] = make_tuple(x0, y0, 0, sortMoves(x0, y0));
        vector<short> flags(N*N);
        int n = 0;
        bool ok;
        while(n < N*N-1)
        {
            int x = get<0>(order[n]);
            int y = get<1>(order[n]);
            ok = false;
            for(int i = get<2>(order[n]);i < 8; ++i)
            {
                int dx = moves[get<3>(order[n])[i]].first;
                int dy = moves[get<3>(order[n])[i]].second;


                if(x+dx < 0 || x+dx >= N || y+dy < 0 || y+dy >= N)
                    continue;
                if(board[y + dy][x + dx] != 0)
                    continue;
                ++n;
                get<2>(order[n]) = i + 1;
                board[y+dy][x+dx] = n + 1;
                flags[n]++;
                if(flags[n] > 8)
                    return false;
                order[n] = make_tuple(x+dx, y+dy, 0, sortMoves(x+dx, y+dy));
                ok = true;
                break;
            }

            if(!ok) // Failed. Backtrack.
            {
                board[y][x] = 0;
                --n;
            }
        }
        return true;;
    }


int main()
{
    int x,y;
    while(cin >> N >> y >> x)
    {
        board = new int*[N];
        for(int i = 0;i < N;i++)
        {
            board[i] = new int[N];
        }
        if(solve(x-1,y-1))
        {
            for(int i = 0;i < N;++i)
            {
                for(int j = 0;j < N;++j)
                {
                    cout << setw(2) << board[i][j] << ' ';
                }
                cout << endl;
            }
        }
        else
        {
            for(int i = 0;i < N;i++)
            {
                for(int j = 0;j < N;j++)
                     cout << setw(2) << 0 << ' ';
                cout << endl;
            }
        }
        cout << endl;
        delete []board;
    }
}
