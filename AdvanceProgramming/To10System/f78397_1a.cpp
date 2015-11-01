#include <iostream>
#include <string>
#include <cmath>

using namespace std;
//F78397 Nikolay Nikolov 1a



int getValueFrom16Base(char c){
	switch(c){
		case '1':{
			return 1;
			break;
		}
		case '2':{
			return 2;
			break;
		}
		case '3':{
			return 3;
			break;
		}
		case '4':{
			return 4;
			break;
		}
		case '5':{
			return 5;
			break;
		}
		case '6':{
			return 6;
			break;
		}
		case '7':{
			return 7;
			break;
		}
		case '8':{
			return 8;
			break;
		}
		case '9':{
			return 9;
			break;
		}
		case 'A':{
			return 10;
			break;
		}
		case 'B':{
			return 11;
			break;
		}
		case 'C':{
			return 12;
			break;
		}
		case 'D':{
			return 13;
			break;
		}
		case 'E':{
			return 14;
			break;
		}
		case 'F':{
			return 15;
			break;
		}
		default :{
			return 0;
			break;
		}
	}
}
void from2to10(){
	const short int base = 2;
	string input;
	cin >> input;
	int number = 0;
	int index = 0;
	for(int i = input.size() - 1;i >= 0;i--){
		if(input[i] == '1'){
			number += pow(base,index);
		}
		index++;
	}	
	cout << number << endl;
}
void from8to10(){
	const short int base = 8;
	int number;
	cin >> number;
	int result = 0;
	for(int i = 0;number != 0;number /= 10,i++){
		result += (number % 10) * pow(base,i);
	}
	cout << result;
}
void from16to10(){
	const short int base = 16;
	string input;
	cin >> input;
	int result;
	for(int i = input.size() - 1,index = 0;i >= 0;i--,index++){
		result += getValueFrom16Base(input[i]) * pow(base,index);
	}
	cout << result << endl;
}

int main() {
	int system;
	cin >> system;
	switch(system){
		case 2:{
			from2to10();
			break;
		}
		case 8:{
			from8to10();
			break;
		}
		case 16:{
			from16to10();
			break;
		}
	}
	return 0;
}
