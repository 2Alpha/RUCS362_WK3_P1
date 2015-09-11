//***************************************************************************
//  FILENAME:	 AllenAssn3.cpp
//  DESCRIPTION: Program that will implement the following. 
// 				 1. xxxxx
//				 2. xxxxx
//
//  DATE:        9/10/15
//  CLASS/TERM:  CS362_X40_Data Structures - CU_CS362 - XIN_X40_15F8W1
//  DESIGNER:	 Andrae Allen
//  FUNCTIONS:	 main - reads values, performs calculations, & displays results
//***************************************************************************

#include <iostream> 
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct apartment
{
	string phoneNumber;
	float monthlyRent;
	bool rented; 
};

const int ZERO = 0;
const int MAX_ENTRIES = 500;

const string INPUT_FILE_1_NAME = "RENTALS.txt"; // File name for input file

void ProgramDescription();
void UserPrompt1();
string convert2UpperCase(string stringInput);

int main()
{
	ProgramDescription();
	UserPrompt1();


	system("PAUSE");
	return ZERO;
}

//*************************************************************************
//  FUNCTION:	  ProgramDescription
//  DESCRIPTION:  Displays a brief discription of the program
//  INPUT:        Parameters:  None
//  OUTPUT: 	  Return value: None
//*************************************************************************
void ProgramDescription()
{
	cout << "Program to implement the following:" << endl;
	cout << "1. Read input file named RENTALS.txt, at users request" << endl;


}

void UserPrompt1()
{
	string promt1Response; 
	bool errorDetectedR1; // input error detection flag for response 1

	do
	{
		cout << endl;
		cout << "Would you like to load existing data from file " << INPUT_FILE_1_NAME << " (Y / N) ?  ";
		cin >> promt1Response;

		promt1Response = convert2UpperCase(promt1Response);

		if ((promt1Response == "Y") || (promt1Response == "N"))
		{
			errorDetectedR1 = false;
		}

		else
		{
			errorDetectedR1 = true;
		}

		if (errorDetectedR1 == true)
		{
			cout << endl; 
			cout << "Your input was not accepted, please try again" << endl; 
		}

	} 

	while (errorDetectedR1 == true);

}


string convert2UpperCase(string stringInput)
{
	int i = 0;
	char c;

	string upperCasedString;

	while (stringInput[i] != '\0')
	{
		// if character is a letter 
		if (isalpha(stringInput[i]))
		{
			c = stringInput[i];
			stringInput[i] = toupper(c);
			i++;
		}

		else
		{
			i++;
		}

	}

	upperCasedString = stringInput;

	return upperCasedString;

}

void readAndSortData(string inputFileName, int recordCount, )
{
	apartment complex[MAX_ENTRIES];
	bool fileOpenSuccess;

	ifstream inputFile; // input file stream variable

	if (!inputFile)
	{
		fileOpenSuccess = false;
		cout << endl;
		cerr << "Error Opening File named \"" << inputFileName << "\"" << endl;
		system("PAUSE");
		exit(5);
	}

	else
	{
		fileOpenSuccess = true;
		cout << endl;
		cout << "Success opening file named \"" << inputFileName << "\"" << endl;
		cout << endl;
	}


	// while data remains to be read and max entries has not been reached
	while ((inputFile) && (recordCount < MAX_ENTRIES))
	{
		inputFile >> complex[0].phoneNumber;						// temp student Id 
		inputFile >> tempStudentClassLevel;				// temp Student Class Level
		inputFile >> tempCredits;						// temp credits
		inputFile.ignore(IGNORE_AMOUNT, '\n');


}