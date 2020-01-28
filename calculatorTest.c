//
//  calculatorTest.c
//  Calculator
//
//  Created by Jonas on 25/01/2020.
//  Copyright © 2020 Jonas. All rights reserved.
//
#include "calculator.h"
#include "calculatorTest.h"

#define NBR_OF_TESTS 10
ERROR_CODE= noError; //global variable

/**
 * This struct represent one test element : the two numer as string, the operator and 
 * the expected reslut, we added the variable "errorCode because if we give by purpose
 * a wrong inpput, we expect during the flow, we raise the flag ERROR_CODE, then we dont
 * want to see the result but compare the expected error with the actual error
 */
struct testElement {
    char *first;
    char operator;
    char *second;
    double expectedResult;
    int32_t expectedErrorCode;
};

/**
 *  This fuction executes the function calculate() on one given test element and compare
 *  the expected result of the test element wit the result that 
 *  the fucntion calculate() gave us two int32_t as input.
 *  in case of ERROR_CODE being raised, it returns -1 and we take care of this in our main function
 *  @param struct testElement, the test element to be evaluated
 *  @return 1 if our test element passed, 0 if test failed, -1 if an ERROR_CODE was raised during execution
 */
double runTestOnOneElement(struct testElement *testElement){
	ERROR_CODE = noError;//just to make sure
	//pointer to fucntion declaration
	double (*ptrCalculate) (char*, char, char*, int32_t*, int32_t*) = &calculate;
    int32_t firstNbrInt,secondNbrInt;// these are our int32_t buffers that will host the parsed input 
    double actualResult = (*ptrCalculate)((*testElement).first, (*testElement).operator, (*testElement).second, &firstNbrInt, &secondNbrInt);
	if(ERROR_CODE){
		return -1;
	}
    return actualResult== (*testElement).expectedResult;
}

/**
 *  This fuction set values for a given struct passed by reference and returns this struct.
 *  @param struct testElement **, char* first, char operator, char* second, int32_t error_code and
 *  double expectedResult, all values to put in the struct
 *  @return the given struct filled with given values
 */
static void setValues(struct testElement *testElement, char* first, char operator, char* second,
                      int32_t error_code, double expectedResult) {
    (*testElement).first = first;
    (*testElement).second = second;
    (*testElement).operator = operator;
    (*testElement).expectedResult = expectedResult;
    (*testElement).expectedErrorCode = error_code;
}
/**
 *  This fuction creates a test element and add it to our given list of test elements.
 *  @param currentTestNumber, so that we put the new test element in the right place in
 *  our test element list, struct testElement ** our list of test elements, passed by reference, 
 *  char* first, char operator, char* second, int32_t error_code and double expectedResult, all values
 *  to put in the struct of the new test element 
 *  @return void
 */
void append(int32_t *currentTestNumber, struct testElement **testElements, char* first, char operator, char* second,
            int32_t shouldFail, double expectedResult) {
	//pointer to fucntion declaration
	void (*ptrSetValues)(struct testElement**, char*, char, char*, int32_t, double) = &setValues;
    int32_t temp = *currentTestNumber;
	(*ptrSetValues)(testElements[temp], first, operator, second, shouldFail, expectedResult);
    *currentTestNumber = temp + 1;
}



/**
 *  This is our main function, it asks from the user if he wants to run all tests or execute 
 *  the program with his own input
 *  In case we wants to run the testsHere we create some tests element, and put them in our list of test elements, then we check 
 *  if for all test element the program works as expected and prints the corresponding message.
 *  In case he wants to execute the program with his own input we call the function MainForDemo()
 *  @return void
 */
int32_t main() {
	printf("%f\n", DBL_MAX);
	double a = 2147483647;
	double b = 2147483647;
	double c = a * b;
	int32_t choice;

	printf("Hello, press \n 1 to run tests : \n 2 or any key to execute the program with your input : \n");

	scanf_s("%d", &choice, 1);

	//run tests
	if (choice == 1)
	{
		struct testElement* testElements[NBR_OF_TESTS];//create a list of tests   
		for (int32_t i = 0; i < NBR_OF_TESTS; i++) {//alocate memory
			testElements[i] = (struct testElement*)malloc(sizeof(struct testElement));
		}
		int32_t currentTestNumber = 0;
		int32_t false = 0; //for readability
		int32_t true = 1;  //for readability
		int32_t testPassed = true;
		// we dont really want to check if we threw the right error, 
		//just want to check that an error was thrown, 
		//we dont consider a wrong error code as a failing test,
		//but we still notice the user abou that
		
		int32_t testPassedButWrongErrorIsTriggered = false;
		int32_t allTestPassed = true;
		//here we create new test element in this manner
		append(&currentTestNumber, testElements, "1", '+', "2", noError, 3);
		append(&currentTestNumber, testElements, "1m", '+', "2", invalidInput, 0);
		append(&currentTestNumber, testElements, "99999", '^', "8", intOverflow, 0);
		append(&currentTestNumber, testElements, "11", '-', "20", noError, -9);
		append(&currentTestNumber, testElements, "14", '/', "0", divisionByZero, 0);
		append(&currentTestNumber, testElements, "10", '8', "3", invalidOperator, 1);
		append(&currentTestNumber, testElements, "14rrrrr", '/rrr', "7rrr", invalidOperator, 2);
		append(&currentTestNumber, testElements, "2", 94, "8", noError, 256);//94 is '^' for some reason if ypu put ^ directly is gives another charcter
		append(&currentTestNumber, testElements, "14", '/', "-7", invalidInput, 2);
		append(&currentTestNumber, testElements, "9", '/', "2", noError, 4.5);

		for (int32_t i = 0; i < NBR_OF_TESTS; i++) {//for all test elements
			ERROR_CODE = noError;//reinitialiwe flag ERROR_CODE
			testPassed = runTestOnOneElement(testElements[i]);//run test on each element 
			
			if (ERROR_CODE) {
				testPassed = (testElements[i]->expectedErrorCode != noError);
				testPassedButWrongErrorIsTriggered = (testElements[i]->expectedErrorCode != ERROR_CODE);
			}
			free(testElements[i]);
			ERROR_CODE = noError;//reinitialiwe flag ERROR_CODE
			
			if (!testPassed) {
				printf("test %d failed!\n", i);
				testPassedButWrongErrorIsTriggered = false;
				allTestPassed = false;
			}
			
			if (testPassedButWrongErrorIsTriggered) {
				//notice the user but we dont consider it as a fail
				printf("test %d passed but wrong error is triggered!\n", i);
				testPassedButWrongErrorIsTriggered = false;
			}
		}
		
		if (allTestPassed) {
			printf("All tests passed! congrats!\n");
		}
	}
    else{//no test, personalized input
        return mainForDemo();
    }
    exit(0);
    return 0;
}

    


