#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

void showMenu();
void getChoice(int& choice);

void createAcc();
void loginU();
void loginP(int lineNum);

int main()
{
	int userInput;

	showMenu();
	getChoice(userInput);

	switch (userInput)
	{
	case 1:
		cout << "Create Account.\n";
		createAcc();
		break;
	case 2:
		cout << "Log In.\n";
		loginU();
		break;
	case 3:
		cout << "Exit.\n";
		cout << "\nGoodbye!\n\n";
		exit(1);
	}
}

void showMenu()
{
	

	cout << "****************************************\n"
		<< "Welcome, User." << endl
		<< "[1] Create Account." << endl
		<< "[2] Log In." << endl
		<< "[3] Exit." << endl
		<< "****************************************";
}

void getChoice(int& choice)
{
	cout << "\nPlease Select an Option From the Menu: ";
	cin >> choice;
	while (!((1 <= choice) && (choice <= 3))) {
		cout << "Invalid Choice, Please Select a Valid Option: ";
		cin >> choice; }
	cout << "\nYour Choice was " << choice << ": ";
}

void createAcc()
{
	char userInput[16];

	ofstream usernamesFile;
	ofstream passwordsFile;

	usernamesFile.open("usernames.txt", ios::app);
	if (usernamesFile.fail())
	{
		cout << "Output file failed to open.";
		exit(1);
	}

	cout << "Input username (15 characters): ";
	cin >> userInput;

	usernamesFile << userInput << endl;

	passwordsFile.open("passwords.txt", ios::app);
	if (passwordsFile.fail())
	{
		cout << "Output file failed to open.";
		exit(1);
	}

	cout << "Input password (15 characters): ";
	cin >> userInput;

	passwordsFile << userInput << endl;

	usernamesFile.close();
	passwordsFile.close();

	cout << "Successfully created account." << endl;
	//Call to main menu function
}

void loginU()
{
	ifstream usernamesFile("usernames.txt");
	if (usernamesFile.fail())
	{
		cout << "Input file failed to open.";
		exit(1);
	}

	string tempUser;
	int lineNumber = 1;
	char userInput[16];

	cout << "Input username: ";
	cin >> userInput;

	while (getline(usernamesFile, tempUser))
	{
		lineNumber++;

		if (tempUser == userInput)
		{
			loginP(lineNumber);
			exit(1);
		}
	}

	cout << "User does not exist, try again\n";
	loginU();

	usernamesFile.close();
}

void loginP(int lineNumber)
{
	ifstream passwordsFile;
	string tempPass;
	char passInput[16];
	int choice;

	for (int i = 1; i <= lineNumber; i++)
	{
		getline(passwordsFile, tempPass);
	}

	cout << "Input password: ";
	cin >> passInput;

	if (passInput == tempPass)
	{
		cout << "Successfully logged in!";
		exit(1); //Replace with main menu function call.
	}
	else
	{
		cout << "Incorrect password." << endl <<
			"[1] Try again." << endl <<
			"[2] Back." << endl <<
			"[3] Exit." << endl;

		cin >> choice;

		switch (choice)
		{
		case 1:
			loginP(lineNumber);
			break;

		case 2:
			showMenu();
			break;

		case 3:
			exit(1);

		default:
			cout << "Invalid input.";
			exit(1);
		}
	}
}