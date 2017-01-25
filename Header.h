// EECE 2560 
// Project 1
// Jacky Ko, Patricia Gavelek
//
// Header file for Project 1. Contains the declaration for the "code" class used for the secret code and the guess code in the main program.
// The file also contains the implmentation of the functions in the "code" class.
//

#include <vector>
#include <cctype>
#include <string>
#include "d_random.h"
using namespace std;

class code
{
public:
//  Constructor
	code(int n = 0, int m = 0);

//  Code Generation/Input Operations
	void generateCode();
	void generateCodePreset();
	void inputCode();

//  Hint Generation Operations
	int checkCorrect(const code &guess);
	int checkIncorrect(const code &guess);

//  Code Checking Operations
	void showCode();

private:
	int codeLength, range;		// Size of the code and the upper bound (exclusive) of the allowed integers.
	vector<int> codeNumbers;	// Vector that stores the code
};

// End of code class

code::code(int n, int m)
// Constructor to initialize code length, range, and the size of the code vector.
{
	vector<int> codeNumbersIni(n);

	codeLength = n;
	range = m;
	codeNumbers = codeNumbersIni;
};

void code::showCode()
// Outputs the code in a list [a, b, c, ...]. Used for checking the code.
{
	cout << "[";
	for (int i = 0; i < codeNumbers.size(); i++)	// Goes through each cell in the vector.
	{
		cout << codeNumbers.at(i);				
		if (i != codeNumbers.size() - 1)			// Formatting. Adds ", " unless the for loop is ending. 
			cout << ", ";
		else
			cout << "]";							// Formatting. Closes the output with a "]".
	}
	cout << endl;
};

void code::generateCode()
// Generating the code using the provided random number generator class.
{
	randomNumber rndInt;							

	for (int i = 0; i < codeNumbers.size(); i++)	// Cycles throught the vector to populate each cell with a random integer.
	{
		codeNumbers.at(i) = rndInt.random(range);	// Range of random integer is from [0,range). Range is provided at initialization.
	}
};

void code::generateCodePreset()
// Random number generator replacement. Used for checking provided values.
{
	// Creates array to populate the vector with.
	// Number sets not in use are commented out.

	int codePreset[5] = { 1,2,3,4,5 };			
	//int codePreset[5] = { 3,2,3,3,3 };
	//int codePreset[5] = { 5,0,3,2,6 };
	//int codePreset[5] = { 2,1,2,2,2 };
	//int codePreset[5] = { 5,0,3,2,6 };

	vector<int> codeNumbersIni(codePreset, codePreset + 5);		// Temporary vector used for transfer.

	codeNumbers = codeNumbersIni;
};

void code::inputCode()
// Populates code with user inputs. Used in creating the guess code.
{
	int inputDigit;
	bool isInt;
	string line;

	cout << "Please Enter Your Guess:" << endl;
	for (int i = 0; i < codeNumbers.size(); i++)													// Cycles through each cell in the vector.
	{
		isInt = 1;																					// Assumes the inputted value is an int intially.
		cout << "[" << i + 1 << "] ";
		getline(cin, line);																			// Extracts input as string for invalid character analysis.

		for (int j = 0; j < line.size(); ++j)														// Goes through each character in string to check if it's a digit.
		{
			if (!isdigit(line[j]))														
			{
				isInt = 0;																			// If any character is not a digit, isInt becomes false.
				cin.clear();																		// Input is reset.
				break;
			}
		}

		if ((isInt == 1) && (line.size() != 0))														// If string is an integer and not blank.
		{
			inputDigit = stoi(line);																// String is converted back into an integer.
			
			if (inputDigit < range && inputDigit >= 0)												// Checks to see if entered value is in range.
				codeNumbers.at(i) = inputDigit;
			else
			{
				cout << "Guess is out of range. Please re-enter your guess." << endl;				// If not in range, return an error.
				i--;
			}
		}

		else
		{
			cout << "Guess contains an invalid character. Please re-enter your guess." << endl;		// If not an integer, return an error.
			i--;
		}
	}
};

int code::checkCorrect(const code &guess)
// Checks number of correct digits in correct location.
{
	int numberCorrect = 0;

	for (int i = 0; i < codeNumbers.size(); i++)
	{
		if (codeNumbers.at(i) == guess.codeNumbers.at(i))	// Compares value of internal (secret) code and guess code at the same index.
			numberCorrect++;								// Increases counter if the code valeus match at the same index.s
	}

	return numberCorrect;									// Returns # correct digits in correct location.
};

int code::checkIncorrect(const code &guess)
// Checks number of correct digits in incorrect location.
{
	int numberIncorrect = 0;
	vector<int> guessCodeEdited;							// Stores an edited guess code with blacklist values.
	vector<int> secretCodeEdited;							// Stores an edited secret code with blacklist values.

	guessCodeEdited = guess.codeNumbers;
	secretCodeEdited = codeNumbers;

	for (int i = 0; i < codeNumbers.size(); i++)			// Blacklists correct digit correct location indexes.
	{
		if (codeNumbers.at(i) == guess.codeNumbers.at(i))
		{
			guessCodeEdited.at(i) = range;					// Use value "range" as a blacklisted number since it will never appear in either codes.
			secretCodeEdited.at(i) = range;					// Blacklist secret code at the matched indexes as well to skip checking.
		}
	}

	for (int i = 0; i < guess.codeNumbers.size(); i++)						// Cycles through the guess code.
	{	
		if (guessCodeEdited.at(i) != range)									// Checks to see if the guess code value is blacklisted. If not, proceed.
		{
			for (int j = 0; j < codeNumbers.size(); j++)					// Nested loop to cycle through secret code.
			{
				if (secretCodeEdited.at(j) != range)						// Checks to see if the secret code value is blacklisted. If not, proceed.
				{
					if (codeNumbers.at(i) == guess.codeNumbers.at(j))		// Checks to see if secret code value at index j is the same as the guess code at i.
					{
						numberIncorrect++;									// Adds to the number of correct digits in the incorrect location.
						guessCodeEdited.at(i) = range;						// Updates guess code blacklist with "used" index.
						secretCodeEdited.at(j) = range;						// Updates secret code blacklist with "used" index.
						break;												// Gets out of internal loop since guess code index is now blacklisted.
					}
				}
			}
		}
	}

	return numberIncorrect;													// Returns # correct digits in incorrect location.
};

// End of header file