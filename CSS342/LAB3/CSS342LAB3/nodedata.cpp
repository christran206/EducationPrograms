//////////////////////////////  nodedata.cpp  ////////////////////////////////

#include "nodedata.h"

//--------------------------  constructor  -----------------------------------
NodeData::NodeData(int n, char c)  { num = n; ch = c; }  

//-----------------------------  setData  ------------------------------------
// set data by prompting user
bool NodeData::setData() { 
   cout << "Please enter an integer: ";   cin >> num;
   cout << "Please enter a character: ";  cin >> ch; 
   return true;
}

//-----------------------------  setData  ------------------------------------
// set data from file
bool NodeData::setData(ifstream& infile) { 
   infile >> num >> ch;
   return true;
}

//-------------------------------  <  ----------------------------------------
// < defined by value of num; if nums equal, ch is used
bool NodeData::operator<(const NodeData& N) const { 
   if (num < N.num) return true;
   if (num == N.num) return ch < N.ch;
   return false; 
}

//-------------------------------  >  ----------------------------------------
// > defined by value of num; if nums equal, ch is used
bool NodeData::operator>(const NodeData& N) const { 
   if (num > N.num) return true;
   if (num == N.num) return ch > N.ch;
   return false;
}

//-------------------------------  ==  ---------------------------------------
// > defined by value of num; if nums equal, ch is used
bool NodeData::operator==(const NodeData& N) const { 
   return num == N.num && ch == N.ch;
}

//-------------------------------  !=  ---------------------------------------
// > defined by value of num; if nums equal, ch is used
bool NodeData::operator!=(const NodeData& N) const { 
   return !(*this == N);
}

//-------------------------------  <<  ---------------------------------------
// display NodeData object
ostream& operator<<(ostream& output, const NodeData& N) { 
   output << N.num << ' ' << N.ch << endl;
   return output;
}

