#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void CountDevNum(unsigned number_for_beaking,unsigned pos,const vector<int> &vec_bn);

int adds[1000];
int count_n = 0;

int main()
{
    string input_breaking_numbers;
    string input_numbers_for_breaking;
    while(getline(cin,input_breaking_numbers) && getline(cin,input_numbers_for_breaking))
    {
        stringstream input_line_bn(input_breaking_numbers);
        vector <int> breaking_numbers;
        int temp = 0;
        while(input_line_bn >> temp)
            breaking_numbers.push_back(temp);
        stringstream input_line_nfb(input_numbers_for_breaking);
        vector<int> numbers_for_breaking;
        while(input_line_nfb >> temp)
            numbers_for_breaking.push_back(temp);
        for (unsigned i = 0;i < numbers_for_breaking.size();i++)
        {
            adds[0] = numbers_for_breaking[i]+1;
            CountDevNum(numbers_for_breaking[i],1,breaking_numbers);
            cout << count_n << " ";
            count_n = 0;
        }
        cout << endl;
    }
    return 0;
}


void CountDevNum(unsigned number_for_breaking,unsigned pos,const vector<int> &vec_bn)
{
    for (int i = vec_bn.size() - 1;i > 0;i--)
    {
        unsigned curent_bn = vec_bn[i];
        if(number_for_breaking > curent_bn)
        {
            adds[pos] = curent_bn;
            if(adds[pos] <= adds[pos - 1])
                CountDevNum(number_for_breaking - curent_bn,pos+1,vec_bn);
        }
        else if(number_for_breaking == curent_bn)
        {
            adds[pos] = curent_bn;
            if(adds[pos] <= adds[pos - 1])
                count_n++;
        }
    }
}
