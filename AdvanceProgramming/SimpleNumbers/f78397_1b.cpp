#include <iostream>
#include <vector>

using namespace std;
//f78397     Nikolay Nikolov 1b
int findeNumSimpleEratosten(int min, int max){
	int counter = 0;
	vector<int>sive(max + 1);
	sive[0] = 0;
	sive[1] = 0;
	for(int i = 2;i<= max;i++)
		sive[i] = 1;
	for(int i = 2; i <= max;i++){
		if(sive[i] != 0 && min <= i){
			counter++;
		}
		for(int j = i + i;j <= max;j += i){
			sive[j] = 0;
		}
	}
	return counter;
}
int main() {
	int number_intervals;
	cin >> number_intervals;
	int counter_simple_numbers[number_intervals];
	for(int i = 0;i < number_intervals;i++){
		int min ,max;
		cin >> min >> max;
		counter_simple_numbers[i] = findeNumSimpleEratosten(min,max);
	}
	for (int i = 0;i < number_intervals;i++){
		cout << counter_simple_numbers[i] << endl;
	}
	return 0;
}
