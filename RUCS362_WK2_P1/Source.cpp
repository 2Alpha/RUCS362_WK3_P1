//***************************************************************************
//  FILENAME:	 AllenAssn3.cpp
//  DESCRIPTION: Program that will implement the following. 
// 				 1. Optionally Read input file named RENTALS.txt
//				 2. If data is available, show all rental records on file 
//				 3. If array space is available, add rental records to the array
//				 4. If data is available, allow user to delete rental records from the array
//				 5. Allow the user save changes or exit without saving any changes
//
//  DATE:        9/10/15
//  CLASS/TERM:  CS362_X40_Data Structures - CU_CS362 - XIN_X40_15F8W1
//  DESIGNER:	 Andrae Allen
//  FUNCTIONS:	 main - reads values, performs calculations, & displays results
//               ProgramDescription - Displays a brief discription of the program
//				 UserPrompt1 - Promt that asks user if they would like to import data from RENTALS.txt
//				 convert2UpperCase - Converts the lower case characters within a string to upper case
//				 readAndSortData - Reads and sorts the data from input file RENTALS.txt
//               showRentals2Screen - Displays all rental records on file via the console  
//				 showAddDeleteExit - Presents the user with the options of show, add, delete, or exit the program  
//				 AddRentals2Array - If space is available, allows user to add rental entries to the array
//				 GetPhoneNumber - Stores the entered phone number specifically in the format ###-###-#### 
//				 GetMonthlyRent - stores the entered amount for monthly rent 
//				 GetRentalStatus - Stores the entered amoount for rental statis (available or rented)
//				 DeleteARental - If array contain data, allows user to delete a specific entry
//				 SearchAndDistroy - Secondary function used by function DeleteARental
//				 SaveAndOrExit - Presents the user with the option to save and or exit the program
//***************************************************************************


#include <iostream> 
#include <fstream>
#include <cstdio> 
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
const int MAX_ENTRIES = 2;			// Max Entries 
const int IGNORE_AMOUNT = 100;		// Ignore Amount 
const int INDEX_4_1ST_DASH = 3;		// Index for First Dash in phone number
const int INDEX_4_2ND_DASH = 7;		// Index for Second Dash in phone number
const float  MAX_RENT = 999999;		// Max rental price - this was not specified 
const string INPUT_FILE_1_NAME = "RENTALS.txt"; // File name for input file
const string OUTPUT_FILE_1_NAME = "RENTALS.txt"; // File name for output file

void ProgramDescription();
bool UserPrompt1();
string convert2UpperCase(string stringInput);

void readAndSortData(bool runFunction, string inputFileName, residence apartment[], int& apartmentIndex);
string showAddDeleteExit();
void AddRentals2Array(string optionSelected, residence apartment[], int& entryCounter);
string GetPhoneNumber();
float GetMonthlyRent();
bool  GetRentalStatus();
void DeleteARental(string optionSelected, residence apartment[], int& entryCounter);
void SearchAndDistroy(string target, residence apartment[], int& entryCounter);
void SaveAndOrExit(string optionSelected, residence apartment[], int& entryCounter);

void showRentals2Screen(string optionSelected, residence apartment[], int& entryCounter);




int main()
{
	int entryCounter = 0;						// entry counter 
	residence apartmentList[MAX_ENTRIES]; 
	string sadeResponse; 
	bool runFunction; 


	ProgramDescription();
	runFunction = UserPrompt1();
 
	readAndSortData(runFunction, INPUT_FILE_1_NAME, apartmentList, entryCounter);

	do
	{

		sadeResponse = showAddDeleteExit();

		showRentals2Screen(sadeResponse, apartmentList, entryCounter);

		AddRentals2Array(sadeResponse, apartmentList, entryCounter);

		DeleteARental(sadeResponse, apartmentList, entryCounter);

		SaveAndOrExit(sadeResponse, apartmentList, entryCounter);

	}

	while (sadeResponse != "X");





	

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

//*************************************************************************
//  FUNCTION:	  UserPrompt1
//  DESCRIPTION:  Promt that asks user if they would like to import data from RENTALS.txt
//  INPUT:        Parameters:  None
//  OUTPUT: 	  Return value: ReadInputFile, boolean variable of whether to read input file.  
//*************************************************************************
bool UserPrompt1()
{
	string promt1Response; // prompt #1 response
	bool errorDetectedR1; // input error detection flag for response 1
	bool ReadInputFile; // Read inout file, boolean variable of whether to read input file

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
			 ReadInputFile = true;
		}
		

		else if (promt1Response == "N")
		{
			errorDetectedR1 = false;
			ReadInputFile = false;
		}

	} 

	// loop if error detected flag equals true 
	while (errorDetectedR1 == true);

	return ReadInputFile; 


}

