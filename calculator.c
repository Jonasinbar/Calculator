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
 *  This fuction takes a long long number and checks
 *  if it is bigger than INT_MAX, that is, it checks
 *  if result can be contained in an int without overflowing
 *  it returns its input as an int if result can be contained in
 *  an int witout overflowing, else it returns -1 that will never be taken
 *  into account because flag NO_ERROR will be assigned to 1.
 *  @param long result, the numer to be checked.
 *  @return the input as an ,int or -1 and raise flag NO_ERROR.
 */
int checkOverflowAndReturnResult(long long result) {
	if (result > INT_MAX) {
		ERROR_CODE = intOverflow;
		return -1;//doesnt matter
	}
	return (int)result;
}

/**
 *  This fuction takes two int as input, calculate their sum as a
 *  long long and call the fucntion checkOverflowAndReturnResult
 *  that will return the input as int if the result does not int overflow,
 *  or it will return -1 and raise flag NO_ERROR so that
 *  the result will not be taked into account.
 *  @param int firstInt, int secondInt, the numbers to be added.
 *  @return the sum of the numbers as int, or -1 and raise flag NO_ERROR.
 */
int add(int firstInt, int secondInt) {
	//pointer to fucntion declaration
	int (*ptrCheckOverflowAndReturnResult)(long long) = &checkOverflowAndReturnResult;
	long long result = (long long)firstInt + (long long)secondInt;
	return (*ptrCheckOverflowAndReturnResult)(result);
}

/**
 *  This fuction takes two int as input, calculate their substraction
 *  and return the result, note that in our case, substract
 *  cannot int overflow because it takes as input two positive ints < INT_MAX
 *  @param int firstInt, int secondInt, the numbers to be substracted.
 *  @return firstInt - secondInt, the substraction as int.
 */
int substract(int firstInt, int secondInt) {
	return firstInt - secondInt;
}

/**
 *  This fuction takes two int as input, calculate their multiplication as a
 *  long and call the fucntion checkOverflowAndReturnResult
 *  that will return the input as int if the result does not int overflow,
 *  or it will return -1 and raise flag NO_ERROR so that
 *  the result will not be taked into account
 *  note that INT_MAX*INT_MAX < LLONG_MAX, then result cannot llong overflow.
 *  @param int firstInt, int secondInt, the numbers to be multiply.
 *  @return the multiplication of the number as int, or -1 and raise flag NO_ERROR.
 */
int multiply(int firstInt, int secondInt) {
	//pointer to fucntion declaration
	int (*ptrCheckOverflowAndReturnResult)(long long) = &checkOverflowAndReturnResult;
	long long result = (long long)firstInt * (long long)secondInt;
	return (*ptrCheckOverflowAndReturnResult)(result);
}

/**
 *  This fuction takes two int as input, calculate their division as a
 *  double. Note that in our case, divide cannot double overflow because it takes
 *  as input two ints < INT_MAX and whole numers.
 *  if case of division by 0, we will return -1 and raise flag NO_ERROR so that
 *  the result will not be taked into account.
 *  @param int firstInt, int secondInt, the numbers to be divided.
 *  @return the division of the number as double, or -1 and raise flag NO_ERROR.
 */
double divide(int firstInt, int secondInt) {
	if (secondInt == 0) {
		ERROR_CODE = divisionByZero;
		return -1;//doesnt matter
	}
	return (double)firstInt / (double)secondInt;
}

/**
 *  This fuction takes two int as input, calculate their modulo
 *  and return the result, note that in our case, modulo
 *  cannot int overflow because it takes as input two positive ints < INT_MAX
 *  @param int firstInt, int secondInt, the numbers to be substracted.
 *  @return firstInt % secondInt, the modulo as int.
 */
int modulo(int firstInt, int secondInt) {
	return firstInt % secondInt;
}

