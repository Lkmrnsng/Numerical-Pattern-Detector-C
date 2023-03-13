/***************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and
applying the concepts learned. I have constructed the functions and their respective algorithms
and corresponding code by myself. The program was run, tested, and debugged by my own
efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the
work of other students and/or persons.
 Luke Marion S. Aniago, DLSU ID# 12206849
***************************************************************************/

/*
 Description: This program will deal with number sequences, giving the user two options; it can either:
 				(1) Find the fifth number to 4 user inputted integers, and state the pattern detected
 				(2) Output a sequence based on the size, pattern, and starting number that the user inputs
 Programmed by: Luke Marion S. Aniago, S14A
 Last modified: December  5, 2022
 Version: 3 (Basic Features using Array + Ugly Numbers + Narcissistic Numbers)
 [Acknowledgements]:
	CCICOMP Professor Mr. Gian Lim on the concept of "Doubling" (a formula for converting binary numbers to decimal) taught in class
 	W3 Schools (n.d.). C Arrays. Retrieved from https://www.w3schools.com/c/c_arrays.php
	Tutorials Point (n.d.). Passing Arrays as Function Arguments in C. Retrieved from https://www.tutorialspoint.com/cprogramming/c_passing_arrays_to_functions.htm
	Tutorials Point (n.d.). Ugly Numbers. Retrieved from https://www.tutorialspoint.com/Ugly-Numbers#:~:text=Ugly%20numbers%20are%20those%20number,factor%20the%207%20will%20come.
  Weisstein, E. (1996). Narcissistic Numbers. Retrieved from https://archive.lib.msu.edu/crcmath/math/math/n/n023.htm
*/


#include <stdio.h>

//FUNCTION PROTOTYPES
void DisplayMenu();
void Choice1GetInputs();
void MainPatternDetector(int nUserNum[4]);
int PrimeSeriesDetector(int nUserNum[4]);
int SinglePrimeNumberChecker(int nNum);
int GetNextPrimeNum(int nPrevNumber);
int BinarySeriesDetector(int nUserNum[4]);
int ArrayBinaryChecker(int nNum[4]);
int SingleBinaryChecker(int nNum);
int Power(int nBase,int nExp);
int BinaryToDecimal(int BinaryNum);
void WriteDecimalAsBinary(int DecimalNum);

void Choice2Menu();
void WriteIncreDecre(int IncreOrDecre);
void WriteEvenOdd(int EvenOrOdd);
void WritePrimeSeries();

int UglySeriesDetector (int nNum[4]);
int isUgly(int nNum);
int GetNextUgly(int nPrevNumber);
void WriteUglyNumbers();
int NarcissisticSeriesDetector (int nNum[4]);
int isNarcissistic(int nNum);
int GetNextNarcissistic(int nPrevNumber);
void WriteNarcissisticNumbers ();

/* This function presents the main menu with options that link to other functions. It asks the user the option of their choice and calls the
respective functions when the input is valid. It also loops the main menu until the user chooses option 3 (exit).
Precondition: User input will only be an integer value
No Parameters and Returned Values
*/
void DisplayMenu () 
{
	int nChoice;

	printf("\n________________________________________________________________________________________________________");
	printf("\n\t\t\t\tWelcome to the Number Sequence Program!\t\t\t\t\t");

	//Presents the main menu once, and presents it again when the options are finished processing (in a loop until the user chooses option 3)
	do {
		printf("\n________________________________________________________________________________________________________");
		printf("\n\n---------------------------------Here are the list of things I can do----------------------------------- \n\n");
		printf("\t[1] Give me 4 integers, then I will detect a number pattern and provide the 5th integer.\n");
		printf("\t[2] Choose a number pattern, size, and starting integer, and I will write a number sequence.\n");
		printf("\t[3] Exit the program.\n");
		printf("\n________________________________________________________________________________________________________");
		printf("\n\t\t\t\t  What Option do you want to use?: ");
		scanf("%d", &nChoice); //Takes user's choice

		switch (nChoice) {
			case 1:
				Choice1GetInputs();
				break; //links to Choice1GetInputs() when user enters 1
			case 2:
				Choice2Menu();
				break; //links to Choice2Menu() when user enters 2
			case 3:
				printf("\n\n*************************** Thank you for using the Number Sequence Program! ***************************\n\n"); //Displays the ending message of the program
				break;
			default:
				printf("\n\tThat's not a valid input! Please type the number of your choice. \n\n");//Makes sure user chooses only within the options provided
		}

	} while (nChoice != 3); //Ends the loop when nChoice is 3
}



