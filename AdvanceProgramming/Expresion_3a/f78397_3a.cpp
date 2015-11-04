#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/* Брой числа в редицата */
  vector<int> vec;
  bool is_done;
  bool is_have;

  void Print(int n,int temp_sum)
  {
      int temp = 0;
        for(int i = 0;i < n;i++)
        {
            if(vec[i] > 0)
            {
                cout << vec[i];
                temp = i;
                break;
            }
        }
        for (int i = 0; i < n; i++)
        {
            if(i != temp)
            {
                if (vec[i] > 0)
                cout << "+" << vec[i];
            else
                cout << vec[i];
            }
        }
        cout << "=" << temp_sum << endl;
        is_done = true;
  }

void checkSol(int n,int sum)
{
    int temp_sum = 0;
    for (int i = 0;i < n;i++)
        temp_sum += vec[i];
    if (temp_sum == sum)
    {
        Print(n,temp_sum);
        is_have = true;
    }
}
void variate(unsigned i,unsigned n,int sum)
{
    if(is_done)
        return;
    if (i >= n)
    {
        checkSol(n,sum);
        return;
    }
    vec[i] = abs(vec[i]);
    variate(i + 1,n,sum);
    vec[i] = -abs(vec[i]);
    variate(i + 1,n,sum);
}
void GetSumFromSequence(const vector<int> &vec,int sum)
{
    int n = vec.size()-1;
    for(unsigned i = 0;i < vec.size() - 1;i++)
        variate(i,n,sum);
}

int main(void) {
    string input;
    while(getline(cin,input))
    {
        istringstream stream_num (input);
        int num;
        while(stream_num >> num)
            vec.push_back(num);
        is_done = false;
        is_have = false;
        int sum = vec[vec.size()-1];
        vec[vec.size()-1] = 0;
        GetSumFromSequence(vec,sum);
        if(!is_have)
            cout << endl;
        vec.clear();
    }
  return 0;
}