/**
 *  This fuction takes two int as input, calculate and return
 *  the first int to the power of the second, as an int.
 *  To do so, we call our fucntion multiply() 'secondInt' times.
 *  Our fuction multiply() is safe from overflow, that is,
 *  if the result cannot be contained in an int it will raise the flag NO_ERROR
 *  then we will stop our loop and wont take the result into consideration
 *  thus, power() will return the result as int iff the result does not int overflow,
 *  or it will return -1 and raise flag NO_ERROR through the function multiply() so that
 *  the result will not be taked into account afterwords
 *  @param int firstInt, the base and int secondInt the exponent.
 *  @return the powering of the number as int, or -1 and flag NO_ERROR will be raised.
 */
int power(int firstInt, int secondInt) {
	//pointer to fucntion declaration
	int (*ptrMultiply)(int, int) = &multiply;
	//basic case, power of 0 
	if (secondInt == 0) {
		return 1;
	}
	//basic case, power of 1
	if (secondInt == 1) {
		return firstInt;
	}
	int result = firstInt;
	//here we do firstInt*firstInt*...*firstInt, 'secondInt' times
	for (int i = 0; i < secondInt - 1; ++i)
	{
		result = (*ptrMultiply)(result, firstInt); //our multiply is safe from int overflow
		//if flag errorCode was raised by multiply, we better stop now
		if (ERROR_CODE) {
			return -1; //doesnt matter
		}
	}
	return result;
}
/**
 *  This fuction takes two int as input, calculate the secondInt'th root of firstInt as a
 *  double. To do se, is uses the fuction pow() from math.h
 *  as both numbers are positive ints < INT_MAX, the result can't overflow here
 *  @param int firstInt, the base, int secondInt the nth root.
 *  @return the secondInt'th root of firstInt as a double
 */
double nthRoot(int firstInt, int secondInt) {
	//pointer to fucntion declaration
	double (*ptrPow)(double, double) = &pow;
	//as both numbers are positive ints, the result can't overflow here
	// not that the nth root of x is equal to x to the power of 1/n
	return ((*ptrPow)((double)firstInt, 1.0 / (double)secondInt));
}


/**
 *  This fuction takes two int as input, calculate their euclideanDivision as a
 *  int. Note that in our case, euclideanDivision cannot int overflow because it takes
 *  as input two ints < INT_MAX and whole numers.
 *  if case of euclideanDivision by 0, we will return -1 and raise flag NO_ERROR so that
 *  the result will not be taked into account.
 *  @param int firstInt, int secondInt, the numbers to be divided.
 *  @return the division of the number as double, or -1 and raise flag NO_ERROR.
 */
int euclideanDivision(int first, int second) {
	if (second == 0) {
		ERROR_CODE = divisionByZero;
		return -1;//doesnt matter
	}
	return first / second;
}
/**
 *  This fuction takes two int as input and the operator,
 *  it chooses the right fucntion to use according to the operator and return
 *  the result of the corresponding operation
 *  if the operator doesnt belong to {+, -, *, /, %, r, ^, :}
 *  we will return -1 and raise flag NO_ERROR so that
 *  the result will not be taked into account.
 *  @param int firstInt, int secondInt, the numbers to be operated, and char operator, the operator.
 *  @return the division of the number as double, or -1 and raise flag NO_ERROR
 *  through called operation fucntion or in case of operator not recongnized.
 */
double executeOperation(int first, char operator, int second) {
	//pointer to fucntion declaration
	int (*ptrAdd)(int, int) = &add;
	int (*ptrSubstract)(int, int) = &substract;
	int (*ptrMultiply)(int, int) = &multiply;
	double (*ptrDivide)(int, int) = &divide;
	int (*ptrModulo)(int, int) = &modulo;
	double (*ptrNthRoot)(int, int) = &nthRoot;
	int (*ptrPower)(int, int) = &power;
	double (*ptrEuclideanDivision)(int, int) = &euclideanDivision;

	switch (operator) {
	case '+':
		return (*ptrAdd)(first, second);
		break;
	case '-':
		return (*ptrSubstract)(first, second);
		break;
	case '*':
		return (*ptrMultiply)(first, second);
		break;
	case '/':
		return (*ptrDivide)(first, second);
		break;
	case '%':
		return (*ptrModulo)(first, second);
		break;
	case 'r':
		return (*ptrNthRoot)(first, second);
		break;
	case '^':
		return (*ptrPower)(first, second);
		break;
	case ':':
		return (*ptrEuclideanDivision)(first, second);
		break;

	default:
		// if operator is not in the set {+, -, *, /, %, r, ^, :}
		ERROR_CODE = invalidOperator;
		return -1;//doesnt matter
	}

}

