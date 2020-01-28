//
//  calculatorTest.h
//  Calculator
//
//  Created by Jonas on 25/01/2020.
//  Copyright © 2020 Jonas. All rights reserved.
//

#ifndef calculatorTest_h
#define calculatorTest_h
//#include <cstdint>
#include <stdio.h>
#include <stdint.h>
extern int32_t ERROR_CODE;
void append(int32_t* currentTestNumber, struct testElement** testElements, char* first, char operator, char* second, int32_t shouldFail, double expectedResult);
int32_t main();
int32_t runTestOnOneElement(struct testElement* testElement);
static void setValues(struct testElement** testElement, char* first, char operator, char* second, int32_t shouldFail, double expectedResult);


#endif /* calculatorTest_h */