//*************************************************************************
//  FUNCTION:	  convert2UpperCase
//  DESCRIPTION:  Converts the lower case characters within a string to upper case
//  INPUT:        Parameters:  stringInput - string to covert all letters uppercase 
//  OUTPUT: 	  Return value: A string where all the letters are uppercase 
//*************************************************************************
string convert2UpperCase(string stringInput)
{
	int i = 0;  // variabel used for tracking index location in array
	char c;		// variable used to temporaliy store character from string

	string upperCasedString;		// A string where all the letters are uppercase  

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

//*************************************************************************
//  FUNCTION:	  readAndSortData
//  DESCRIPTION:  Reads and sorts the data from input file RENTALS.txt
//  INPUT:        Parameters:  runFunction -  Boolean variable of whether to run function 
//							   inputFileName - Input file name
//							   apartment - Array containing apartment records 
//							   apartmentIndex - appartment index, used to keep track of number of entries
//
//  OUTPUT: 	  Return value: None
//*************************************************************************
void readAndSortData(bool runFunction, string inputFileName, residence apartment[], int& apartmentIndex)
{
	// if runfunction equals true 
	if (runFunction == true)
	{

		bool fileOpenSuccess;				// file open success flag
		bool repeatQuestion;				// repeat question flag 

		string error1Response;				// error number #1 response 
		string fileReadErrorResponse;		// file read error response

		ifstream inputFile; // input file stream variable
		inputFile.open(inputFileName.c_str());

		
		// if file could not be opened
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

			// while repeat question equals true 
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

		for (apartmentIndex = 0; ((inputFile) && (apartmentIndex < MAX_ENTRIES)); apartmentIndex++)
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
				cout << "No further entries will be read. " << endl;
				inputFile.close();
			}


		}

	}

}

//*************************************************************************
//  FUNCTION:	  showRentals2Screen
//  DESCRIPTION:  Displays all rental records on file via the console
//  INPUT:        Parameters:  optionSelected -  Menu option selected  
//							   apartment - Array containing apartment records
//							   entryCounter - Entry counter 
//
//  OUTPUT: 	  Return value: None
//*************************************************************************
void showRentals2Screen(string optionSelected, residence apartment[], int& entryCounter)
{

	// if entry counter equals 0 and the option selected equals S 
	if ((entryCounter == ZERO) && (optionSelected == "S"))
	{
		cout << "After an extensive search, it appears there a no rentals stored." << endl;
		cout << "Therefore there are no entries to display " << endl;
	}

	// else if entry counter is greater than 0 and the  option selected equals S
	else if ((entryCounter > ZERO) && (optionSelected == "S"))
	{

		cout << fixed << showpoint << setprecision(2);
		cout << "Phone Nmmber" << setw(15) << "Monthly Rent " << setw(15) << "Status" << endl;
		cout << "------------" << setw(15) << "------------" << setw(15) << "------------" << endl;
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

	} // end else if
}