/**
 *  This fuction takes a string as input,
 *  and return is as a long long int.
 *  it also checks if it is really a number represented in a string,
 *  if not it raises flag ERROR_CODE and returns -1 that will not be taken into account
 *  @param char* stringNbr, the string to be parsed into a long long int.
 *  @return the parsed string as a long long int or -1 and raise flage ERROR_CODE.
 */
long long stringConvertToLong(char* stringNbr) {
	long long number = 0;

	for (char* digit = stringNbr; *digit; ++digit)
	{
		if( *digit >= '0' && *digit <= '9' ){
		number = number * 10 + *digit - '0';
		}
		
		else{
			//stringNbr is not really a number
			ERROR_CODE = invalidInput;
			return -1;//doesnt matter
		}
	}
	return number;
}
/**
 *  This fuction takes a two long long ints as input,
 *  and checks if they can be contained in an int if so, it returns 1.
 *  if one of the inputs int-overflows, it returns 0
 *  @param firstLongNbr and secondLongNbr, the number that we check the dont int-overflow.
 *  @return 1 if the numbers are not int-overflowing, 0 else
 */
int verifyNumbersAreInt(long long firstLongNbr, long long secondLongNbr) {
	return !(firstLongNbr > INT_MAX || secondLongNbr > INT_MAX);
}


/**
 *  This fuction takes as input : the two input as string : firstStr and secondStr
 *  plus two int buffer : firstNbrInt and secondNbrInt that are passed by reference that
 *  will contain the int parsed value of the the input strng respectively, in case the two string
 *  are really string representation of numbers, not longer than MAXSIZEINPUT, not negative,
 *  whole numbers and not int-Overflowing
 *  If the two input strings respect all the rules that we just described, it put their value as
 *  int the buffers firstNbrInt and secondNbrInt and return 1 else 0.
 *  if one of the inputs int-overflows, it returns 0
 *  @param "firstStr" and "secondStr" the string to check if their parsed values can be contained 
 *  in an int and if they are valid, we put the int representation of firstStr in the input int buffer "firstNbrInt",
 *  the same for secondStr that we put in "secondNbrInt"
 *  @return 1 if firstStr and secondStr can be parsed into an int, 0 else
 */
