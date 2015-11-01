#include <iostream>
#include <cmath>

using namespace std;
//f78397 Nikolay Nololov
int main() {
	//Main exetrcises
	int digit,number;
	cin >> number >> digit;
	int count_number = 0;
	for(int temp = number;temp != 0;count_number++,temp /= 10);
	if(count_number < digit){
		cout << "Wrong number!"<<endl;
	}
	else{
		cout << ((number / (int)pow(10,digit - 1))%10) << endl;
	
	
		// first subexercise
		int big_number = (number / (int)pow(10,1))%10;
		for(int temp = number,i = 1;i < count_number;i++,temp /= 10){
			int curent_digit = temp % 10;
			if(curent_digit > big_number){
				big_number = curent_digit;
			}
		}
		cout << big_number << endl;
		// second subexercise
		int sum_digits = 0;
		for(int temp = number;temp != 0;temp /= 10){
			sum_digits += temp % 10;
		}
		cout << sum_digits << endl;
		//third subexericse
		int n_digit = (number / (int)pow(10,digit - 1))%10;
		bool is_even_digit = !(n_digit & 1);
		cout << ((is_even_digit) ? "true" : "false") << endl;
		//fourth subexercise
		bool is_even_sum_digits = !(sum_digits & 1);
		cout << ((is_even_sum_digits) ? "true" : "false") << endl;
		//fifth subexericse
		cout << number << " = 1 ";
		for(int i = 2,temp = number;temp != 1 ;){
			if(temp % i == 0){
				cout << " * " << i;
				temp /= i;
			}
			else{
				i++;
			}
		}
	}
	return 0;
}
