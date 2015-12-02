#include <iostream>
#include <map>

using namespace std;

int main()
{
    unsigned length;
    while(cin >> length)
    {
        map<string,int> set_my;
        string in;
        for(unsigned i = 0;i < length;i++)
        {
            cin >> in;
            set_my[in]++;
        }
        string result;
        unsigned big_num = 0;
        for(map<string,int>::iterator ii = set_my.begin(); ii != set_my.end();ii++)
        {
            if(big_num < ii->second)
            {
                big_num = ii->second;
                result = ii->first;
            }
        }
        if(big_num > length/2)
            cout << result;
        else
            cout << "";
        cout << endl;
    }
    return 0;
}