int inputIsValid(char* firstStr, char* secondStr, int* firstNbrInt, int* secondNbrInt) {
	//pointer to fucntion declaration
	int (*ptrVerifyNumbersAreInt)(long long, long long) = &verifyNumbersAreInt;
	long long (*ptrStringConvertToLong)(char*) = &stringConvertToLong;

	
	if (strnlen(firstStr, MAXSIZEINPUT + 1) > MAXSIZEINPUT
		|| strnlen(secondStr, MAXSIZEINPUT + 1) > MAXSIZEINPUT) {
		ERROR_CODE = invalidInput;
		return 0;
	}
	//we dont support negative numbers
	if (*firstStr == '-' || *secondStr == '-') {
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
	//here we parse our strings into long long and check if they int-overflow
	long long firstLongNbr = (*ptrStringConvertToLong)(firstStr);
	long long secondLongNbr = (*ptrStringConvertToLong)(secondStr);
	if (!(*ptrVerifyNumbersAreInt)(firstLongNbr, secondLongNbr)) {
		ERROR_CODE = intOverflow;
		return 0;
	}
	
	//if everything went well, we fill up our two int buffers that were passed by reference and return 1
	*firstNbrInt = (int)firstLongNbr;
	*secondNbrInt = (int)secondLongNbr;
	return 1;
}

/**
 *  This is our main function : This fuction takes as input : the operator, the two input as string : firstStr and secondStr
 *  plus two int buffer : firstNbrInt and secondNbrInt that are passed by reference that
 *  will contain the int parsed value of the the input strng respectively, and that will, if the two strings are "valid" 
 *  call the funtion executeOperation with the two int that were passed by reference and that will
 *  give us the result of the operation of raise the flaf ERROR_CODE if something went wrong
 *  (for example int overflow) if the input is not valid, it raises flag ERROR_CODE and returns -1 that will
 *  not be taken into account, if the input is valid, it returns the result of the operation as a double.
 *  @param "firstStr" and "secondStr" the string that contains the input from the user, the char "operator" got from the user,
 *  "firstNbrInt" and "firstNbrInt", the int buffer that will contain the parsed value the strings as int
 *  @return if the input is not valid, it raises flag ERROR_CODE and returns -1 that will
 *  not be taken into account, if the input is valid, it returns the result of the operation as a double.
 */
double calculate(char* firstStr, char operator, char* secondStr,
		int* firstNbrInt, int* secondNbrInt) {
	//pointer to fucntion declaration
	int (*ptrInputIsValid)(char*, char*, int*, int*) = &inputIsValid;
	double (*ptrExecuteOperation)(int*, char, int*) = &executeOperation;


	if ((*ptrInputIsValid)(firstStr, secondStr, firstNbrInt, secondNbrInt)) {
		return (*ptrExecuteOperation)(*firstNbrInt, operator, *secondNbrInt);
	}
	else {
		ERROR_CODE = invalidInput;
		return -1;//doesnt matter

	}
	
}
/**
 *  This fuction is supposed to print the details of an error in case there is one according to ERROR_CODE, a global int variable.
 *  @param no parameters, it looks at ERROR_CODE, a global int variable.
 *  @return void, just prints informations to the user
 */
void printError() {
	switch (ERROR_CODE)
	{
	case divisionByZero:
		printf("Failed: can't divide by 0 \n");
		break;
	case intOverflow:
		printf("Failed: int Overflow\n");
		break;
	case invalidInput:
		printf("Failed: invalid input \nOnly positive int are accepted\n");
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
 *  In case there is no error the function just allows us to get rid of the .0000 in case of result being int:
 * for example, in case of 1+2 the result is a doble and will print "3.000", this function prints 3 "instead"
 *  @param no parameters, it looks at ERROR_CODE, a global int variable.
 *  @return void, just prints informations to the user
 */
void printResult(double result) {
	//pointer to fucntion declaration
	void (*ptrPrintError)() = &printError;
	if (ERROR_CODE) {
		(*ptrPrintError)();
	}
	else if ((int)result == result) {//we geck if restult is a whole number
		int resultInt = (int)result;
		printf("%d\n", resultInt);//to get rid of the .0000 in case of result being int
	}
	else {
		printf("%f\n", result);
	}
}
/**
 *  This is the main() function we call in case we dont want to run tests and want to execute 
 *  the prgram with our own inputs. It asks for the two nubers and the operator, 
 
 */
int mainForDemo() {
	//pointer to fucntion declaration
	double (*ptrCalculate) (char*, char, char*, int*, int*) = &calculate;
	void (*ptrPrintResult) (double) = &printResult;

	char* operator = malloc((MAXSIZEINPUT + 1) * sizeof(char));
	char* firstStr = malloc((MAXSIZEINPUT + 1) * sizeof(char));
	char* secondStr = malloc((MAXSIZEINPUT + 1) * sizeof(char));
	int firstNbrInt, secondNbrInt; // these are our int buffers that will host the parsed input 
	double result = 0;

	printf("Insert first number :");
	scanf_s("%s", firstStr, MAXSIZEINPUT);

	printf("Insert operation: ");
	scanf_s("%s", operator, MAXSIZEINPUT);

	printf("Insert second number: ");
	scanf_s("%s", secondStr, MAXSIZEINPUT);
	//if the operator length is not 1 char, we better stop, raise ERROR_CODE flag 
	if (strnlen(operator, MAXSIZEINPUT) != 1) {
		ERROR_CODE = invalidOperator;
	}
	else{
		//here begins the calculation
		result = (*ptrCalculate)(firstStr, operator[0], secondStr, &firstNbrInt, &secondNbrInt);
	}
	//either print the result or print the error
	(*ptrPrintResult)(result);

	
	return 0;
}

