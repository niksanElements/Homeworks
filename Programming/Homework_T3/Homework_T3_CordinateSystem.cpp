#include <iostream>

using namespace std;
struct point {
	int x;
	int y;
};

int main() {
	
	// The is firs subsection
	cout << "Place enter point:";
	point a;
	cin >> a.x >> a.y;
	
	if(a.x > 0){
		if(a.y > 0){
			cout << "The point is in 1 quadrant." << endl;
		}
		else if(a.y < 0){
			cout << "The point is in 4 quadrant." << endl;
		}
		else{
			cout << "The point is on the oc beetwin 1 and 4 quadrants." << endl;
		}
	}
	else if(a.x < 0){
		if(a.y > 0){
			cout << "The point is in 2 quadrant." << endl;
		}
		else if(a.y < 0){
			cout << "The point is in 3 quadrant." << endl;
		}
		else{
			cout << "The point is on the oc beetwin 2 and 4 quadrants." << endl;
		}
	}
	else{
		if(a.y > 0){
			cout << "The point is on the oc beetwin 1 and 2 quadrants." << endl;
		}
		else if(a.y < 0){
			cout << "The point is on the oc beetwin 3 and 4 quadrants." << endl;
		}
		else{
			cout << "The point is the 0." << endl;
		}
	}
	
	//The second subsection.
	const short int null = 0;
	const short int positive = 1;
	const short int negative = 2;
	
	
	point a2;
	cout << "Place enter point:";
	cin >> a2.x >> a2.y;
	
	short int sign_x;
	short int sign_y;
	
	if(a2.x > 0){
		sign_x = positive;
	}
	else if(a2.x < 0){
		sign_x = negative;
	}
	else{
		sign_x = null;
	}
	if(a2.y > 0){
		sign_y = positive;
	}
	else if(a2.y < 0){
		sign_y = negative;
	}
	else{
		sign_y = null;
	}
	switch(sign_x){
		case positive:
			cout << ((sign_y == positive) ? "The point is in 1 quadrant":
					((sign_y == negative) ? "The point is in 4 quadrant." :
					"The point is beetwin 1 and 4 quadrant."));
			break;
		case negative:
			cout << ((sign_y == positive) ? "The point is in 2 quadrant":
					((sign_y == negative) ? "The point is in 3 quadrant." :
					"The point is beetwin 2 and 3 quadrant."));
			break;
		case null:
			cout << ((sign_y == positive) ? "The point is on the oc beetwin 1 and 2 quadrants.":
					((sign_y == negative) ? "The point is on the oc beetwin 3 and 4 quadrants." :
					"The point is the 0."));
			break;
	}
	
	//The third subsection.
	
	int numbers_elements = 7; 
	point points[] = {
		{2,3},{3,-3},{0,0},
		{1,7},{3,-5},{-2,3},
		{0,3},
	};
	for(int i = 0;i < numbers_elements;i++){
		if(points[i].x > 0){
			if(points[i].y > 0){
				cout << "The point is in 1 quadrant." << endl;
			}
			else if(points[i].y < 0){
				cout << "The point is in 4 quadrant." << endl;
			}
			else{
				cout << "The point is on the oc beetwin 1 and 4 quadrants." << endl;
			}
		}
		else if(points[i].x < 0){
			if(points[i].y > 0){
				cout << "The point is in 2 quadrant." << endl;
			}
			else if(points[i].y < 0){
				cout << "The point is in 3 quadrant." << endl;
			}
			else{
				cout << "The point is on the oc beetwin 2 and 4 quadrants." << endl;
			}
		}
		else{
			if(points[i].y > 0){
				cout << "The point is on the oc beetwin 1 and 2 quadrants." << endl;
			}
			else if(points[i].y < 0){
				cout << "The point is on the oc beetwin 3 and 4 quadrants." << endl;
			}
			else{
				cout << "The point is the 0." << endl;
			}
		}
	}
	
	//The fourth subsection.
	const short int null = 0;
	const short int positive = 1;
	const short int negative = 2;
	
	
	int number_elements = 0;
	cout << "Enter number elements ";
	cin >> number_elements;
	for(int i = 0;i < number_elements;i++){
		cout << "Enter point: ";
		point a;
		cin >> a.x >> a.y;
		short int sign_x;
		short int sign_y;
		if(a.x > 0){
		sign_x = positive;
		}
		else if(a.x < 0){
			sign_x = negative;
		}
		else{
			sign_x = null;
		}
		if(a.y > 0){
			sign_y = positive;
		}
		else if(a.y < 0){
			sign_y = negative;
		}
		else{
			sign_y = null;
		}
		switch(sign_x){
			case positive:
				cout << ((sign_y == positive) ? "The point is in 1 quadrant":
						((sign_y == negative) ? "The point is in 4 quadrant." :
						"The point is beetwin 1 and 4 quadrant."));
				break;
			case negative:
				cout << ((sign_y == positive) ? "The point is in 2 quadrant":
						((sign_y == negative) ? "The point is in 3 quadrant." :
						"The point is beetwin 2 and 3 quadrant."));
				break;
			case null:
				cout << ((sign_y == positive) ? "The point is on the oc beetwin 1 and 2 quadrants.":
						((sign_y == negative) ? "The point is on the oc beetwin 3 and 4 quadrants." :
						"The point is the 0."));
				break;
		} 
		cout << endl;
	}
	return 0;
}
