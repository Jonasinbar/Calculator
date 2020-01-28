//
//  calculator.c
//  Calculator
//
//  Created by Jonas on 25/01/2020.
//  Copyright © 2020 Jonas. All rights reserved.
//

#include "calculator.h"
#include "calculatorTest.h"

/**
 *  This fuction takes a uint64_t number and checks
 *  if it is bigger than INT32_MAX, that is, it checks
 *  if result can be contained in an int32_t without overflowing
 *  it returns its input as an int32_t if result can be contained in
 *  an int32_t witout overflowing, else it returns -1 that will never be taken
 *  into account because flag NO_ERROR will be assigned to 1.
 *  @param long result, the numer to be checked.
 *  @return the input as an ,int32_t or -1 and raise flag NO_ERROR.
 */
int32_t checkOverflowAndReturnResult(uint64_t result) {
	if (result > INT32_MAX) {
		ERROR_CODE = intOverflow;
		return -1;//doesnt matter
	}
	return (int32_t)result;
}

/**
 *  This fuction takes two int32_t as input, calculate their sum as a
 *  uint64_t and call the fucntion checkOverflowAndReturnResult
 *  that will return the input as int32_t if the result does not int32_t overflow,
 *  or it will return -1 and raise flag NO_ERROR so that
 *  the result will not be taked into account.
 *  @param int32_t firstInt, int32_t secondInt, the numbers to be added.
 *  @return the sum of the numbers as int32_t, or -1 and raise flag NO_ERROR.
 */
double add(int32_t firstInt, int32_t secondInt) {
	//pointer to fucntion declaration
	int32_t (*ptrCheckOverflowAndReturnResult)(uint64_t) = &checkOverflowAndReturnResult;
	uint64_t result = (uint64_t)firstInt + (uint64_t)secondInt;
	return (double)(*ptrCheckOverflowAndReturnResult)(result);
}

/**
 *  This fuction takes two int32_t as input, calculate their substraction
 *  and return the result, note that in our case, substract
 *  cannot int32_t overflow because it takes as input two positive ints < INT32_MAX
 *  @param int32_t firstInt, int32_t secondInt, the numbers to be substracted.
 *  @return firstInt - secondInt, the substraction as int32_t.
 */
double substract(int32_t firstInt, int32_t secondInt) {
	return (double)firstInt - (double)secondInt;
}

/**
 *  This fuction takes two int32_t as input, calculate their multiplication as a
 *  long and call the fucntion checkOverflowAndReturnResult
 *  that will return the input as int32_t if the result does not int32_t overflow,
 *  or it will return -1 and raise flag NO_ERROR so that
 *  the result will not be taked into account
 *  note that INT32_MAX*INT32_MAX < LLONG_MAX, then result cannot llong overflow.
 *  @param int32_t firstInt, int32_t secondInt, the numbers to be multiply.
 *  @return the multiplication of the number as int32_t, or -1 and raise flag NO_ERROR.
 */
double multiply(int32_t firstInt, int32_t secondInt) {
	//pointer to fucntion declaration
	int32_t (*ptrCheckOverflowAndReturnResult)(uint64_t) = &checkOverflowAndReturnResult;
	uint64_t result = (uint64_t)firstInt * (uint64_t)secondInt;
	return (*ptrCheckOverflowAndReturnResult)(result);
}

/**
 *  This fuction takes two int32_t as input, calculate their division as a
 *  double. Note that in our case, divide cannot double overflow because it takes
 *  as input two ints < INT32_MAX and whole numers.
 *  if case of division by 0, we will return -1 and raise flag NO_ERROR so that
 *  the result will not be taked into account.
 *  @param int32_t firstInt, int32_t secondInt, the numbers to be divided.
 *  @return the division of the number as double, or -1 and raise flag NO_ERROR.
 */
double divide(int32_t firstInt, int32_t secondInt) {
	if (secondInt == 0) {
		ERROR_CODE = divisionByZero;
		return -1;//doesnt matter
	}
	return (double)firstInt / (double)secondInt;
}

/**
 *  This fuction takes two int32_t as input, calculate their modulo
 *  and return the result, note that in our case, modulo
 *  cannot int32_t overflow because it takes as input two positive ints < INT32_MAX
 *  @param int32_t firstInt, int32_t secondInt, the numbers to be substracted.
 *  @return firstInt % secondInt, the modulo as int32_t.
 */
