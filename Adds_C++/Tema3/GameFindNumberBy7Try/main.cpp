#include <iostream>

using namespace std;

int main()
{
    int begin = 1;
    int end = 100;
    int i = 0;
    do
    {
        int middle = begin + (end - begin)/2;
        cout << middle << endl;
        cout << "Chose a case 0)find -1)up 1) down ";
        short flag_case;
        cin >> flag_case;
        switch(flag_case)
        {
        case 0:
            {
                cout << "You win" <<endl;
                return 0;
            }
        case -1:
            {
                begin = middle + 1;
                break;
            }
        case 1:
            {
                end = middle - 1;
            }
        }
        i++;
    }while(i < 7);
    cout << "You lose!";
    return 0;
}
