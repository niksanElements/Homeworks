#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

unsigned gcd(unsigned x, unsigned y)
{
    while (y > 0)
    {
        unsigned tmp = y;
        y = x % y;
        x = tmp;
    }
    return x;
}
string ShiftLeft1(string m,unsigned k)
{
    unsigned i, ths, next, gcdNK;
    unsigned n = m.size();
    char  tmp;
    for (gcdNK = gcd(n, k), i = 0; i < gcdNK; i++)
    {
        ths = i;
        tmp = m[ths];
        next = ths + k;
        if (next >= n)
            next -= n;
        while (next != i)
        {
            m[ths] = m[next];
            ths = next;
            next += k;
            if (next >= n)
                next -= n;
        }
        m[ths] = tmp;
    }
    return m;
}

int main()
{
    string str;
    while(cin >> str)
    {
        string input;
        unsigned temp;
        cin >> temp;
        getline(cin,input);
        stringstream in(input);
        vector<unsigned> nums;
        nums.push_back(temp);
        while(in >> temp)
            nums.push_back(temp);
        unsigned n = str.size();
        for(unsigned i = 0;i < nums.size();i++)
        {
            while(n < nums[i])
                nums[i] -= n;
            cout << ShiftLeft1(str,nums[i]) << endl;
        }
    }
    return 0;
}