double modulo(int32_t firstInt, int32_t secondInt) {
	if (secondInt == 0) {
		ERROR_CODE = divisionByZero;
		return -1;//doesnt matter
	}
	return (double)(firstInt % secondInt);
}

/**
 *  This fuction takes two int32_t as input, calculate and return
 *  the first int32_t to the power of the second, as an int32_t.
 *  To do so, we call our fucntion multiply() 'secondInt' times.
 *  Our fuction multiply() is safe from overflow, that is,
 *  if the result cannot be contained in an int32_t it will raise the flag NO_ERROR
 *  then we will stop our loop and wont take the result into consideration
 *  thus, power() will return the result as int32_t iff the result does not int32_t overflow,
 *  or it will return -1 and raise flag NO_ERROR through the function multiply() so that
 *  the result will not be taked into account afterwords
 *  @param int32_t firstInt, the base and int32_t secondInt the exponent.
 *  @return the powering of the number as int32_t, or -1 and flag NO_ERROR will be raised.
 */
double power(int32_t firstInt, int32_t secondInt) {
	
	//basic case, power of 0 
	if (secondInt == 0) {
		return 1;
	}
	//basic case, power of 1
	if (secondInt == 1) {
		return firstInt;
	}
	int32_t result = firstInt;
	//here we do firstInt*firstInt*...*firstInt, 'secondInt' times
	for (int32_t i = 0; i < secondInt - 1; ++i)
	{
		result = multiply((int)result, firstInt); //our multiply is safe from int32_t overflow
		//if flag errorCode was raised by multiply, we better stop now
		if (ERROR_CODE) {
			return -1; //doesnt matter
		}
	}
	return (double)result;
}
/**
 *  This fuction takes two int32_t as input, calculate the secondInt'th root of firstInt as a
 *  double. To do se, is uses the fuction pow() from math.h
 *  as both numbers are positive ints < INT32_MAX, the result can't overflow here
 *  @param int32_t firstInt, the base, int32_t secondInt the nth root.
 *  @return the secondInt'th root of firstInt as a double
 */
double nthRoot(int32_t firstInt, int32_t secondInt) {
	//as both numbers are positive ints, the result can't overflow here
	// not that the nth root of x is equal to x to the power of 1/n
	return pow((double)firstInt, 1.0 / (double)secondInt);
}


/**
 *  This fuction takes two int32_t as input, calculate their euclideanDivision as a
 *  int32_t. Note that in our case, euclideanDivision cannot int32_t overflow because it takes
 *  as input two ints < INT32_MAX and whole numers.
 *  if case of euclideanDivision by 0, we will return -1 and raise flag NO_ERROR so that
 *  the result will not be taked into account.
 *  @param int32_t firstInt, int32_t secondInt, the numbers to be divided.
 *  @return the division of the number as double, or -1 and raise flag NO_ERROR.
 */
double euclideanDivision(int32_t first, int32_t second) {
	if (second == 0) {
		ERROR_CODE = divisionByZero;
		return -1;//doesnt matter
	}
	return first / second;
}

int chooseRightOperation(char operator) {
	switch (operator) {
	case '+':
		return 0;
		break;
	case '-':
		return 1;
		break;
	case '*':
		return 2;
		break;
	case '/':
		return 3;
		break;
	case '%':
		return 4;
		break;
	case 'r':
		return 5;
		break;
	case '^':
		return 6;
		break;
	case ':':
		return 7;
		break;
	default:
		// if operator is not in the set {+, -, *, /, %, r, ^, :}
		ERROR_CODE = invalidOperator;
		return -1;//doesnt matter
	}
}
/**
 *  This fuction takes two int32_t as input and the operator,
 *  it chooses the right fucntion to use according to the operator and return
 *  the result of the corresponding operation
 *  if the operator doesnt belong to {+, -, *, /, %, r, ^, :}
 *  we will return -1 and raise flag NO_ERROR so that
 *  the result will not be taked into account.
 *  @param int32_t firstInt, int32_t secondInt, the numbers to be operated, and char operator, the operator.
 *  @return the division of the number as double, or -1 and raise flag NO_ERROR
 *  through called operation fucntion or in case of operator not recongnized.
 */
double executeOperation(int32_t first, char operator, int32_t second) {
	double (*fun_ptr_arr[])(int32_t, int32_t) = { add, substract, multiply, divide, modulo, nthRoot, power, euclideanDivision };
	int rightOperationNumber = chooseRightOperation(operator);
	if (rightOperationNumber == -1) {
		return -1; //doesnt matter, in this case ERROR_CODE flage is raised
	}
	return (*fun_ptr_arr[rightOperationNumber])(first, second);
}


