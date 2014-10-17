// ----------------------------------------------------------------------------
// You write meaningful comments and assumptions
//	Assumption: Input data is properly formatted.
//	Last name is no larger than 30 chars
//	First name is no larger than 30 chars
//	grade is a valid int

#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int const MAXSIZE = 100;            // maximum number of records in total
int const MAXLENGTH = 31;           // maximum string length 
int const MAXGRADE = 100;           // highest possible grade
int const LOWGRADE = 0;             // lowest possible grade
int const GROUP = 10;               // group amount
int const HISTOGRAMSIZE = (MAXGRADE-LOWGRADE)/GROUP + 1;    // grouped by GROUP

struct StudentType  {               // information of one student
   int grade;                       // the grade of the student
   char last[MAXLENGTH];            // last name (MAXLENGTH-1 at most)
   char first[MAXLENGTH];           // first name (MAXLENGTH-1 at most)
};

// prototypes go here
bool sortInput(ifstream& infile, StudentType students[], int& size);
int compareStudents(const StudentType firStudent,const StudentType secStudent);
void displayList(const StudentType students[],int size);
void setHistogram(int histogram[],const StudentType students[],int size);
void displayHistogram(const int histogram[]);
int findAverage(const StudentType students[],int size);



//------------------------------- main ----------------------------------------
int main()  {
   StudentType students[MAXSIZE];   // list of MAXSIZE number of students
   int size = 0;                    // total number of students
   int histogram[HISTOGRAMSIZE];    // grades grouped by GROUP
   int average = 0;                 // average exam score, truncated

   // creates file object and opens the data file
   ifstream infile("data1.txt");
   if (!infile)  { 
      cout << "File could not be opened." << endl; 
      return 1;  
   }

   // read and sort input by last then first name
   bool successfulRead = sortInput(infile, students, size);

   // display list, histogram, and class average 
   if (successfulRead)  {
      displayList(students, size);
      setHistogram(histogram, students, size);
      displayHistogram(histogram);
      average = findAverage(students, size);
      cout << "Average grade: " << average << endl << endl;
   }
   return 0;
}

// ----------------------------------------------------------------------------
// functions go here

/*
sortInput
read infile from first parameter and place into StudentType array from
second parameter using insertion sorting. Array size will be limited to
the third int parameter and will always be fewer than MAXSIZE
eof checked by the >> operator
Will increase size based on the number of valid student data added to 
students array

Assumption: Input data is properly formatted.
	Last name is no larger than 30 chars
	First name is no larger than 30 chars
	grade is a valid int
*/
bool sortInput(ifstream& infile, StudentType students[], int& size) {
	//While loop to populate student array
	while(size < MAXSIZE && !infile.eof()) {
		//Create a StudentType to store temp data for data check
		StudentType temp;
		//Assignments in if statement for validity check
		if (infile >> temp.last >> temp.first >> temp.grade) {
			//Check if grade is within valid range given, 
			//continue if not
			if(temp.grade < LOWGRADE || temp.grade > MAXGRADE) {
				continue;
			}
			//Insertion Implementation
			int diff = 0; //int to track difference to store temp
			//calls compareStudents function to determine 
			//alphabetical order
			//while loop if temp is lower than compared student
			while(compareStudents(temp,students[size-1-diff]) < 0 
				&& size-diff > 0) {
				   //shift student one index higher
				   students[size-diff] = students[size-1-diff];
				   diff++; //increase diff for next comparison
			}
			students[size-diff] = temp; //Store temp student
		    size++; //increase size
		}
	}
	//Returns a success as long as one StudentType is valid
	//Assumption: No students is a failure to sort
	return size >= 1;
}

//compareStudents
//Compare names of student in first StudentType parameter against
//StudentType in second parameter by last name and then by first name
//Returns -1 is first Student is lower alphabetically
//Returns 0 if the names are identical
//Returns 1 if the first Student is greater alphabetically
int compareStudents(const StudentType firStudent,const StudentType secStudent){
	//Compare last names and store in an int
	int result = strcmp(firStudent.last, secStudent.last);
	//If last name comparison results are 0, compare first names
	if( result == 0) {
		result =  strcmp(firStudent.first, secStudent.first);
	}
	return result;
}
//displayList
//read through StudentType array passed by first parameter with the count
//of students given by the size in the second parameter
void displayList(const StudentType students[],int size) {
	cout << "List of names sorted:" << endl;
	//for loop to go through students array
	for(int i = 0; i < size; i++) {
		//Using display width to adjust formatting
		cout << " " << students[i].grade << "  " << 
			students[i].last << " " << students[i].first << endl;
	}
	cout<< endl;
}

//setHistogram
//populate histogram using the int array in the first parameter using the
//StudentType array given in the second parameter. Number is students is
//limited by the size given in the third parameter
void setHistogram(int histogram[],const StudentType students[],int size) {
	//Array values are set to 0
	for(int i = 0; i < HISTOGRAMSIZE; i++) {
		histogram[i] = 0;
	}
	//For loop to parse information from StudentType array
	for(int i = 0; i < size; i++) {
		//Dividing grade by group results in a 
		//predictable array location
		histogram[students[i].grade/GROUP]++;
	}
}
//displayHistogram
//read int array given in parameter and display a formatted histogram
void displayHistogram(const int histogram[]) {
	cout << "Histogram of grades:" << endl;
	//For loop to display grade ranges increasing by GROUP value
	for(int grade = 0; grade <= MAXGRADE; grade+=GROUP) {
		//To display the range,a conditional is used to check if 
		//the value
		//goes beyond the MAXGRADE. If so, then display the MAXGRADE 
		cout << setw(3) << grade << "-->" << setw(4) << 
			(grade+GROUP-1 > MAXGRADE? MAXGRADE : grade+GROUP-1) << ": ";
		//Display a * for the int value stored in the 
		//array wfor the range
		for(int stars = 0; stars < histogram[grade/GROUP]; stars++) {
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;
}
//findAverage
//read data from StudentType array in first parameter and sum the grade values
//based on the number of students given by size in second parameter.
int findAverage(const StudentType students[],int size) {
	int gradeSum = 0; // Initial sum is 0
	//For loop to add all the grades of students
	for(int i = 0; i < size; i++) {
		gradeSum += students[i].grade;
	}
	return gradeSum/size; //Returns the sum divided by the size
}