/* This function gets 4 integers from the user. It will not return to main menu until 1st input contains the sentinel value (-999); it stops getting inputs
once this happens. If all inputs are obtained, it calls the MainPatternDetector() function with the nUserInput[] array as the parameter.
Precondition: The user will only input integers
No Parameters and Returned Values
*/
void Choice1GetInputs() 
{
	int nUserInput[4]; //Declares an array with a size of 4 elements

	//Take 4 Integers from User, Revert back to main menu if first integer is -999 (Sentinel Value)

	do{
	printf("\n\n\n***************************************** You picked option 1! *****************************************\n");
	printf("\n\tPlease Input 4 Integers! \n");
	printf("\tInput first integer:\t");
	scanf("%d", &nUserInput[0]); //assigns the user's first input in the array with index 0

	if (nUserInput[0]!= -999) { // Sentinel Value Checking
		printf("\tInput second integer:\t");
		scanf("%d", &nUserInput[1]); //assigns the user's second input in the array with index 1
		printf("\tInput third integer:\t");
		scanf("%d", &nUserInput[2]); //assigns the user's third input in the array with index 2
		printf("\tInput fourth integer:\t");
		scanf("%d", &nUserInput[3]); //assigns the user's fourth input in the array with index 3

		MainPatternDetector (nUserInput); //calls the pattern checking function, passing the array containing user input values
	}

	else
		printf("\n\tSentinel Value detected in First Input, reverting back to Main Menu...\n\n");
	}while (nUserInput[0]!= -999);
}



