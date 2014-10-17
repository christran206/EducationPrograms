#include <string.h>
#include <iostream>

using namespace std;

int intAddition(int firstNum, int secondNum);
const int ARRAYSIZE = 1;

int main() {	
	int a = 5;
	double b = 2.3;
	cout << a + b << endl;
}

int intAddition(int firstNum, int secondNum) {
	return firstNum + secondNum;
}