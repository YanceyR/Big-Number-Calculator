//
//  ==========================================================================
//
//  main.cpp
//
//  Owner: Yancey Reid
//  Program: AddAndMultiply
//  Date Created: 2/19/17
//
//  Copyright © 2017 Yancey Reid. All rights reserved.
//
//  ==========================================================================
//

#include <iostream>
#include "Constants_.h"
#include "Number_.h"

using namespace std;

bool ValidateAmount(string);
bool ValidateNumber(string);
void PrintNumbers(Number[], int, int, char);
Number AddNumbers(Number[], int);
Number MultiplyFirstTwoNumbers(Number[], Number[]);


//
//  ==========================================================================
//
//  Driver for program. Requests numbers, adds the numbers, multiplies the
//  first two numbers, and prints the intermediate steps with answer.
//
//  ==========================================================================
//
int main()
{
    unsigned int number_amount;
    unsigned int product_amount = 2;
    string holder;
    Number sum, product;
    Number numbers[NUMBERS_MAX];
    Number product_additions[DIGITS_MAX];
    
    cout << " - This program adds " << NUMBERS_MIN << " through " << NUMBERS_MAX << " very large numbers." << endl;
    cout << " - It multiplies the first two numbers showing the intermediate steps." << endl;
    cout << " - Numbers must have between " << DIGITS_MIN << " and " << DIGITS_MAX << " digits." << endl;
    cout << endl << endl;
    
    cout << "Enter amount of numbers: ";
    getline(cin, holder);
    cout << endl;
    
    while (ValidateAmount(holder))
    {
        cout << endl;
        holder.clear();
        cout << "Invalid amount, please re-enter: ";
        getline(cin, holder);
    }
    
    number_amount = stoi(holder);
    
    for (int i = 0; i < number_amount; i++)
    {
        cout << "Enter number #" << i + 1 << ": ";
        getline(cin, holder);
        
        while (ValidateNumber(holder))
        {
            cout << endl;
            holder.clear();
            cout << "Invalid number, please re-enter: ";
            getline(cin, holder);
        }
        
        numbers[i].SetNumber(holder);
        cout << endl;
    }
    
    cout << endl;
    cout << "The sum of: \n" << endl;

    sum = AddNumbers(numbers, number_amount);
    sum.FormatNumber();
    
    PrintNumbers(numbers, number_amount, sum.formatted_number.length(), '+');
    cout << string(SPACE_OFFSET, ' ') << sum.formatted_number << endl;
    
    cout << endl;
    cout << "The product of: \n" << endl;
    
    product = MultiplyFirstTwoNumbers(numbers, product_additions);
    product.FormatNumber();
    
    PrintNumbers(numbers, product_amount, product.formatted_number.length(), '*');
    PrintNumbers(product_additions, numbers[1].number_length, product.formatted_number.length(), '+');
    
    if (numbers[0].formatted_number == "0" || numbers[1].formatted_number == "0")
        cout << string(SPACE_OFFSET + product.formatted_number.length() - 1, ' ') << 0;
    else
        cout << string(SPACE_OFFSET, ' ') << product.formatted_number << endl;

    cout << endl << endl;;
    
    return 0;
}


//
//  ==========================================================================
//
//  Validates that input is a number and is between the numbers min and max.
//
//  ==========================================================================
//
bool ValidateAmount(string num_str)
{
    bool error = (num_str.size() == 0);
    
    for (int i = 0; i < num_str.size() && !error; i++)
    {
        error = (num_str[i] < '0' || num_str[i] > '9');
    }
    
    if (!error)
        error = (stoi(num_str) < NUMBERS_MIN || stoi(num_str) > NUMBERS_MAX);
    
    return error;
}


//
//  ==========================================================================
//
//  Validates that input is a number and is between the digits min and max.
//
//  ==========================================================================
//
bool ValidateNumber(string num_str)
{
    bool error = (num_str.size() < DIGITS_MIN || num_str.size() > DIGITS_MAX);
    
    for (int i = 0; i < num_str.size() && !error; i++)
    {
        error = (num_str[i] < '0' || num_str[i] > '9');
    }
    
    return error;
}


//
//  ==========================================================================
//
//  Prints a number array, a given symbol, and a line.
//
//  ==========================================================================
//
void PrintNumbers(Number numbers[], int amount_of_numbers, int format_length, char symbol)
{
    for (int i = 0; i < amount_of_numbers; i++)
    {
        if (i != amount_of_numbers - 1)
            cout << string(SPACE_OFFSET, ' ');
        else
            cout << symbol << ")" << string(SPACE_OFFSET - 2, ' ');
        
        numbers[i].FormatNumber();
        
        cout << string(format_length - numbers[i].formatted_number.length(), ' ');
        cout << numbers[i].formatted_number;
        cout << endl;
    }
    
    cout << string(format_length + SPACE_OFFSET, '-') << endl;
}


//
//  ==========================================================================
//
//  Adds all the numbers in a Number array.
//
//  ==========================================================================
//
Number AddNumbers(Number numbers[], int number_amount)
{
    Number sum = numbers[0];
    
    for (int i = 1; i < number_amount; i++)
    {
        sum.AddNumber(numbers[i]);
    }

    return sum;
}


//
//  ==========================================================================
//
//  Multiplies the first two numbers in a Number array.
//
//  ==========================================================================
//
Number MultiplyFirstTwoNumbers(Number numbers_to_multiply[], Number numbers_to_add[])
{
    int remainder, temp_sum;
        
    for (int i = 0; i < numbers_to_multiply[1].number_length; i++)
    {
        numbers_to_add[i].number_length += i;
        remainder = 0;
        
        for (int k = 0; k < numbers_to_multiply[0].number_length; k++)
        {
            temp_sum = numbers_to_multiply[1].number_array[i] * numbers_to_multiply[0].number_array[k];
            temp_sum += remainder;
            remainder = 0;
            
            if (temp_sum > 9)
            {
                numbers_to_add[i].number_array[k + i] = temp_sum % 10;
                remainder = temp_sum / 10;
            }
            else
            {
                numbers_to_add[i].number_array[k + i] = temp_sum;
            }
            
            numbers_to_add[i].number_length++;
        }
        
        if (remainder != 0)
        {
            numbers_to_add[i].number_array[numbers_to_multiply[0].number_length + i] = remainder;
            numbers_to_add[i].number_length++;
        }
    }
    
    return AddNumbers(numbers_to_add, numbers_to_multiply[1].number_length);
}