/*This function checks if there are existing patterns within the set of numbers given by the user, and prints the fifth number (with the reasoning) if it detects
a number pattern in the sequence. It has the necessary computations for patterns Incre/Decre, Odd/Even, MN Series, and *N Series; but calls other functions to assist
with detecting Prime Series, Binary Series, and Ugly Number Series Patterns.
Precondition: the array parameter nUserNum [] only contains values for the integer data type
@param nUserNum[4] is an array containing the 4 user inputted integers, to be checked for patterns.
No Returned Values
*/
void MainPatternDetector (int nUserNum[4]) 
{
	int isIncrement, isDecrement, isAddAdd, isAddMinus, isMinusAdd, isMinusMinus, isMultipliedByN, isPrime, isBinary, isConstantZero;
	int isUgly, isNarcissistic;
	int nGap, nFifthNum;
	int nNum1Num2Diff, nNum2Num3Diff, nNum3Num4Diff, nNum1Num2Quotient, hasNoRemainderBetween;
	int isFirstTwoLastTwoSameGap, isFirstTwoNextTwoSameGap;

	//Initializing truth Values to zero (false) instead of garbage Value
	isAddAdd = 0;
	isAddMinus = 0;
	isMinusAdd = 0;
	isMinusMinus = 0;
	isMultipliedByN = 0; 
	isConstantZero = 0;
	isPrime = 0; 
	isBinary = 0;

	//PATTERN CHECKING: Stores 1 (or True) in variable if the condition for the pattern is true

	//Differences of the Inputted Numbers (to be used for Increment/Decrement and MN Series pattern checking + results)
	nNum1Num2Diff = nUserNum[1]-nUserNum[0];
	nNum2Num3Diff = nUserNum[2]-nUserNum[1];
	nNum3Num4Diff = nUserNum[3]-nUserNum[2];

	isFirstTwoLastTwoSameGap= nNum1Num2Diff == nNum3Num4Diff; // Checks if the first 2 inputs and the last 2 inputs have the same gap
	isFirstTwoNextTwoSameGap= nNum1Num2Diff == nNum2Num3Diff; // Checks if the first 2 inputs and the next set of 2 inputs (integer 2 & 3) have the same gap

	//INCREMENT/DECREMENT SERIES: Checks if the difference between numbers positive or negative, and if the differences between all numbers are equal.
	isIncrement = nNum1Num2Diff > 0 && isFirstTwoLastTwoSameGap && isFirstTwoNextTwoSameGap;
	isDecrement = nNum1Num2Diff < 0 && isFirstTwoLastTwoSameGap && isFirstTwoNextTwoSameGap;
	
	//ODD/EVEN SERIES: is integrated within Increment/Decrement Series (checked while printing for IncreDecre results, as Odd/Even pattern can only occur under that case)

	//MN SERIES: Checks if the sequence is incremented and/or decremented by two different integers

	if (nNum1Num2Diff != nNum2Num3Diff)
	{
		isAddAdd = isFirstTwoLastTwoSameGap && nNum1Num2Diff >= 0 && nNum2Num3Diff >= 0;
		isAddMinus = isFirstTwoLastTwoSameGap && nNum1Num2Diff >= 0 && nNum2Num3Diff < 0;
		isMinusAdd = isFirstTwoLastTwoSameGap && nNum1Num2Diff < 0 && nNum2Num3Diff >= 0;
		isMinusMinus = isFirstTwoLastTwoSameGap && nNum1Num2Diff < 0 && nNum2Num3Diff < 0;
	}

	//*N SERIES: Checks if the sequence numbers are being multiplied by a common factor.
	if (nUserNum[0]==0 && nUserNum[1]==0 && nUserNum[2]==0 && nUserNum[3]==0) //in the case that all inputs are zero
		isConstantZero = 1;

	if (nUserNum[0] != 0 && nUserNum[1] != 0 && nUserNum[2] != 0) { //Makes sure the program will not divide with zero
		nNum1Num2Quotient = nUserNum[1]/nUserNum[0];//To be used also in result printing
		hasNoRemainderBetween = nUserNum[1]%nUserNum[0] == 0 && nUserNum[3]%nUserNum[2] == 0 && nUserNum[2]%nUserNum[1]== 0; //Makes sure no remainders are present in-between calculations
		//Checks if the quotient is positive, if the quotient is constant, and if there are no remainders in between calculations.
		isMultipliedByN = nNum1Num2Quotient == nUserNum[3]/nUserNum[2] && nNum1Num2Quotient == nUserNum[2]/nUserNum[1] && hasNoRemainderBetween;
	}

	//Checks if the numbers are in a sequential prime number series

	isPrime = PrimeSeriesDetector(nUserNum); //Calls the PrimeSeriesDetector() and assigns its return value to isPrime

	//Checks if the numbers can be interpreted as a sequential binary number sequence

  if (ArrayBinaryChecker(nUserNum) == 1) //Makes sure all elements in the array are Binary Numbers
		isBinary = BinarySeriesDetector (nUserNum); //Calls the BinarySeriesDetector() and assigns its return value to isBinary

	//BONUS SERIES:
	isUgly = UglySeriesDetector(nUserNum);
	isNarcissistic = NarcissisticSeriesDetector (nUserNum);

	//PRINTING OF RESULTS (WITH 5TH NUMBER)
	printf("\n\n::::::::::::::::::::::::::::::::::::::::::::::: Results ::::::::::::::::::::::::::::::::::::::::::::::::\n\n ");

	if (isIncrement || isDecrement) { //Groups together the Increment and Decrement series, common nGap formula
		nGap = nUserNum[1]-nUserNum[0]; //Difference to nNum1Num2Diff: nGap will always be positive

		if (nGap < 0)
			nGap *= -1; //Makes sure nGap is a positive value

		//Program will print result based on which pattern is true
		if (isIncrement) {
			nFifthNum = nUserNum[3] + nGap;

			printf("\tFifth number: %d\n", nFifthNum);
			printf("\tPattern: Increments of %d ", nGap);
		}

		else {
			nFifthNum = nUserNum[3] - nGap;

			printf("\tFifth number: %d\n", nFifthNum);
			printf("\tPattern: Decrements of %d ", nGap);
		}
		//Program will check whether the Increment/Decrement Series is also an odd/even series. Since odd/even can only occur below he incre/decre pattern
		if (nGap == 2 && nUserNum [0] % 2 == 0) //Checks if the gap is only by 2s, and if the first digit inputted is an even number
			printf("while also being an Even Series\n");

		else if (nGap == 2 && (nUserNum [0] % 2 == 1 || nUserNum [0] % 2 == -1 )) //else, if the gap is by 2s, and if the first digit is odd.
			printf("while also being an Odd Series\n");
		//Note: the "nUserNum [0] % 2 == -1" condition is used to cater for negative odd numbers
		//the even number checker only accepts zero as the modulo result whether the input is negative or positive.
	}

 	else if (isConstantZero)//Having constant zeroes, means the sequence was multiplied by zero repetitively
		printf("\tFifth Number: %d \n\tPattern: Multiplied by %d\n", nUserNum[0], nUserNum[0]); 

  else if(isAddAdd || isAddMinus || isMinusAdd || isMinusMinus) { //Groups together the MN series, common 5th number formula
	  nFifthNum = nUserNum[3] + nNum2Num3Diff;
		printf("\n\tFifth number: %d\n", nFifthNum);

		if (isAddAdd)
			printf("\tPattern: +%d +%d Sequence\n", nNum1Num2Diff, nNum2Num3Diff);
		else if (isAddMinus)
			printf("\tPattern: +%d %d Sequence\n", nNum1Num2Diff, nNum2Num3Diff);
		else if (isMinusAdd)
			printf("\tPattern: %d +%d Sequence\n", nNum1Num2Diff, nNum2Num3Diff);
		else if (isMinusMinus)
			printf("\tPattern: %d %d Sequence\n", nNum1Num2Diff, nNum2Num3Diff);

	}
  
  //Note: All conditions above are mutually exclusive, that's why they are in an "if else" chain, to lessen computation process.
	//However, *N, Primary, and Binary Series can exist alongside some patterns above, requiring a nested if statement instead to ensure checking.

	if (isMultipliedByN) {
		nFifthNum = nUserNum[3] * nNum1Num2Quotient;

		printf("\n\tFifth number: %d\n", nFifthNum);
		printf("\tPattern: Multiplied by %d\n", nNum1Num2Quotient);
	}

	if (isPrime) {
		nFifthNum = GetNextPrimeNum(nUserNum[3]); //Assigns the next prime number after the 4th input as the 5th integer
		printf("\n\n\tFifth number: %d\n", nFifthNum);
		printf("\tPattern: Prime Series");
	}

	if (isBinary) {
		nFifthNum = BinaryToDecimal(nUserNum[3]) + 1;
		printf("\n\tFifth number as binary: ");
		WriteDecimalAsBinary(nFifthNum);
		printf("\tPattern: Binary Series");
	}

	if (isUgly) {
		nFifthNum = GetNextUgly(nUserNum[3]); //Assigns the next ugly number after the 4th input as the 5th integer
		printf("\n\n\tFifth number: %d\n", nFifthNum);
		printf("\tPattern: Ugly Number Series");
	}

  if (isNarcissistic){
    nFifthNum = GetNextNarcissistic(nUserNum[3]); //Assigns the next Narcissistic number after the 4th input as the 5th integer
		printf("\n\n\tFifth number: %d\n", nFifthNum);
		printf("\tPattern: Narcissistic Number Series");
  }

	//The no relation condition will only be satisfied once all other patterns above are false
	if (isIncrement == 0 && isDecrement== 0 && isAddAdd== 0 && isAddMinus== 0 && isMinusAdd== 0 && isMinusMinus== 0 && isMultipliedByN==0 && isPrime== 0 && isBinary == 0 && isConstantZero== 0)
		if(isUgly == 0 && isNarcissistic==0)
			printf("\tNo relation!");

	printf("\n\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n ");
}


