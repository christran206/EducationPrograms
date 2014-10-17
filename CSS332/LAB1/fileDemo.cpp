// fileDemo.cpp : Defines the entry point for the console application.
//

/*note that this code won't compile directly on unix or mac without modification - try porting it now to your compiler*/
//#include "stdafx.h"
#include <fstream>
#include <iostream>
using namespace std;


//constants, flags, etc...
const static int MAX_SIZE = 100;    //q:which is better - this or #define?
const static bool DEBUG = true;

//related data structures for this program
struct rational {
	int num;
	int denom;
};

//todo:follow each line of code in a debugger, commenting as you go, answering the following questions
//q:can a byte ever be defined as anything other than 8 bits?  What does the C specification say about this related to chars?
int main(int argc, char* argv[])  //explain the new types here
{
	//using the stream concept in C, how to write a file 
	//note you could use an fstream object to accomplish both tasks
	//but explicit use of ofstream/ifstream makes responsibilities more obvious
	ofstream outFile;
	outFile.open("rats.dat");
	for (int i = 0; i < MAX_SIZE / 2; i++) {
		outFile << i << " " << (i + 1) << " " ;  //0/1, 1/2, watch for boundary cases like denom == 0
	}
	outFile.close();  //always
	
	struct rational rats[MAX_SIZE];
	ifstream  inFile;
	inFile.open("rats.dat");
	if (inFile.is_open()) {
		int top,bottom;		//q:what are the starting values here?
		int count = 0;
		while (inFile >> top >> bottom && count < MAX_SIZE) {
			rats[count].num = top;
			rats[count].denom = bottom;
			if(DEBUG) {
				cout << rats[count].num << "/" << rats[count].denom << endl;
			}
			count++;
		}
		inFile.close();
	}
	else {
		cerr << "Didn't open file.";
		exit(-1);
	}

	return 0;
}