//*************************************************************************
//  FUNCTION:	  showAddDeleteExit
//  DESCRIPTION:  Presents the user with the options of show, add, delete, or exit the program
//  INPUT:        Parameters:  User input from console
//
//  OUTPUT: 	  Return value: string response2Question - response to question
//*************************************************************************
string showAddDeleteExit()
{
	string response2Question;			// Response to question
	bool repeatQuestion;				// Repeat question
	do {

		cout << endl; 
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

	// while repeat question equals true
	while (repeatQuestion == true);


	return response2Question;

}

//*************************************************************************
//  FUNCTION:	  AddRentals2Array
//  DESCRIPTION:  If space is available, allows user to add rental entries to the array
//
//  INPUT:        Parameters:  optionSelected -  Menu option selected  
//							   apartment - Array containing apartment records
//							   entryCounter - Entry counter 
//
//  OUTPUT: 	  Return value: None
//*************************************************************************
void AddRentals2Array (string optionSelected, residence apartment[], int& entryCounter)
{
	
	cout << "entry counter = " << entryCounter << endl;

	// if option selcted equls "A" and entry counter equals max entries 
	if ((optionSelected == "A") && (entryCounter == MAX_ENTRIES))
	{
		cout << "The maximum amount of entries (" << MAX_ENTRIES << ") has been reached." << endl;
		cout << "Therefore you cannot add any more entries" << endl;
	}

	
	// else if option selcted equls "A" and entry counter is less than max entries  
	else if ((optionSelected == "A") && (entryCounter < MAX_ENTRIES))
	{

		cout << "You selected Add Rental to array" << endl;
		cout << "There are 3 steps to complete this entry, see below for instructions " << endl;
		cout << "Step 1. Enter a vaild phone number in the format of \"###-###-####\" " << endl;
		cout << "Step 2. Enter the monthly rent. Must greater than 0 and less than " << MAX_RENT << endl;
		cout << "Step 3. Enter the Rental Status as Y = yes, N = No" << endl;
		cout << endl;
		 
		apartment[entryCounter].phoneNumber = GetPhoneNumber();;
		apartment[entryCounter].monthlyRent = GetMonthlyRent();
		apartment[entryCounter].rented = GetRentalStatus();
		entryCounter++;

		cout << "Entry successfully added!" << endl << endl;
	}


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
			cout << "Please follow the format \"###-###-####\" Try again." << endl;
			errorCounter++;
		}

		else if (length > 12)
		{
			cout << "The phone number you entered is too long" << endl;
			cout << "Please follow the format \"###-###-####\" Try again." << endl;
			errorCounter++;
		}

		else if (length = 12)
		{
			
			for (int index = ZERO; index < 3; index++)         // Used Loops for error checking 
				{				
					if (!(isdigit(phoneNumber[index])))
					{
						
						errorCounter++;
						//cout << "not a number " << endl; 
					}

				}


			for (int index = 3; index < 4; index++)         // Used Loops for error checking 
			{
				if (phoneNumber[index] != '-')
				{
					errorCounter++;
					//cout << "dash not where it should be " << endl;
				}

			}

			for (int index = 4; index < 7; index++)         // Used Loops for error checking 
			{
				if (!(isdigit(phoneNumber[index])))
				{
					errorCounter++;
					//cout << "not a number " << endl;
				}

			}

			for (int index = 7; index < 8; index++)         // Used Loops for error checking 
			{
				if (phoneNumber[index] != '-')
				{
					errorCounter++;
					//cout << "dash not where it should be " << endl;
				}

			}

			for (int index = 8; index < 12; index++)         // Used Loops for error checking 
			{
				if (!(isdigit(phoneNumber[index])))
				{
					errorCounter++;
					//cout << "not a number " << endl;
				}

			}

		} /// end else if

		if ((length == 12) && (errorCounter > 0))
		{
			cout << endl; 
			cout << "Error! You Enterd 12 characters, however not in the correct format." << endl; 
			cout << "Please follow the format \"###-###-####\" Try again." << endl;
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
		cout << "Step 2. Enter the Monthly Rent : ";
		cin >> monthlyRent;


		
		if ((cin.fail()) || (monthlyRent > MAX_RENT))
		
		{
			cin.clear();
			cin.ignore(999, '\n');
			errorCounter++;
			cout << "Error! you did not enter a number between 0 and " << MAX_RENT << " Try again." << endl;
		}
		


	}
	while (errorCounter > 0);

	return monthlyRent;

}

bool  GetRentalStatus()
{
	bool repeatQuestion;
	bool rentalStatusInBool;
	string rentalStatusResponse; 
	
	do 
	{

		cout << endl;
		cout << "Step 3. Is the apartment currently rented? Y = yes, N = No" << endl;
		cin >> rentalStatusResponse;

		rentalStatusResponse = convert2UpperCase(rentalStatusResponse);

		if ((rentalStatusResponse != "Y") && (rentalStatusResponse != "N"))
		{
			cout << endl;
			cout << "ERROR! Unrecognized input, please try again." << endl;
			cout << endl;
			repeatQuestion = true;
		}


		else if (rentalStatusResponse == "Y")
		{
			repeatQuestion = false;
			rentalStatusInBool = true; 
		}



		else if (rentalStatusResponse == "N")
		{
			repeatQuestion = false;
			rentalStatusInBool = false;
		}
	}


	while (repeatQuestion == true);

	return rentalStatusInBool;
}