/* This function determines whether an inputted array contains sequentially incrementing prime numbers. 
Precondition: The inputted array contains 4 integers
@param nUserNum[4] is an array containing the 4 integers, whose elements will be checked by the PrimeSeriesDetector ()
@return nRes represents the result of the function, returns 1 if inputted array contains sequentially incrementing prime numbers, else return 0
*/
int PrimeSeriesDetector(int nUserNum[4])
{
    int nRes=0; //Initial Value is False
	if (SinglePrimeNumberChecker(nUserNum[0]) == 1) //Checks if the first input is a prime number
		if (GetNextPrimeNum(nUserNum[0]) == nUserNum[1]) //Checks if the next occuring prime number after the first input is equal to the second input
			if (GetNextPrimeNum(nUserNum[1]) == nUserNum[2]) //Checks if the next occuring prime number after the second input is equal to the third input
				if (GetNextPrimeNum(nUserNum[2]) == nUserNum[3]) //Checks if the next occuring prime number after the third input is equal to the fourth input
                    nRes=1;
	return nRes;
}

/* This function determines whether an inputted integer is prime
Precondition: the value passed to the parameter is an integer value
@param nNum is an integer, which will checked whether it is prime or not
@return nRes represents the result of the function, returns 1 if the integer inputted is prime, else return 0
*/
int SinglePrimeNumberChecker (int nNum) 
{
	int h, nFactors = 0;// h is a temp variable for the loop, nFactors represent the number of Factors of the number
	int nResult = 0; //Initializes value to false

	for (h = 1; h <= nNum; h++) { //Counts all the factors, Prime numbers are always positive so negative nNum will not be processed
		if (nNum % h == 0)
			nFactors+=1;
	}

	//Once Factor Counting is finished, program will check how many factors there are.


	if (nFactors == 2) //If number is prime, the factors should total to 2
		nResult = 1; //Represents that the result is true


	return nResult;
}

/* This function gets the next prime number after the inputted integer value
Precondition: the value passed to the parameter is an integer value, this function is only called by the PrimeSeriesDetector() once the first user input is a prime number
@param nPrevNumber is an integer, which will be the basis where the GetNextPrimeNum() starts looking for the next prime number
@return nNextPrimeNumber represents the next occuring prime number after the parameter nPrevNumber
*/
int GetNextPrimeNum(int nPrevNumber) 
{
	int i = 1; //i is a temp variable for the loop
	int nCurrentNumber = nPrevNumber + 1; //Starts checking with the next integer after the previous number
	int nNextPrimeNumber;

	while(i == 1) { //To check every integer until it sees the next prime number

		if (SinglePrimeNumberChecker(nCurrentNumber)==1) { //if the current number is a prime number
			nNextPrimeNumber = nCurrentNumber; //sets the current number as the next prime number to be returned
			i = 0; //ends the loop once the loop finds the next prime number
		} else
			nCurrentNumber +=1; //Increments the current number if it is not a prime number
		
	}
	return nNextPrimeNumber;
}


/* This function detects whether the inputted array contains sequentially incrementing binary numbers
Precondition: The inputted array contains 4 integers, all of which can also be interpreted as binary numbers
@param nUserNum[4] is an array containing the 4 binary integers, whose elements will be checked by the BinarySeriesDetector ()
@return nRes represents the result of the function, returns 1 if inputted array contains sequentially incrementing binary numbers, else return 0
*/
int BinarySeriesDetector(int nUserNum[4]){
    int nRes = 0; //Initial Value is False

	if (BinaryToDecimal(nUserNum[0]) + 1 == BinaryToDecimal(nUserNum[1])) //Checks if the first input occurs just before the second input
		if (BinaryToDecimal(nUserNum[1]) + 1 == BinaryToDecimal(nUserNum[2])) //Checks if the second input occurs just before the third input
			if (BinaryToDecimal(nUserNum[2]) + 1 == BinaryToDecimal(nUserNum[3])) //Checks if the third input occurs just before the fourth input
				nRes = 1; //Sets isBinary to true when all conditions are met

    return nRes;
}

