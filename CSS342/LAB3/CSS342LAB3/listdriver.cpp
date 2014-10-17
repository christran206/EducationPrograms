
// Driver for simple linked list, does not do thorough testing
// test using lists of different length and all possible combinations
// Not compiled, might have typos

#include "list.h"
#include "nodedata.h"

// to compile under unix/linux:  g++ listdriver.cpp nodedata.cpp 

int main() {
   NodeData* ptr;                    // used for parameter 2 in retrieve, remove
   List list1, list2, list3, list4, list5; 

   // create file object and open the datafiles
   ifstream infile("listdata.txt");
   if (!infile) {
      cout << "File could not be opened." << endl;
      return 1;
   }
   ifstream infile2("listdata2.txt");
   if (!infile2) {
      cout << "File could not be opened." << endl;
      return 1;
   }

   // build lists from data files 
   list1.buildList(infile);                 
   list2.buildList(infile2);                 

   // print, sorted by number
   cout << endl << list1 << endl;           
   cout << endl << list2 << endl;           

   // check copy constructor and assignment
   list3 = list2;
   list5 = list1;
   List list6(list2), list7(list1);
   cout << endl << list3 << endl;           
   cout << endl << list7 << endl;           

   // test == and !=
   cout << "list1 " << (list1 == list2 ? "equals":"does not equal") 
        << " list2" << endl;
   cout << "list2 " << (list2 == list3 ? "equals":"does not equal") 
        << " list3" << endl;

   // check merge, intersect
   list4.merge(list1, list2);  cout << endl << list4 << endl;           
   list3.merge(list3, list3);  cout << endl << list3 << endl;   // not changed
   list3.merge(list3, list7);  cout << endl << list3 << endl; 

   List list8; 
   list8.intersect(list5, list6);  cout << endl << list8 << endl; 
   list6.intersect(list6, list6);  cout << endl << list6 << endl; 
   list6.intersect(list6, list7);  cout << endl << list6 << endl; 

   // needs more testing: retrieve and remove

   // now all the destructor calls should delete all the lists
   return 0;
}

