#include <vector>
#include "d_random.h"

using namespace std;

//Brief Description of code class?
//Testing

class code
{
public:
	code(int n = 0, int m = 0);
	void showCode();
	int checkCorrect(const code &guess);
	int checkIncorrect(const code &guess);
	void generateCode();
	void generateCodePreset();
	void inputCode();

private:
	int codeLength, range;
	vector<int> codeNumbers;
};

//Constructor to initialize variables
code::code(int n, int m)
{
	vector<int> codeNumbersIni(n);

	codeLength = n;
	range = m;
	codeNumbers = codeNumbersIni;
};

//Used for checking the code
void code::showCode()
{
	cout << "[";
	for (int i = 0; i < codeNumbers.size(); i++)
	{
		cout << codeNumbers.at(i);
		if (i != codeNumbers.size() - 1)
			cout << ", ";
		else
			cout << "]";
	}
	cout << endl;
};

//Random number generator for creating code
void code::generateCode()
{
	randomNumber rndInt;

	for (int i = 0; i < codeNumbers.size(); i++)
	{
		codeNumbers.at(i) = rndInt.random(range);
	}
};

//Random number generator replacement
void code::generateCodePreset()
{
	int codePreset[5] = { 1,2,3,4,5 };
	//int codePreset[5] = { 3,2,3,3,3 };

	vector<int> codeNumbersIni(codePreset, codePreset + 5);

	codeNumbers = codeNumbersIni;

};

//Input Code NEEDS TO NOT TAKE DECIMALS (CRASHING)
void code::inputCode()
{
	int inputDigit;

	cout << "Please Enter Your Guess:" << endl;
	for (int i = 0; i < codeNumbers.size(); i++)
	{
		cout << "[" << i + 1 << "] ";
		cin >> inputDigit;

		if (inputDigit < range && inputDigit >= 0) //Checks to see if entered value is in range
			codeNumbers.at(i) = inputDigit;
		else
		{
			cout << "Guess is out of range. Please Re-enter Your Guess." << endl;
			i--;
		}
	}
};

//Checks Number of Correct Digits in Correct Location
int code::checkCorrect(const code &guess)
{
	int numberCorrect = 0;

	for (int i = 0; i < codeNumbers.size(); i++)
	{
		if (codeNumbers.at(i) == guess.codeNumbers.at(i))
			numberCorrect++;
	}

	return numberCorrect;
};

//Checks Number of Correct Digits in Incorrect Location WIP
int code::checkIncorrect(const code &guess)
{
	int numberIncorrect = 0;
	vector<int> guessCodeEdited;
	vector<int> secretCodeEdited;

	guessCodeEdited = guess.codeNumbers;
	secretCodeEdited = codeNumbers;

	for (int i = 0; i < codeNumbers.size(); i++)	//Blacklists matched locations
	{
		if (codeNumbers.at(i) == guess.codeNumbers.at(i))
		{
			guessCodeEdited.at(i) = range;			//Use "range" as a blacklisted number since it will never appear in either codes
			secretCodeEdited.at(i) = range;
		}
	}

	for (int i = 0; i < guess.codeNumbers.size(); i++)
	{
		if (guessCodeEdited.at(i) != range)
		{
			for (int j = 0; j < codeNumbers.size(); j++)
			{
				if (secretCodeEdited.at(j) != range)
				{
					if (codeNumbers.at(i) == guess.codeNumbers.at(j))
					{
						numberIncorrect++;
						guessCodeEdited.at(i) = range;
						secretCodeEdited.at(j) = range;
						break;
					}
				}
			}
		}
	}

	return numberIncorrect;
};