/* This function determines whether an inputted array contains elements which can all be interpreted as binary numbers (Ones and Zeros only)
Precondition: The inputted array contains 4 integers
@param nNum[4] is an array containing integers, which will checked whether all elements can be interpreted as binary numbers
@return nFinalRes represents the result of the function, returns 1 if all elements in the array inputted can be interpreted as binary numbers, else return 0
*/
int ArrayBinaryChecker(int nNum[4]) 
{
	int h, nRes, totalTrutValues=0, nFinalRes;

	for(h = 0; h <= 3; h++) { //Repeats the checking for every element in the array
		nRes = SingleBinaryChecker (nNum[h]); //Calls the function to check if the current element in the array is binary, assigns 1 if yes and 0 if otherwise

		if (nRes == 1) //Increments the totalTruthValues once the element passes the binary number checking
			totalTrutValues++;
	}

	if (totalTrutValues == 4) //Checks if all 4 elements in the array was able to increment the totalTruthValues (which means they all passed the checking)
		nFinalRes =1;
	else
		nFinalRes = 0;

	return nFinalRes;
}

/* This function determines whether an inputted integer can  be interpreted as a binary number (Ones and Zeros only)
Precondition: The value passed to the function is an integer (can be zero or negative)
@param nNum is an integer, which will checked if it can be interpreted as a binary number
@return nRes represents the result of the function, returns 1 if the integer inputted can be interpreted as a binary number, else return 0
*/
int SingleBinaryChecker(int nNum) 
{
	int nNextDigit, nRes=1;

	while (nNum !=0) { //Loops until the nNum is reduced to zero
		nNextDigit = nNum % 10; //Extracts the rightmost digit in the integer and assigns it to nNextDigit
		nNum /= 10; //Cuts off the rightmost digit from the integer once it is extracted

		if (nNextDigit != 0 && nNextDigit != 1) //If any of the digits are NOT equal to 1 and 0, it sets the nRes to zero (to be returned by the end of the function)
			nRes = 0;
	}//Note: Negative numbers will not pass here, because a negative nNum % 10 will not result to positive 1

	return nRes; 
}

/* This function multiplies the given nBase to itself, nExp number of times. It acts as a power function but only for positive integers
Precondition: The values passed to the function are positive integers, the Machine Project will only use this function with a base 10.
@param nBase is an integer, to be multiplied by itself, this Machine Project will only use 10 as the nBase value
@return nResult is an accumulator that represents the result of the repetitive multiplication process
*/
int Power(int nBase, int nExp) 
{
	int nResult = 1; //Since the operator will be multiplication (cannot be zero)
	int  i;

	for(i = 1; i <= nExp; i++) //Multiplies the base by itself repetitively based on the exponent nExp
		nResult *= nBase;

	return nResult;
}

/* This function converts a given BinaryNumber into its respective decimal value
Precondition: The values passed to this function are only integers that may be interpreted as binary numbers (ones and zeros only)
@param BinaryNum is an integer, interpreted as a binary number, will be converted into its respective decimal value
@return nAccumulator is an accumulator that represents the decimal value of the binary number (computed through "Doubling Method")
*/
int BinaryToDecimal(int BinaryNum) 
{
	int nDigitCounter=0, nNextDigit, nAccumulator = 0;
	int BinaryNumCopy = BinaryNum; //Assigns the value of the Binary Num to a copy (for digit counting)


	while(BinaryNumCopy!=0) { //Counts the digits in the binary number
		BinaryNumCopy /=10;
		nDigitCounter++;
	}

	for (; nDigitCounter > 0; nDigitCounter--) {
		//Extracts one digit starting from the left, going to the right, depending on the loop counter
		nNextDigit= BinaryNum; //Resets the nNextDigit value to the original binary number
		nNextDigit %= Power(10, nDigitCounter); //Cuts off the unnecessary digits on the left
		nNextDigit /= Power(10, nDigitCounter-1); //Cuts off the unnecessary digits on the right

		//Uses the "Doubling" formula for converting Binary Numbers to Decimal, courtesy of CCICOMP Professor Mr. Gian Lim
		nAccumulator = nAccumulator * 2 + nNextDigit;
	}

	return nAccumulator;
}

/* This function prints a given decimal number into its binary number form using an array. It usually takes the value of the 5th number in the binary sequence
Precondition: The values passed to this function are positive integers (its only called once there is at least 4 sequentially incrementing binary numbers detected)
which means this function will not be called with a parameter of zero and below.
@param DecimalNum is a positve integer to be written as its binary number form, usually represents the 5th binary number to be outputted by the machine.
No Return Values
*/
void WriteDecimalAsBinary(int DecimalNum) 
{
	int nBinDigit[32], index=0; //Declared an array that can fit 32 digits, enough size to accomodate the limits of an integer data type.
	int nArrayPrinter;

	while (DecimalNum > 0) { //Must only loop until 1, because using zero as the limit will make the loop infinite since 0/2 is still zero
		nBinDigit[index] = DecimalNum % 2; //Gets the remainder from dividing by 2
		DecimalNum /=2; //Updates the value of the Decimal number after the division
		index++;
		//Note: Without an array, we can print the BinDigits in reverse by multiplying them by 10, 100, 1000 respectively (uses Power funtion and an accumulator)
	}

	//Array Printing:
	nArrayPrinter = index-1; //Assigns index value to the Array Printer (minus one since array index starts from zero)

	for (; nArrayPrinter >= 0; nArrayPrinter--) //Prints the array starting from the highest index to the zero index (prints in reverse)
		printf("%d", nBinDigit[nArrayPrinter]);

}

