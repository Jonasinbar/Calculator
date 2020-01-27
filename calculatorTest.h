//
//  calculatorTest.h
//  Calculator
//
//  Created by Jonas on 25/01/2020.
//  Copyright � 2020 Jonas. All rights reserved.
//

#ifndef calculatorTest_h
#define calculatorTest_h
#include <stdio.h>
extern int ERROR_CODE;
void append(int* currentTestNumber, struct testElement** testElements, char* first, char operator, char* second, int shouldFail, double expectedResult);
int main();
int runTestOnOneElement(struct testElement* testElement);
static void setValues(struct testElement** testElement, char* first, char operator, char* second, int shouldFail, double expectedResult);


#endif /* calculatorTest_h */
