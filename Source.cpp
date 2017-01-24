//testing
#include <iostream>

#include "Header.h"

using namespace std;

int main()
{
	//int secretCodeLength;
	//int secretCodeRange;

	//cin >> secretCodeLength;
	//cin >> secretCodeRange;

	code guessCode(5, 10);
	code secretCode(5, 10); //Hard-coded for testing

	guessCode.inputCode();
	cout << "Your Guess Is: " << endl;
	guessCode.showCode();
	secretCode.generateCodePreset();
	cout << "The Secret Code Is: " << endl;
	secretCode.showCode();

	cout << "Number of Correct Digits in Correct Places: " << secretCode.checkCorrect(guessCode) << endl;
	cout << "Number of Correct Digits in Incorrect Places: " << secretCode.checkIncorrect(guessCode) << endl;

	system("pause");
};
