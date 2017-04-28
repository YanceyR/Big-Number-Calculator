//
//  ==========================================================================
//
//  Number_.cpp
//
//  Owner: Yancey Reid
//  Program: AddAndMultiply
//  Date Created: 2/19/17
//
//  Copyright © 2017 Yancey Reid. All rights reserved.
//
//  ==========================================================================
//

#include <stdio.h>
#include <iostream>
#include "Number_.h"

using namespace std;


//
//  ==========================================================================
//
//  Assigns every element in number_array to 0.
//
//  ==========================================================================
//
Number::Number()
{
    for (int i = 0; i < DIGITS_MAX * 2; i++)
    {
        number_array[i] = 0;
    }
}


//
//  ==========================================================================
//
//  Assigns the number_array to the number being passed with the ones place
//  starting at index 0.
//
//  ==========================================================================
//
void Number::SetNumber(string num_to_set)
{
    string temp_num;
    bool found = false;
    
    if (num_to_set[0] == '0')
    {
        for (int i = 0; i < num_to_set.length();  i++)
        {
            if (num_to_set[i] != '0')
                found = true;
            
            if (found)
                temp_num += num_to_set[i];
        }
        
        if (!found)
            temp_num = "0";
        
        num_to_set = temp_num;
    }
    
    number_length = num_to_set.length();
    
    for (int i = number_length - 1; i >= 0; i--)
    {
        number_array[(number_length - 1) - i] = num_to_set[i] - '0';
    }
}


//
//  ==========================================================================
//
//  Formats the string representation of the number_arr with commas.
//
//  ==========================================================================
//
void Number::FormatNumber()
{
    formatted_number.erase();
    
    for (int i = 0; i < number_length; i++)
    {
        formatted_number = char(number_array[i] + '0') + formatted_number;
        
        if ((i + 1) % 3 == 0 && i != number_length - 1)
            formatted_number = ',' + formatted_number;
    }
}


//
//  ==========================================================================
//
//  Adds the number to the current instance digit-by-digt.
//
//  ==========================================================================
//
void Number::AddNumber(Number num_to_add)
{
    int max_length;
    int remainder = 0;
    int temp_sum = 0;
    Number total_sum;
    
    if (number_length >= num_to_add.number_length)
        max_length = number_length;
    else
        max_length = num_to_add.number_length;
    
    for (int i = 0; i < max_length; i++)
    {
        temp_sum = number_array[i] + num_to_add.number_array[i] + remainder;
        
        if (temp_sum < 10)
        {
            total_sum.number_array[i] = temp_sum;
            total_sum.number_length++;
            remainder = 0;
        }
        else
        {
            total_sum.number_array[i] = temp_sum % 10;
            total_sum.number_length++;
            remainder = temp_sum / 10;
        }
    }
    
    if (remainder != 0)
    {
        total_sum.number_array[max_length] = remainder;
        total_sum.number_length++;
    }
    
    *this = total_sum;
}
