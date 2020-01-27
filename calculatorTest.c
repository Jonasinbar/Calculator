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
    int expectedErrorCode;
};

/**
 *  This fuction executes the function calculate() on one given test element and compare
 *  the expected result of the test element wit the result that 
 *  the fucntion calculate() gave us two int as input.
 *  in case of ERROR_CODE being raised, it returns -1 and we take care of this in our main function
 *  @param struct testElement, the test element to be evaluated
 *  @return 1 if our test element passed, 0 if test failed, -1 if an ERROR_CODE was raised during execution
 */
int runTestOnOneElement(struct testElement *testElement){
	ERROR_CODE = noError;//just to make sure
	//pointer to fucntion declaration
	double (*ptrCalculate) (char*, char, char*, int*, int*) = &calculate;
    int firstNbrInt,secondNbrInt;// these are our int buffers that will host the parsed input 
    double actualResult = (*ptrCalculate)(testElement->first, testElement->operator, testElement->second, &firstNbrInt, &secondNbrInt);
	if(ERROR_CODE){
		return -1;
	}
    return actualResult==testElement->expectedResult;
}

/**
 *  This fuction set values for a given struct passed by reference and returns this struct.
 *  @param struct testElement **, char* first, char operator, char* second, int error_code and
 *  double expectedResult, all values to put in the struct
 *  @return the given struct filled with given values
 */
static void setValues(struct testElement **testElement, char* first, char operator, char* second,
                      int error_code, double expectedResult) {
    (*testElement)->first = first;
    (*testElement)->second = second;
    (*testElement)->operator = operator;
    (*testElement)->expectedResult = expectedResult;
    (*testElement)->expectedErrorCode = error_code;
}
/**
 *  This fuction creates a test element and add it to our given list of test elements.
 *  @param currentTestNumber, so that we put the new test element in the right place in
 *  our test element list, struct testElement ** our list of test elements, passed by reference, 
 *  char* first, char operator, char* second, int error_code and double expectedResult, all values
 *  to put in the struct of the new test element 
 *  @return void
 */
void append(int *currentTestNumber, struct testElement **testElements, char* first, char operator, char* second,
            int shouldFail, double expectedResult) {
	//pointer to fucntion declaration
	void (*ptrSetValues)(struct testElement**, char*, char, char*, int, double) = &setValues;
    int temp = *currentTestNumber;
	(*ptrSetValues)(&testElements[temp], first, operator, second, shouldFail, expectedResult);
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
int main(){
	//pointer to fucntion declaration
	int (*ptrRunTestOnOneElement)(struct testElement*) = &runTestOnOneElement;
	int (*ptrMainForDemo)() = &mainForDemo;
	void (*ptrAppend)(int*, struct testElement**, char*, char, char*, int, double) = &append;
    int choice;
    printf("Hello, press \n 1 to run tests : \n 2 or any key to execute the program with your input : \n");
    scanf_s("%d",&choice,1);
    if(choice==1){//run tests
        struct testElement *testElements[NBR_OF_TESTS];//create a list of tests
        for (int i = 0; i < NBR_OF_TESTS; i++) {//alocate memory
            testElements[i]  = (struct testElement *)malloc(sizeof(struct testElement));
        }
        int currentTestNumber = 0;
        int false = 0; //for readability
        int true = 1;  //for readability
		int testPassed = true;
		// we dont really want to check if we threw the right error, 
		//just want to check that an error was thrown, 
		//we dont consider a wrong error code as a failing test,
		//but we still notice the user abou that
		int testPassedButWrongErrorIsTriggered = false;
		int allTestPassed = true;
		//here we create new test element in this manner
		(*ptrAppend)(&currentTestNumber, testElements,"1", '+', "2", noError, 3);
		(*ptrAppend)(&currentTestNumber, testElements, "1m", '+', "2",invalidInput, 0);
		(*ptrAppend)(&currentTestNumber, testElements,"99999", '^', "8", intOverflow, 0);
		(*ptrAppend)(&currentTestNumber, testElements,"11", '-', "20", noError, -9);
		(*ptrAppend)(&currentTestNumber, testElements,"14", '/', "0", divisionByZero, 0);
		(*ptrAppend)(&currentTestNumber, testElements,"10", '8', "3", invalidOperator, 1);
		(*ptrAppend)(&currentTestNumber, testElements,"14rrrrr", '/rrr', "7rrr", invalidOperator, 2);
		(*ptrAppend)(&currentTestNumber, testElements,"11", '/', "2", noError, 5.5);
		(*ptrAppend)(&currentTestNumber, testElements,"14", '/', "-7", invalidInput, 2);
		(*ptrAppend)(&currentTestNumber, testElements,"10", '-', "5", noError, 5);
        
        for (int i = 0; i < NBR_OF_TESTS; i++) {//for all test elements
            ERROR_CODE = noError;//reinitialiwe flag ERROR_CODE
			testPassed = (*ptrRunTestOnOneElement)(testElements[i]);//run test on each element 
            if(ERROR_CODE){
                testPassed = (testElements[i]->expectedErrorCode!=noError);
				testPassedButWrongErrorIsTriggered = (testElements[i]->expectedErrorCode != ERROR_CODE);
            }
            free(testElements[i]);
            ERROR_CODE = noError;//reinitialiwe flag ERROR_CODE
            if(!testPassed){
                printf("test %d failed!\n",i);
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
        return (*ptrMainForDemo)();
    }
    exit(0);
    return 0;
}

    