/* This function determines whether an inputted array contains sequentially incrementing ugly numbers. 
Precondition: The inputted array contains 4 integers
@param nNum[4] is an array containing the 4 integers, whose elements will be checked by the UglySeriesDetector ()
@return nRes represents the result of the function, returns 1 if inputted array contains sequentially incrementing ugly numbers, else return 0
*/
int UglySeriesDetector (int nNum[4])
{
	int nRes = 0;
	if (isUgly(nNum[0])==1) //Checks if the first input is an Ugly Number
		if (GetNextUgly(nNum[0])==nNum[1]) //Checks if the next occuring ugly number after the previus input is equal to the next input
			if (GetNextUgly(nNum[1])==nNum[2]) 
				if (GetNextUgly(nNum[2])==nNum[3]) 
						nRes = 1;
	return nRes;
}

/* This function determines whether an inputted integer is an ugly number
Precondition: the value passed to the parameter is an integer value
@param nNum is an integer, which will checked whether it is an ugly number or not
@return nRes represents the result of the function, returns 1 if the integer inputted is an ugly number, else return 0
*/
int isUgly(int nNum){
  int h;// h is a temp variable for the loop
  int nRes= 1; //Initializes nRes to true
	
	if (nNum <= 0)
		nRes=0;
	else
		for (h = 1; h <= nNum; h++) { //Checks all factors
			if (nNum % h == 0)
				if (SinglePrimeNumberChecker(h)==1) //Checks sequentially if it is a factor, a prime number, and if it is not equal to 2, 3, and 5 (which means its not an ugly number)
      	  if (h!=2 && h!=3 && h!=5)
       	   nRes = 0; //Sets nRes to zero once it finds prime factors that are not 2, 3, and 5.

	}
	return nRes;
}

/* This function gets the next ugly number after the inputted integer value
Precondition: the value passed to the parameter is an integer value, only called with an ugly number parameter in this machine project
@param nPrevNumber is an integer, which will be the basis where the GetNextUgly() starts looking for the next ugly number
@return nNextUglyNum represents the next occuring ugly number after the parameter nPrevNumber
*/
int GetNextUgly(int nPrevNumber)
{
	int i = 1; //i is a variable for the while loop
	int nCurrentNumber = nPrevNumber + 1; //Starts checking with the next integer after the previous number
	int nNextUglyNum;


	while(i == 1) { //To check every integer until it sees the next ugly number

		if (isUgly (nCurrentNumber) == 1) { //Checks if the current number is an ugly number
			nNextUglyNum = nCurrentNumber; //sets the current number as the next ugly number to be returned
			i = 0; //ends the loop once the loop finds the next ugly number
		} else
			nCurrentNumber +=1; //Increments the current number if it is not an ugly number
	}
	return nNextUglyNum;
}
/* This function determines whether an inputted array contains sequentially incrementing Narcissistic numbers. 
Precondition: The inputted array contains 4 integers
@param nNum[4] is an array containing the 4 integers, whose elements will be checked by the NarcissisticSeriesDetector ()
@return nRes represents the result of the function, returns 1 if inputted array contains sequentially incrementing Narcissistic numbers, else return 0
*/
int NarcissisticSeriesDetector (int nNum[4])
{
	int nRes = 0;
	if (isNarcissistic(nNum[0])==1) //Checks if the first input is a Narcissistic Number
		if (GetNextNarcissistic(nNum[0])==nNum[1]) //Checks if the next occuring Narcissistic number after the previus input is equal to the next input
			if (GetNextNarcissistic(nNum[1])==nNum[2]) 
				if (GetNextNarcissistic(nNum[2])==nNum[3]) 
						nRes = 1;
	return nRes;
}
/* This function determines whether an inputted integer is a Narcissistic number
Precondition: the value passed to the parameter is an integer value
@param nNum is an integer, which will checked whether it is a Narcissistic number or not
@return nRes represents the result of the function, returns 1 if the integer inputted is a Narcissistic number, else return 0
*/
int isNarcissistic(int nNum){
  int nRes= 0; //Initializes nRes to false
  int DigitCount = 0, NumCopy = nNum, nSum=0;
	
	if (nNum <= 0)
		nRes=0;
	else
	{
	while(NumCopy!=0) //Counts the digits in the number
  {
    NumCopy /=10;
    DigitCount++;
  }

  NumCopy = nNum;

  while (NumCopy!=0)
  {
    nSum += Power (NumCopy%10, DigitCount);
    NumCopy/=10;
  }

  if (nNum == nSum)
    nRes = 1;
	}

	return nRes;
}
/* This function gets the next Narcissistic number after the inputted integer value
Precondition: the value passed to the parameter is an integer value, only called with a Narcissistic number parameter in this machine project
@param nPrevNumber is an integer, which will be the basis where the GetNextNarcissistic() starts looking for the next Narcissistic number
@return nNextNarcissistic represents the next occuring Narcissistic number after the parameter nPrevNumber
*/
int GetNextNarcissistic(int nPrevNumber)
{
	int i = 1; //i is a variable for the while loop
	int nCurrentNumber = nPrevNumber + 1; //Starts checking with the next integer after the previous number
	int nNextNarcissistic;


	while(i == 1) { //To check every integer until it sees the next Narcissistic number

		if (isNarcissistic (nCurrentNumber) == 1) { //Checks if the current number is a Narcissistic number
			nNextNarcissistic = nCurrentNumber; //sets the current number as the next Narcissistic number to be returned
			i = 0; //ends the loop once the loop finds the next Narcissistic number
		} else
			nCurrentNumber +=1; //Increments the current number if it is not a Narcissistic number
	}
	return nNextNarcissistic;
}
/* This function displays the submenu for the second option, and calls the necessary functions based on the user's choice. This menu is looped until the user
chooses the option for returning to the main menu
Precondition: The user inputs only integer values in this function
No Parameters and Returned Values
*/
void Choice2Menu () 
{
	int nPatternChoice;

	do {
		printf("\n\n\n***************************************** You picked option 2! *****************************************\n");
		printf("Choose a Number Pattern to use in the sequence: \n");
		printf("[1] Increments of N \n");
		printf("[2] Decrements of N \n");
		printf("[3] Incrementing Even Series \n");
		printf("[4] Incrementing Odd Series \n");
		printf("[5] Incrementing Prime Series \n");
		printf("[6] Incrementing Ugly Number Series \n");
    printf("[7] Incrementing Narcissistic Number Series \n");
		printf("[8] [Go back to Main Menu] \n\n");

		printf("Input Number Pattern Option to use:  ");
		scanf("%d", &nPatternChoice);

		switch (nPatternChoice) {
			case 1:
			case 2:
				WriteIncreDecre(nPatternChoice); //Calls the WriteIncreDecre() function using the nPatternChoice as a parameter
				break; //executes when choice is 1 or 2
			case 3:
			case 4:
				WriteEvenOdd(nPatternChoice); //Calls the WriteEvenOdd() function using the nPatternChoice as a parameter
				break; //executes when choice is 2 or 3
			case 5:
				WritePrimeSeries(); //Calls the WritePrimeSeries() function
				break;
			case 6:
				WriteUglyNumbers(); //Calls the WriteUglyNumbers() function
				break;
      case 7:
				WriteNarcissisticNumbers(); //Calls the WriteNarcissisticNumbers() function
				break;
			case 8:
				printf("\n\nGoing back to main menu...\n\n");
				break;
			default:
				printf("\n\tThat's not a valid input! Please type the number of your choice. \n\n"); //Makes sure user chooses only within the options provided
		}
	} while (nPatternChoice!=8);
}

