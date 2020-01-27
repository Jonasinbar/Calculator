//
//  calculator.h
//  Calculator
//
//  Created by Jonas on 25/01/2020.
//  Copyright © 2020 Jonas. All rights reserved.
//

#ifndef calculator_h
#define calculator_h

#include <stdio.h>
#include <stdlib.h> //for exit()
#include <limits.h> //for INT_MAX
#include <string.h> //for strspn and strlen
#include <math.h> // for pow
#define MAXSIZEINPUT 10 //because the INT_MAX is 10 digit, if we have more that 10 digit, we have an overflow for sure.

enum errorCodes {
	noError=0, divisionByZero = 1, intOverflow = 2, invalidInput = 3, invalidOperator = 4
};

char* getErroryName(enum Days day);
int add(int firstInt, int secondInt);
double calculate(char* firstStr, char operator, char* secondStr, int* firstNbrInt, int* secondNbrInt);
int checkOverflowAndReturnResult(long long result);
double divide(int firstInt, int secondInt);
int euclideanDivision(int first, int second);
double executeOperation(int first, char operator, int second);
int inputIsValid(char* firstStr, char* secondStr, int* firstNbrInt, int* secondNbrInt);
int modulo(int firstInt, int secondInt);
int multiply(int firstInt, int secondInt);
double nthRoot(int firstInt, int secondInt);
int power(int firstInt, int secondInt);
int mainForDemo();
void printResult(double result);
long long stringConvertToLong(char* stringNbr);
int substract(int firstInt, int secondInt);
int verifyNumbersAreInt(long long firstLongNbr, long long secondLongNbr);
void printError();
int mainForDemo();

#endif /* calculator_h */
