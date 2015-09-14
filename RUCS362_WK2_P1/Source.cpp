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
#include <limits>

using namespace std;

struct residence
{
	string phoneNumber;
	float monthlyRent;
	bool rented; 
};

const int ZERO = 0;
const float FLOAT_ZERO = 0;
const int MAX_ENTRIES = 5;
const int IGNORE_AMOUNT = 100;
const int FIRST_DASH = 4; 
const string INPUT_FILE_1_NAME = "RENTALS.txt"; // File name for input file

void ProgramDescription();
bool UserPrompt1();
string convert2UpperCase(string stringInput);

void readAndSortData(bool skipFunction, string inputFileName, residence apartment[], int& counter);
string showAddDeleteExit();
void AddRentals2Array();
string GetPhoneNumber();
float GetMonthlyRent();

void showRentals2Screen(residence apartment[], int& entryCounter);



int main()
{
	int entryCounter; 
	residence apartmentList[MAX_ENTRIES]; 
	string sadeResponse; 


	ProgramDescription();

	readAndSortData(UserPrompt1(), INPUT_FILE_1_NAME, apartmentList, entryCounter);
	sadeResponse = showAddDeleteExit();
	
	if (sadeResponse == "S")
	{
		showRentals2Screen(apartmentList, entryCounter);
	}

	else if (sadeResponse == "A")
	{
		AddRentals2Array();
	}





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

bool UserPrompt1()
{
	string promt1Response; 
	bool errorDetectedR1; // input error detection flag for response 1
	bool skipReadInputFile; 

	do
	{
		cout << endl;
		cout << "Would you like to load existing data from file " << INPUT_FILE_1_NAME << " (Y / N) ?  ";
		cin >> promt1Response;

		promt1Response = convert2UpperCase(promt1Response);

		
		if ((promt1Response != "Y") && (promt1Response != "N"))
		{
			cout << endl;
			cout << "ERROR! Unrecognized input, please try again." << endl;
			errorDetectedR1 = true;
		}
		
		else if (promt1Response == "Y") 
		{
			errorDetectedR1 = false;
			 skipReadInputFile = false;
		}
		

		else if (promt1Response == "N")
		{
			errorDetectedR1 = false;
			skipReadInputFile = true;
		}

	} 

	while (errorDetectedR1 == true);

	return skipReadInputFile; 


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

void readAndSortData(bool skipFunction, string inputFileName, residence apartment[], int& apartmentIndex)
{
	if (skipFunction != true)
	{

	
		bool fileOpenSuccess;
		bool repeatQuestion;

		string error1Response;
		string fileReadErrorResponse;

		ifstream inputFile; // input file stream variable
		inputFile.open(inputFileName.c_str());

		if (!inputFile)
		{
			fileOpenSuccess = false;
			cout << endl;
			cerr << "Error! System could not open file named \"" << inputFileName << "\"" << endl;


			do
			{
				cout << "To exit, press X. To proceed starting with no data, press Y. ";
				cin >> fileReadErrorResponse;
				fileReadErrorResponse = convert2UpperCase(fileReadErrorResponse);

				if ((fileReadErrorResponse != "X") && (fileReadErrorResponse != "Y"))
				{
					cout << endl;
					cout << "ERROR! Unrecognized input, please try again." << endl;
					cout << endl;
					repeatQuestion = true;
				}

				else if (fileReadErrorResponse == "X")
				{
					repeatQuestion = false;
					system("PAUSE");
					exit(5);
				}


				else if (fileReadErrorResponse == "Y")
				{
					repeatQuestion = false;
				}


			}

			while (repeatQuestion == true);
		}

		else
		{
			fileOpenSuccess = true;
			cout << endl;
			cout << "Success opening file named \"" << inputFileName << "\"" << endl;
			cout << endl;
		}





		// while data remains to be read and max entries has not been reached

		for ( apartmentIndex = 0; ((inputFile) && (apartmentIndex < MAX_ENTRIES)); apartmentIndex++)
		{


			inputFile >> apartment[apartmentIndex].phoneNumber;
			inputFile >> apartment[apartmentIndex].monthlyRent;
			inputFile >> apartment[apartmentIndex].rented;
			inputFile.ignore(IGNORE_AMOUNT, '\n');

			//cout << apartment[apartmentIndex].phoneNumber << endl;
			//cout << apartment[apartmentIndex].monthlyRent << endl;
			//cout << apartment[apartmentIndex].rented << endl;

			if (apartmentIndex >= (MAX_ENTRIES - 1))
			{
				cout << "Alert! Maximum number of Entries (" << MAX_ENTRIES << ") has been reached" << endl;
				cout << "No further entries will be read. "<< endl; 
				inputFile.close();
			}


		}


	}

}

void showRentals2Screen(residence apartment[], int& entryCounter)
{
	cout << fixed << showpoint << setprecision(2);
	cout << "Phone Nmmber" << setw(15) << "Monthly Rent "  << setw(15) << "Status" << endl; 
	cout << "------------" << setw(15) << "------------"   << setw(15) << "------------" << endl;
	for (int apartmentIndex = 0; apartmentIndex < entryCounter; apartmentIndex++)
	{		
		cout << apartment[apartmentIndex].phoneNumber << setw(15)
			 << apartment[apartmentIndex].monthlyRent << setw(15);
			 
			 if (apartment[apartmentIndex].rented == 1)
			 {
				 cout << left;
				 cout << "   rented" << endl;
				 cout << right;
			 }

			 else
			 {
				 cout << left; 
				 cout << "   available" << endl;
				 cout << right;

				 //cout << apartment[apartmentIndex].rented << endl;
			 }
	}
}


string showAddDeleteExit()
{
	string response2Question;
	bool repeatQuestion;
	do {

		cout << "Please choose an option by entering its corresponding letter" << endl;
		cout << "S = Show rentals to the Screen " << endl;
		cout << "A = Add rentals to the array " << endl;
		cout << "D = Delete a rental" << endl;
		cout << "X = Exit the program" << endl;
		cout << endl;
		cout << "Please enter response here: ";
		cin >> response2Question;
		cin.ignore(IGNORE_AMOUNT, '\n');

		response2Question = convert2UpperCase(response2Question);


		if ((response2Question != "S") && (response2Question != "A") && (response2Question != "D") && (response2Question != "X"))
		{
			cout << endl;
			cout << "ERROR! Unrecognized input, please try again." << endl;
			cout << endl;
			repeatQuestion = true;
		}

		else
		{
			repeatQuestion = false;
		}
	}

	while (repeatQuestion == true);


	return response2Question;

}
void AddRentals2Array()
{
	string validPhoneNumber; 
	float monthlyRent; 
	bool status;

	cout << "You selected Add Rental to array" << endl; 
	cout << "There are 3 steps to complete this entry, see below for instructions "<< endl; 
	cout << "Step 1. Enter a vaild phone number (10  Digits) "<< endl; 
	cout << "Step 2. Enter the monthly rent. Must greater than 0 and less than " << FLT_MAX << endl;
	cout << "Step 3. Enter the Rental Status as True (1) or False (0)." << endl;  
	cout << endl;
	validPhoneNumber = GetPhoneNumber();
	monthlyRent = GetMonthlyRent();



}
string GetPhoneNumber()
{
	string phoneNumber;
	int length;                         // length of user input

	int errorCounter;

	do
	{
		int i = ZERO;
		errorCounter = ZERO;
		cout << endl;
		cout << "Step 1. Enter the phone number : ";
		getline(cin, phoneNumber);

		length = phoneNumber.length();

		if (length < 12)
		{
			cout << "The phone number you entered is too short" << endl; 
			errorCounter++;
		}

		else if (length > 12)
		{
			cout << "The phone number you entered is too long" << endl;
			errorCounter++;
		}

		else if (length = 12)
		{
			while (phoneNumber[i] != '\0')
			{
				for (int index = ZERO; index < 4; index++)         // Used Loops for error checking 
				{
					if (!(isalpha(phoneNumber[index])))
					{
						errorCounter++;
						cout << "not a number " << endl; 

					}

				}
			}
		} /// end else if


		if ((length = 10) && (errorCounter > 0))
		{
			cout << endl << "Error! You Enterd 12 characters but they were not all numbers. Try again." << endl;
		}
	}

	
	while (errorCounter > 0); // loop if error counter is greater than zero (0) 

	return phoneNumber;

}

float GetMonthlyRent()
{
	int errorCounter;
	float monthlyRent; 

	do
	{
		int i = ZERO;
		errorCounter = ZERO;
		cout << endl;
		cout << "Step 1. Enter the Monthly Rent : ";
		cin >> monthlyRent;


		
		if (cin.fail())
		
		{
			cin.clear();
			cin.ignore(999, '\n');
			errorCounter++;
			cout << "Error! you did not enter a number between 0 and " << FLT_MAX << " Try again." << endl;
		}
		


	}
	while (errorCounter > 0);

	return monthlyRent;

}