#include "employee.h"

// incomplete class and not fully documented

//--------------------------  constructor  -----------------------------------
Employee::Employee(string last, string first, int id, int sal) {
   idNumber = (id >= 0 && id <= MAXID? id : -1);
   salary = (sal >= 0 ? sal : -1);
   lastName = last;
   firstName = first;
}   

//--------------------------  destructor  ------------------------------------
// Needed so that memory for strings is properly deallocated
Employee::~Employee() {}

//---------------------- copy constructor  -----------------------------------
   Employee::Employee(const Employee& E) {
      lastName = E.lastName;
      firstName = E.firstName;
      idNumber = E.idNumber;
      salary = E.salary;
   }

//-------------------------- operator= ---------------------------------------
   Employee& Employee::operator=(const Employee& E) {
      if (&E != this) {
         idNumber = E.idNumber;
         salary = E.salary;
         lastName = E.lastName;
         firstName = E.firstName;
      }
      return *this;
   }

//-----------------------------  setData  ------------------------------------
// set data from file
bool Employee::setData(ifstream& inFile) {
   inFile >> lastName >> firstName >> idNumber >> salary;
   return idNumber  >= 0 && idNumber <= MAXID && salary >= 0; 
}

//-------------------------------  <  ----------------------------------------
// < defined by value of name
bool Employee::operator<(const Employee& E) const { 
   return lastName < E.lastName ||
          (lastName == E.lastName && firstName < E.firstName);
}


//-------------------------------  <= ----------------------------------------
// < defined by value of inamedNumber
bool Employee::operator<=(const Employee& E) const { 
   return *this < E || *this == E;
}

//-------------------------------  >  ----------------------------------------
// > defined by value of name
bool Employee::operator>(const Employee& E) const { 
   return lastName > E.lastName ||
          (lastName == E.lastName && firstName > E.firstName);
}

//-------------------------------  >= ----------------------------------------
// < defined by value of name
bool Employee::operator>=(const Employee& E) const { 
   return *this > E || *this == E;
}

//----------------- operator == (equality) ----------------
// if name of calling and passed object are equal,
//   return true, otherwise false
//
bool Employee::operator==(const Employee& E) const {
   return lastName == E.lastName && firstName == E.firstName;
}

//----------------- operator != (inequality) ----------------
// return opposite value of operator==
bool Employee::operator!=(const Employee& E) const {
   return !(*this == E);
}

//-------------------------------  <<  ---------------------------------------
// display Employee object

ostream& operator<<(ostream& output, const Employee& E) { 
   output << setw(4) << E.idNumber << setw(7) << E.salary << "  " 
          << E.lastName << " " << E.firstName << endl; 
   return output;
}

