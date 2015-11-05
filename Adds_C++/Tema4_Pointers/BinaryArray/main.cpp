#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>

using namespace std;

unsigned short *From10To2(unsigned number,unsigned &lenght);
unsigned long long From2To10(unsigned short** binary_matrix,const unsigned int binary_lenght[],unsigned lenght);

const int rand_min_element = 10;
const int rand_max_element = 100;

int main()
{
    srand(time(0));
    unsigned lenght = 0;
    cin >> lenght;

    unsigned *arr_numbers  = new unsigned[lenght];
    for(unsigned i = 0;i < lenght;i++)
    {
        arr_numbers[i] = rand()%(rand_max_element - rand_min_element) + rand_min_element;
    }

    unsigned short **binary_matrix = new unsigned short*[lenght];
    unsigned int* binary_lenghts = new unsigned int[lenght];
    for(unsigned i = 0;i < lenght;i++)
    {
        binary_matrix[i] = From10To2(arr_numbers[i],binary_lenghts[i]);
    }
    unsigned long long result_number = From2To10(binary_matrix,binary_lenghts,lenght);
    cout << result_number << endl;


    delete []arr_numbers;
    for(unsigned i = 0;i < lenght;i++)
        delete []binary_matrix[binary_lenghts[i]];
    delete []binary_matrix;
    delete []binary_lenghts;

    return 0;
}

unsigned short *From10To2(unsigned number,unsigned &lenght)
{
    int temp = number;
    lenght = 0;
    while(temp)
    {
        temp = temp >> 1;
        lenght++;
    }
    if(lenght % 4 != 0)
        lenght += (4 - (lenght % 4));
    unsigned short *binary_arr = new unsigned short[lenght];
    for(int i = lenght - 1;i >= 0;i--)
    {
        temp = number % 2;
        number /= 2;
        binary_arr[i] = temp;
    }
    return binary_arr;

}

unsigned long long From2To10(unsigned short** binary_matrix,const unsigned int binary_lenght[],unsigned lenght)
{
	const short int base = 2;
	unsigned long long result_number = 0;
	int index = 0;
	for(int i = lenght - 1;i >= 0;i--)
    {
        for(int j = binary_lenght[i] - 1;j >= 0;j--)
        {
            int temp = binary_matrix[i][j];
            if(binary_matrix[i][j] == 1)
            {
                result_number += pow(base,index);
            }
            index++;
        }
	}
	return result_number;
}
