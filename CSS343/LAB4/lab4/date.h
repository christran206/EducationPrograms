/*---------------------------------------------------------------------------
Date
Container Class for storage of time with the accuracy down to a full second
   
Features:
    -- Retrive Each Atrribute of Time(Year, Month, Day, Hour, Minite, Second)
    -- Set Each Attribute of Time
    -- Implements the output<< operator
Assumptions:
    -- If attempting to set a value beyond the maximum value that can be held
        then the number will be MOD of that number, 68 minutes will store 8
---------------------------------------------------------------------------*/
#ifndef DATE
#define DATE

#include <string>
#include <iostream>
using namespace std;

class Date {
public:
    Date(int year = 0, int month = 0, int day = 0, int hour = 0, 
        int minute = 0, int second = 0);
     ~Date();

     int getYear();
     void setYear(int);
     int getMonth();
     void setMonth(int);
     int getDay();
     void setDay(int);
     int getHour();
     void setHour(int);
     int getMinute();
     void setMinute(int);
     int getSecond();
     void setSecond(int);

private:
     int year, month, day, hour, minute, second;

};

#endif