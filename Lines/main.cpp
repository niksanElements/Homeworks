#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

typedef struct s_point
{
    int f,s,v;
}point;

bool comp(const point &a,const point &b)
{
     if(a.f == b.f)
     {
         return a.s > b.s;
     }
     return a.f < b.f;
}

int n;

vector<point> lines;
vector<point> l2;
stack<point> s;

int main()
{
    cin >> n;
    for(int i = 0;i < n;i++)
    {
        int f,s;
        cin >> f >> s;
        // int v = s -f;
        lines.push_back(point {f,s,i});
        l2.push_back(point {f,s,i});
    }
    sort(lines.begin(),lines.end(),comp);

    vector<int> result;
    int currMax = 1;
    for(int i = 0;i < lines.size() * 2;i++)
    {
        if(s.empty())
        {
            s.push(lines[i]);
        }
        else
        {
            point p = s.top();
            if(lines[i].f == p.f && lines[i].s == p.s && lines[i].v == p.v)
            {
                currMax += 1;

                s.pop();
            }
            else
            {
                s.push(lines[i]);
                currMax = 0;
            }

        }
    }

    for(int i = 0;i < result.size();i++)
        cout << result[i] << endl;

    return 0;
}