/* This function writes an incrementing or decrementing number sequence based on the user's given sequence size, gap, and starting number
Precondition: The values passed to this function are only either 1 or 2, representing Incrementing Series or Decrementing Series, the user will also input 
integer values in this function
@param IncreOrDecre represents the user's pattern choice, to be used when the function decides whether to add or subtract the user's given increment/decrement
No Returned Values
*/
void WriteIncreDecre(int IncreOrDecre) 
{
	int nIncrementDecrement, nSequenceSize, nStartingNumber;
	int looper;

	printf("\nPlease input the increment/decrement 'N' (as positive):\t");
	scanf("%d", &nIncrementDecrement);

	if (nIncrementDecrement > 0) { //Checks if the input is valid before proceeding to next prompt
		printf("Please input the number of values 'X' to be generated:\t");
		scanf("%d", &nSequenceSize);

		if (nSequenceSize >=2) { //Checks if the input is valid before proceeding to next prompt
			printf("Please input the starting number 'Y' in the series:\t");
			scanf("%d", &nStartingNumber);

			printf("\nSequence Generated!:\n");
			for (looper = 1; looper <= nSequenceSize; looper ++) { //Prints the sequence elements 1 by 1 through a loop
				printf("%d ", nStartingNumber); //Uses the starting number as the result printing element
				if(IncreOrDecre == 1)//Checks if user chose Case 1 or Case 2, and does the arithmetic related to the choice
					nStartingNumber += nIncrementDecrement; //If user chose case 1, add the inputted N
				else
					nStartingNumber -= nIncrementDecrement; //Else, decrement the inputted N
			}
		} else
			printf("\nYou've placed an invalid sequence size. Only numbers greater than 1 will be processed.");
	}

	else
		printf("\nYou've placed an invalid increment/decrement. Please input a positive integer to represent your increments/decrements.");
}