void  DeleteARental(string optionSelected, residence apartment[], int& entryCounter)
{
	if ((entryCounter == ZERO) && (optionSelected == "D"))
	{
		cout << "After an extensive search, it appears there a no rentals stored." << endl;
		cout << "Therefore there are no entries to delete. "<< endl; 
	}

	else if ((entryCounter > ZERO) && (optionSelected == "D"))
	{
		string PhoneNumber2Delete;

		cout << "List of Phone Numbers for rentals on file:" << endl;

		for (int apartmentIndex = 0; apartmentIndex < entryCounter; apartmentIndex++) // Display Phone Numbers of all rentals stored,
		{
			cout << apartment[apartmentIndex].phoneNumber << endl;
		}

		cout << endl;
		cout << "Enter Phone Number of the rental you wish to delete." << endl;
		cout << "Please follow the format \"###-###-####\"" << endl;

		PhoneNumber2Delete = GetPhoneNumber();

		SearchAndDistroy(PhoneNumber2Delete, apartment, entryCounter);
	}
}

void SearchAndDistroy (string target, residence apartment[], int& entryCounter)
{
	int placeFound = 0;
	bool targetDistroyed; 

	while ((placeFound < entryCounter) && (apartment[placeFound].phoneNumber != target))
		placeFound++;                        // increment index

	//If itemToDel was Found, delete it
	if (placeFound < entryCounter) {

		// Move all values below itemToDel UP one cell
		for (int num = placeFound + 1; num < entryCounter; num++)
		{
			apartment[num - 1].phoneNumber = apartment[num].phoneNumber;
		}


		// Decrement list size
		entryCounter--;

		// Zero out deleted last item
		//apartment[entryCounter] = '/0';	// Optional

		cout << endl << "Success!" <<endl; 
		cout << "Rental entry with phone # \"" << target << "\" has been deleted.";
		cout << endl; 
		targetDistroyed = true;
	}  // end if

	else
	{
		cout << endl << "ERROR!" << endl;
		cout << "Rental entry with phone # \"" << target << "\" cound not be found."<< endl; 
	}
}

void SaveAndOrExit(string optionSelected, residence apartment[], int& entryCounter)
{
	if (optionSelected == "X")
	{



		string saveOrExitResponse;
		bool repeatQuestion;


		do
		{
			cout << endl;
			cout << "Before you go" << endl;
			cout << "Would you like to save any modificatiions that may have occured?" << endl;
			cout << "Y = yes, N = No : ";

			cin >> saveOrExitResponse;

			saveOrExitResponse = convert2UpperCase(saveOrExitResponse);

			if ((saveOrExitResponse != "Y") && (saveOrExitResponse != "N"))
			{
				cout << endl;
				cout << "ERROR! Unrecognized input, please try again." << endl;
				cout << endl;
				repeatQuestion = true;
			}


			else if (saveOrExitResponse == "Y")
			{
				repeatQuestion = false;
				if (remove(OUTPUT_FILE_1_NAME.c_str()) != 0)
					cout << "delete failed" << endl;

				ofstream modifiedRentalFile;							// output file steam name
				modifiedRentalFile.open(OUTPUT_FILE_1_NAME.c_str());     // open file for writing
				char skip = ' ';

				for (int apartmentIndex = ZERO; apartmentIndex < entryCounter; apartmentIndex++)
				{
					modifiedRentalFile << apartment[apartmentIndex].phoneNumber << skip
						<< apartment[apartmentIndex].monthlyRent << skip
						<< apartment[apartmentIndex].rented << endl;
				}

				modifiedRentalFile.close();     // close output file

			}



			else if (saveOrExitResponse == "N")
			{
				repeatQuestion = false;
				cout << "FYI, any changes made will not be saved. " << endl;

			}
		}

		while (repeatQuestion == true);
	}
}



