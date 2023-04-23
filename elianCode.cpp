#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

void showMenu();
void getChoice(int& choice, int limit);
string get_line(ifstream& file, int line_number);
void createAcc();
void loginUsername(string& tempUsername, string& authority);
void loginPassword(string tempPassword);
void incorrectPassword(string tempPassword);
void adminCheck();
void sendMessages(string tempUsername);
int mainMenu(string username, string authority);

int main()
{	
	ofstream accountsFile;
	accountsFile.open("accounts.txt", ios::app);
	if (accountsFile.fail())
	{
		cout << "Output file failed to open.";
		exit(1);
	}

	adminCheck();
	showMenu();
	cout << "\nPlease Select an Option From the Menu: ";
	string username;
	string authority;
	int userInput;
	getChoice(userInput, 3);
	
	switch (userInput)
	{
	case 1:
		cout << "Create Account.\n";
		createAcc();
		break; 
	case 2:
		cout << "Log In.\n";
		loginUsername(username, authority);
		break; 
	case 3:
		cout << "Exit.\n";
		cout << "\nGoodbye!\n\n";
		exit(3);
	}




	accountsFile.close();
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
	while (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "Invalid input. Please enter an integer: ";
		cin >> choice;
	}
	while ((choice < 1) || (limit < choice)) {
		cout << "Invalid Choice, Please Select a Valid Option: ";
		cin.clear();
		cin.ignore();
		cin >> choice;
	}
	cout << "\nYour Choice was " << choice << ": ";
	cin.ignore();
}

string get_line(ifstream& file, int line_number) {
	string line;
	int current_line = 0;
	file.seekg(0, ios::beg);
	while (current_line < line_number && getline(file, line)) {
		current_line++;
	}
	if (current_line == line_number) {
		return line;
	}
	else {
		return "failed to get line";
	}
}

void createAcc()
{
	ofstream accountsFile;
	accountsFile.open("accounts.txt", ios::app);
	if (accountsFile.fail())
	{
		cout << "Output file failed to open.";
		exit(1);
	}
	ifstream usernameCheck;
	usernameCheck.open("accounts.txt");
	if (usernameCheck.fail())
	{
		cout << "Input file failed to open.";
		exit(1);
	}

	string userInput;
	string tempUsername;
	int lineNumber = 0;

	cout << "Input username: ";
	getline(cin, userInput);

	usernameCheck.seekg(0, ios::beg);
	while (getline(usernameCheck, tempUsername))
	{
		lineNumber++;
		if (lineNumber % 3 == 1)
			if (tempUsername == userInput)
			{
				cout << "\nThis username is already taken, please try again.\n";
				accountsFile.close();
				usernameCheck.close();
				createAcc();
				return;
			}
	}
	accountsFile << userInput << endl;

	cout << "Input password: ";
	getline(cin, userInput);
	accountsFile << userInput << endl << "0" << endl;

	accountsFile.close();
	usernameCheck.close();
	cout << "Successfully created account." << endl;
}

void loginUsername(string& tempUsername, string& tempAuthority)
{
	ifstream accountsFile;
	accountsFile.open("accounts.txt");
	if (accountsFile.fail())
	{
		cout << "Input file failed to open.";
		exit(1);
	}

	string tempPassword;
	int lineNumber = 0;
	string userInput;

	cout << "Input username: ";
	getline(cin, userInput);

	accountsFile.seekg(0, ios::beg);
	while (getline(accountsFile, tempUsername))
	{
		lineNumber++;
		if (lineNumber % 3 == 1)
			if (tempUsername == userInput)
			{
				tempPassword = get_line(accountsFile, lineNumber + 1);
				tempAuthority = get_line(accountsFile, lineNumber + 2);
				loginPassword(tempPassword);
				accountsFile.close();
				return;
			}
	}
	cout << "User does not exist, try again.\n";
	accountsFile.close();
	loginUsername(tempUsername, tempAuthority);
}

void loginPassword(string tempPassword)
{
	string userInput;

	cout << "Input password: ";
	getline(cin, userInput);

	if (userInput == tempPassword)
	{
		cout << "Successfully logged in!";
		return; 
	}
	else
		incorrectPassword(tempPassword);
}

void incorrectPassword(string tempPassword)
{
	int choice;
	cout << "Incorrect password." << endl <<
		"[1] Try again." << endl <<
		"[2] Back." << endl <<
		"[3] Exit." << endl;

	getChoice(choice, 3);

	switch (choice)
	{
	case 1:
		cout << "Try again.\n";
		loginPassword(tempPassword);
		break;
	case 2:
		cout << "Back.\n";
		main();
		break;
	case 3:
		cout << "Exit.\n";
		exit(2);
	}
}

void adminCheck()
{
	ifstream usernamesFile;
	usernamesFile.open("accounts.txt");
	if (usernamesFile.fail())
	{
		cout << "Input file failed to open.";
		exit(4);
	}

	ofstream accountsFile;
	accountsFile.open("accounts.txt", ios::app);
	if (accountsFile.fail())
	{
		cout << "Output file failed to open.";
		exit(1);
	}

	string temp;

	while (getline(usernamesFile, temp))
	{
		if (temp == "admin")
			return;
	}
		accountsFile << "admin" << endl << "123456" << endl << "1" << endl;
}

void sendMessages(string tempUsername)
{
	ifstream accountsFile("accounts.txt");
	ofstream messageFile;
	string input, message, username, temp;
	int lineNumber = 0;

	cout << "Input the username of the receiver: ";
	getline(cin, username);

	while (getline(accountsFile, input))
	{
		lineNumber++;

		if (lineNumber % 3 == 1)
		{
			if (input == username)
			{
				temp = username;
				username += ".txt";
				messageFile.open(username, ios::app);

				cout << "Input message: ";
				getline(cin, message);

				messageFile << "From: " << tempUsername << endl;
				messageFile << "To: " << temp << endl << endl;

				messageFile << message << endl;

				messageFile.close();
				exit(2);
			}
		}
	}
	cout << "User does not exist.";
	exit(2);
}

int mainMenu(string username, string authority)
{
	int lineNum = 0;
	string tempNum;
	ifstream authorityCheck("accounts.txt");

	authorityCheck.seekg(0, ios::beg);
	while (getline(authorityCheck, tempNum))
	{
		lineNum++;
		if (lineNum % 3 == 1)
			if (tempNum == username)
			{
				authorityCheck.seekg(0, ios::beg);
				for (int i = 1; i <= lineNum + 2; i++)
				{
					getline(authorityCheck, tempNum);
					if (tempNum == "1")
					{
						cout << "admin";

					}
					if (tempNum == "0")
					{
						cout << "guest";

					}
				}
			}
	}

	return 3;
}