/* This function writes an Incrementing Even or Odd number sequence based on the user's given sequence size and starting number
Precondition: The values passed to this function are only either 3 or 4, representing Even Series or Odd Series, the user will also input 
integer values in this function
@param EvenOrOdd represents the user's pattern choice, to be used when the function checks the validity of the inputted starting number 
No Returned Values
*/
void WriteEvenOdd(int EvenOrOdd) 
{
	int nSequenceSize, nStartingNumber;
	int looper;

	printf("\nPlease input the number of values 'X' to be generated:\t");
	scanf("%d", &nSequenceSize);

	if (nSequenceSize >=2) { //Check if sequence size is valid, else do not execute 
		printf("Please input the starting number 'Y' in the series:\t");
		scanf("%d", &nStartingNumber);

		//Checks if the starting number is even when pattern choice is even, or if the starting number is odd when the pattern choice is odd
		if ((EvenOrOdd == 3 && nStartingNumber%2 ==0) || (EvenOrOdd == 4 && nStartingNumber%2 ==1)) { 
			printf("\nSequence Generated!:\n");

			for (looper = 1; looper <= nSequenceSize; looper ++) { //Prints the starting number, adds 2, and prints it again until the sequence size is fulfilled
				printf("%d ", nStartingNumber);
				nStartingNumber += 2;
			}
		} else
			printf("\nYou've placed an invalid starting number.");
	} else
		printf("\nYou've placed an invalid sequence size. Only numbers greater than 1 will be processed.");
}

/* This function writes an Incrementing Prime number sequence based on the user's given sequence size and starting number
Preconditions: Values to be inputted by the user in this function must be integer values
No Parameters and Returned Values
*/
void WritePrimeSeries() 
{
	int nSequenceSize, nStartingNumber;
	int looper;

	printf("\nPlease input the number of values 'X' to be generated:\t");
	scanf("%d", &nSequenceSize);

	if (nSequenceSize >=2) { //Checks if the sequence size is valid, else do not continue with asking the starting number
		printf("Please input the starting number 'Y' in the series:\t");
		scanf("%d", &nStartingNumber);

		if (SinglePrimeNumberChecker(nStartingNumber) == 1) { //Checks if the starting number is a prime number, else do not continue
			printf("\nSequence Generated!:\n");
			
			//Prints the starting number, then updates its value by calling the GetNextPrimeNum (), repeating this until the sequence size is fulfilled.
			for (looper = 1; looper <= nSequenceSize; looper ++) { 
				printf("%d ", nStartingNumber);
				nStartingNumber = GetNextPrimeNum(nStartingNumber);
			}
		} else
			printf("\nYou've placed an invalid starting number (not a prime number).");
	} else
		printf("\nYou've placed an invalid sequence size. Only numbers greater than 1 will be processed.");
}

/* This function writes an Incrementing Ugly number sequence based on the user's given sequence size and starting number
Preconditions: Values to be inputted by the user in this function must be integer values
No Parameters and Returned Values
*/
void WriteUglyNumbers()
{
	int nSequenceSize, nStartingNumber;
	int looper;

	printf("\nPlease input the number of values 'X' to be generated:\t");
	scanf("%d", &nSequenceSize);

	if (nSequenceSize >=2) { //Checks if the sequence size is valid, else do not continue with asking the starting number
		printf("Please input the starting number 'Y' in the series:\t");
		scanf("%d", &nStartingNumber);

		if (isUgly(nStartingNumber) == 1) { //Checks if the starting number is an ugly number, else do not continue
			printf("\nSequence Generated!:\n");
			
			//Prints the starting number, then updates its value by calling the GetNextUgly (), repeating this until the sequence size is fulfilled.
			for (looper = 1; looper <= nSequenceSize; looper ++) { 
				printf("%d ", nStartingNumber);
				nStartingNumber = GetNextUgly(nStartingNumber);
			}
		} else
			printf("\nYou've placed an invalid starting number (not an ugly number).");
	} else
		printf("\nYou've placed an invalid sequence size. Only numbers greater than 1 will be processed.");
}

/* This function writes an Incrementing Narcissistic number sequence based on the user's given sequence size and starting number
Preconditions: Values to be inputted by the user in this function must be integer values
No Parameters and Returned Values
*/
void WriteNarcissisticNumbers (){
	int nSequenceSize, nStartingNumber;
	int looper;

	printf("\nPlease input the number of values 'X' to be generated:\t");
	scanf("%d", &nSequenceSize);

	if (nSequenceSize >=2) { //Checks if the sequence size is valid, else do not continue with asking the starting number
		printf("Please input the starting number 'Y' in the series:\t");
		scanf("%d", &nStartingNumber);

		if (isNarcissistic(nStartingNumber) == 1) { //Checks if the starting number is a Narcissistic number, else do not continue
			printf("\nSequence Generated!:\n");
			
			//Prints the starting number, then updates its value by calling the GetNextNarcissistic (), repeating this until the sequence size is fulfilled.
			for (looper = 1; looper <= nSequenceSize; looper ++) { 
				printf("%d ", nStartingNumber);
				nStartingNumber = GetNextNarcissistic(nStartingNumber);
			}
		} else
			printf("\nYou've placed an invalid starting number (not a Narcissistic number).");
	} else
		printf("\nYou've placed an invalid sequence size. Only numbers greater than 1 will be processed.");
}


/* The main function calls the DisplayMenu() function to start the program
No Preconditions
No Parameters and Returned Values
*/
int main() 
{
	DisplayMenu(); //Calls the function that displays the main menu

	return 0;
}

