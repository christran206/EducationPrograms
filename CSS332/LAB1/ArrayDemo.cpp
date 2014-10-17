//
//  main.cpp
//  ArraysBS
//
//  Created by Rob Nash on 9/26/13.
//  Copyright (c) 2013 Rob Nash. All rights reserved.
//

#include <iostream>

void display(int data[], int size);
void bubble(int data[], int size);
void swap(int data[], int idx1, int idx2);

int main(int argc, const char * argv[])
{
    const int SIZE = 7;
    int set[] = {1,4,3,2,5,9,8};
    
    display(set, SIZE);
    bubble(set, SIZE);
    display(set,SIZE);
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

void display(int data[], int size) {
    for(int i =0; i < size; i++) {
        std::cout << data[i] << ",";
    }
    std::cout << std::endl;
}

void bubble(int data[], int size) {
    for(int i = 0; i < size; i++) {
        for(int k = 0; k <size-1-i; k++) {
            if(data[k]<data[k+1]) {
                swap(data,k,k+1);
            }
        }
    }
}

void swap(int data[], int idx1, int idx2) {
    int temp = data[idx1];
    data[idx1] = data[idx2];
    data[idx2] = temp;
}