/**
 *  This fuction takes a string as input,
 *  and return is as a uint64_t int32_t.
 *  it also checks if it is really a number represented in a string,
 *  if not it raises flag ERROR_CODE and returns -1 that will not be taken into account
 *  @param char* stringNbr, the string to be parsed into a uint64_t int32_t.
 *  @return the parsed string as a uint64_t int32_t or -1 and raise flage ERROR_CODE.
 */
uint64_t stringConvertToLong(char* stringNbr) {
	uint64_t number = 0;
	for (int i = 0; i < strnlen(stringNbr, MAXSIZEINPUT); i++) {
		if ((stringNbr[i] >= '0') && (stringNbr[i] <= '9')) {
			number = (number*10) + (stringNbr[i] - '0');
		}

		else {
			//stringNbr is not really a number
			ERROR_CODE = invalidInput;
			return -1;//doesnt matter
		}
	}
	/*for (char* digit = stringNbr; *digit; ++digit)
	{
		if( *digit >= '0' && *digit <= '9' ){
		number = number * 10 + *digit - '0';
		}
		
		else{
			//stringNbr is not really a number
			ERROR_CODE = invalidInput;
			return -1;//doesnt matter
		}
	}*/
	return number;
}
/**
 *  This fuction takes a two uint64_t ints as input,
 *  and checks if they can be contained in an int32_t if so, it returns 1.
 *  if one of the inputs int32_t-overflows, it returns 0
 *  @param firstLongNbr and secondLongNbr, the number that we check the dont int32_t-overflow.
 *  @return 1 if the numbers are not int32_t-overflowing, 0 else
 */
int32_t verifyNumbersAreInt(uint64_t firstLongNbr, uint64_t secondLongNbr) {
	return !(firstLongNbr > INT32_MAX || secondLongNbr > INT32_MAX);
}


/**
 *  This fuction takes as input : the two input as string : firstStr and secondStr
 *  plus two int32_t buffer : firstNbrInt and secondNbrInt that are passed by reference that
 *  will contain the int32_t parsed value of the the input strng respectively, in case the two string
 *  are really string representation of numbers, not longer than MAXSIZEINPUT, not negative,
 *  whole numbers and not int32_t-Overflowing
 *  If the two input strings respect all the rules that we just described, it put their value as
 *  int32_t the buffers firstNbrInt and secondNbrInt and return 1 else 0.
 *  if one of the inputs int32_t-overflows, it returns 0
 *  @param "firstStr" and "secondStr" the string to check if their parsed values can be contained 
 *  in an int32_t and if they are valid, we put the int32_t representation of firstStr in the input int32_t buffer "firstNbrInt",
 *  the same for secondStr that we put in "secondNbrInt"
 *  @return 1 if firstStr and secondStr can be parsed into an int32_t, 0 else
 */
int32_t inputIsValid(char* firstStr, char* secondStr, int32_t* firstNbrInt, int32_t* secondNbrInt) {
	//pointer to fucntion declaration
	int32_t (*ptrVerifyNumbersAreInt)(uint64_t, uint64_t) = &verifyNumbersAreInt;
	uint64_t (*ptrStringConvertToLong)(char*) = &stringConvertToLong;

	
	if (strnlen(firstStr, MAXSIZEINPUT + 1) > MAXSIZEINPUT
		|| strnlen(secondStr, MAXSIZEINPUT + 1) > MAXSIZEINPUT) {
		ERROR_CODE = invalidInput;
		return 0;
	}
	//we dont support negative numbers
	if (firstStr[0] == '-' || secondStr[0] == '-') {
		ERROR_CODE = invalidInput;
		return 0;
	}
	//here we check if firstStr and secondStr are made only of digits
	size_t spanFirst = strspn(firstStr, "0123456789");
	size_t spanSecond = strspn(secondStr, "0123456789");
	if (spanFirst != strnlen(firstStr, MAXSIZEINPUT)
		|| spanSecond != strnlen(secondStr, MAXSIZEINPUT)) {
		ERROR_CODE = invalidInput;
		return 0;
	}
	//here we parse our strings into uint64_t and check if they int32_t-overflow
	uint64_t firstLongNbr = (*ptrStringConvertToLong)(firstStr);
	uint64_t secondLongNbr = (*ptrStringConvertToLong)(secondStr);
	if (!(*ptrVerifyNumbersAreInt)(firstLongNbr, secondLongNbr)) {
		ERROR_CODE = intOverflow;
		return 0;
	}
	
	//if everything went well, we fill up our two int32_t buffers that were passed by reference and return 1
	*firstNbrInt = (int32_t)firstLongNbr;
	*secondNbrInt = (int32_t)secondLongNbr;
	return 1;
}

