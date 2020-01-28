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
#include <stdint.h>
#include <float.h>
#define MAXSIZEINPUT 10 //because the INT_MAX is 10 digit, if we have more that 10 digit, we have an overflow for sure.

enum errorCodes {
	noError=0, divisionByZero = 1, intOverflow = 2, invalidInput = 3, invalidOperator = 4
};
int chooseRightOperation(char);
char* getErroryName(enum Days day);
double add(int32_t firstInt, int32_t secondInt);
double calculate(char* firstStr, char operator, char* secondStr, int32_t* firstNbrInt, int32_t* secondNbrInt);
int32_t checkOverflowAndReturnResult(uint64_t result);
double divide(int32_t firstInt, int32_t secondInt);
double euclideanDivision(int32_t first, int32_t second);
double executeOperation(int32_t first, char operator, int32_t second);
int32_t inputIsValid(char* firstStr, char* secondStr, int32_t* firstNbrInt, int32_t* secondNbrInt);
double modulo(int32_t firstInt, int32_t secondInt);
double multiply(int32_t firstInt, int32_t secondInt);
double nthRoot(int32_t firstInt, int32_t secondInt);
double power(int32_t firstInt, int32_t secondInt);
void printResult(double result);
uint64_t stringConvertToLong(char* stringNbr);
double substract(int32_t firstInt, int32_t secondInt);
int32_t verifyNumbersAreInt(uint64_t firstLongNbr, uint64_t secondLongNbr);
void printError();
double mainForDemo();

#endif /* calculator_h */
