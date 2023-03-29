#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

void showMenu();
void getChoice(int& choice, int limit);

void createAcc();
void loginU();
void loginP(int lineNum);

int main()
{
	int userInput;

	showMenu();
	cout << "\nPlease Select an Option From the Menu: ";
	getChoice(userInput, 3);//fix so that entering a word doesnt break it.

	switch (userInput)
	{
	case 1:
		cout << "Create Account.\n";
		createAcc();
		break;
	case 2:
		cout << "Log In.\n";
		loginU();//combine loginU and loginP into login(?)
		break;
	case 3:
		cout << "Exit.\n";
		cout << "\nGoodbye!\n\n";
		exit(3);
	}
	return 0;
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

void getChoice(int& choice, int limit)
{
	cin >> choice;
	while ((choice<1) || (limit<choice)) {
		cout << "Invalid Choice, Please Select a Valid Option: ";
		cin.ignore();
		cin >> choice;
	}
	cout << "\nYour Choice was " << choice << ": ";
}

void createAcc()
{
	ofstream accountsFile;
	string userInput;

	accountsFile.open("accounts.txt", ios::app);
	if (accountsFile.fail())
	{
		cout << "Output file failed to open.";
		exit(1);
	}
	
	cout << "Input username (15 characters): ";
	cin.ignore();
	getline(cin, userInput);
	accountsFile << userInput << endl;

	cout << "Input password (15 characters): ";
	getline(cin, userInput);
	accountsFile << userInput << endl;

	accountsFile.close();

	cout << "Successfully created account." << endl;
}

void loginU()
{
	ifstream accountsFile;

	accountsFile.open("accounts.txt");
	if (accountsFile.fail())
	{
		cout << "Input file failed to open.";
		exit(1);
	}

	string tempUsername;
	int lineNumber = 0;
	string userInput;

	cout << "Input username: ";
	cin.ignore();
	getline(cin, userInput);

	while (getline(accountsFile, tempUsername))
	{	
		lineNumber++;
		if(lineNumber%2==1)
		if (tempUsername == userInput)
		{
			loginP(lineNumber);
			accountsFile.close();
			exit(2);
		}

	}
	cout << "User does not exist, try again\n";
	loginU();
}

void loginP(int lineNumber)
{
	ifstream accountsFile("accounts.txt");
	string tempPass;
	string userInput;
	int choice;

	for (int i = 1; i <= lineNumber+1; i++)
	{
		getline(accountsFile, tempPass);
	}

	cout << "Input password: ";
	getline(cin, userInput);
	if (userInput == tempPass)
	{
		cout << "Successfully logged in!";
		exit(2); //Replace with main menu function call.
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
			cout << "Try again.\n";
			loginP(lineNumber);
			break;
		case 2:
			cout << "Back.\n";
			showMenu();
			break;
		case 3:
			cout << "Exit.\n";
			exit(3);
		}
	}
}