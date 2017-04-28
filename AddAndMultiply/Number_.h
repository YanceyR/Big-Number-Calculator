//
//  ==========================================================================
//
//  Number_.h
//
//  Owner: Yancey Reid
//  Program: AddAndMultiply
//  Date Created: 2/19/17
//
//  Copyright © 2017 Yancey Reid. All rights reserved.
//
//  ==========================================================================
//

#ifndef Number__h
#define Number__h

#include <stdio.h>
#include <iostream>
#include "Constants_.h"

using namespace std;
struct Number
{
    string formatted_number;
    int number_array[DIGITS_MAX * 2];
    int number_length = 0;
    
    Number();
    void SetNumber(string);
    void FormatNumber();
    void AddNumber(Number);
};

#endif /* Number__h */
