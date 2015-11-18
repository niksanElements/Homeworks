#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

bool Compare (char i,char j) { return (i>j); }

int main()
{
    string input;
    while(cin >> input)
    {
        sort(&input[0],&input[input.size()],Compare);
        cout << input << endl;
    }
    return 0;
}