/**
 *  This is our main function : This fuction takes as input : the operator, the two input as string : firstStr and secondStr
 *  plus two int32_t buffer : firstNbrInt and secondNbrInt that are passed by reference that
 *  will contain the int32_t parsed value of the the input strng respectively, and that will, if the two strings are "valid" 
 *  call the funtion executeOperation with the two int32_t that were passed by reference and that will
 *  give us the result of the operation of raise the flaf ERROR_CODE if something went wrong
 *  (for example int32_t overflow) if the input is not valid, it raises flag ERROR_CODE and returns -1 that will
 *  not be taken into account, if the input is valid, it returns the result of the operation as a double.
 *  @param "firstStr" and "secondStr" the string that contains the input from the user, the char "operator" got from the user,
 *  "firstNbrInt" and "firstNbrInt", the int32_t buffer that will contain the parsed value the strings as int32_t
 *  @return if the input is not valid, it raises flag ERROR_CODE and returns -1 that will
 *  not be taken into account, if the input is valid, it returns the result of the operation as a double.
 */
double calculate(char* firstStr, char operator, char* secondStr,
		int32_t* firstNbrInt, int32_t* secondNbrInt) {

	if (inputIsValid(firstStr, secondStr, firstNbrInt, secondNbrInt)) {
		return executeOperation(*firstNbrInt, operator, *secondNbrInt);
	}
	else {
		ERROR_CODE = invalidInput;
		return -1;//doesnt matter

	}
	
}
/**
 *  This fuction is supposed to print the details of an error in case there is one according to ERROR_CODE, a global int32_t variable.
 *  @param no parameters, it looks at ERROR_CODE, a global int32_t variable.
 *  @return void, just prints informations to the user
 */
void printError() {
	switch (ERROR_CODE)
	{
	case divisionByZero:
		printf("Failed: can't divide by 0 \n");
		break;
	case intOverflow:
		printf("Failed: int32_t Overflow\n");
		break;
	case invalidInput:
		printf("Failed: invalid input \nOnly positive int32_t are accepted\n");
		break;
	case invalidOperator:
		printf("Failed: invalid operator \nOnly {+, -, *, /, %, r, ^, :} are supported\n");
		break;
	default:
		printf("Failed\n");
	}
}

/**
 *  This fuction is supposed to print either the result or the details of an error in case there is one.
 *  In case there is no error the function just allows us to get rid of the .0000 in case of result being int32_t:
 * for example, in case of 1+2 the result is a doble and will print "3.000", this function prints 3 "instead"
 *  @param no parameters, it looks at ERROR_CODE, a global int32_t variable.
 *  @return void, just prints informations to the user
 */
void printResult(double result) {
	//pointer to fucntion declaration
	void (*ptrPrintError)() = &printError;
	if (ERROR_CODE) {
		(*ptrPrintError)();
	}
	else if ((int32_t)result == result) {//we geck if restult is a whole number
		int32_t resultInt = (int32_t)result;
		printf("%d\n", resultInt);//to get rid of the .0000 in case of result being int32_t
	}
	else {
		printf("%f\n", result);
	}
}
/**
 *  This is the main() function we call in case we dont want to run tests and want to execute 
 *  the prgram with our own inputs. It asks for the two nubers and the operator, 
 
 */
double mainForDemo() {
	char operator = ' ';
	char* firstStr;
	firstStr = malloc(MAXSIZEINPUT);
	char* secondStr;
	secondStr = malloc(MAXSIZEINPUT);

	int32_t firstNbrInt, secondNbrInt; // these are our int32_t buffers that will host the parsed input 
	double result = 0;

	printf("Insert first number :");
	scanf_s("%s", firstStr, MAXSIZEINPUT+1);

	printf("Insert operation: ");
	scanf_s(" %c", &operator, 1);

	printf("Insert second number: ");
	scanf_s("%s", secondStr, MAXSIZEINPUT+1);	
	result = calculate(firstStr, operator, secondStr, &firstNbrInt, &secondNbrInt);
	//print result will either print the error if there is or the result if everything went well
	printResult(result);
	return 0;
}

