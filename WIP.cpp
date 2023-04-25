#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

void showMenu();
void getChoice(int& choice, int limit);
string get_line(ifstream& file, int line_number);

void createAcc(string& tempUsername, string& tempPassword, string& tempAuthority);
void loginUsername(string& tempUsername, string& tempPassword, string& tempAuthority);
void loginPassword(string tempPassword);
void incorrectPassword(string tempPassword);

void adminCheck();

void mainMenu(string tempUsernamesername, string tempAuthority);
void profile(string& tempUsername, string& tempPassword, string tempAuthority);
void sendMessages(string tempUsername);
void inbox(string tempUsername);
void schedule(string username, string authority);

void manage(string username);



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

	string username, password, authority;
	int userInput;
	getChoice(userInput, 3);

	switch (userInput)
	{
	case 1:
		cout << "Create Account." << endl;
		createAcc(username, password, authority);
		break;
	case 2:
		cout << "Log In." << endl;
		loginUsername(username, password, authority);
		break;
	case 3:
		cout << "Exit." << endl;
		cout << "\nGoodbye!\n\n";
		exit(3);
	}

	while (true)
	{
		mainMenu(username, authority);
		getChoice(userInput, 6);

		switch (userInput)
		{
		case 1:
			cout << "Profile." << endl;
			profile(username, password, authority);
			break;

		case 2:
			cout << "Schedule." << endl;
			schedule(username, authority);
			break;

		case 3:
			cout << "Message." << endl;
			sendMessages(username);
			break;

		case 4:
			cout << "Inbox." << endl;
			inbox(username);
			break;

		case 5:
			if (authority == "1")
			{
				cout << "Manage." << endl;
				manage(username);
				break;
			}
			else
			{
				cout << "Exit." << endl;
				exit(0);
			}
			break;

		case 6:
			if (authority == "1")
			{
				cout << "Exit." << endl;
				exit(0);
			}
			else
			{
				cout << "Invalid option.";
				exit(0);
			}
		}
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

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Invalid input. Please enter an integer: ";
		cin >> choice;

		if (!(cin.fail()))
			if ((choice < 1) || (limit < choice))
			{
				cout << "Invalid Choice, Please Select a Valid Option: ";
				cin.clear();
				cin.ignore(100, '\n');
				cin >> choice;
			}
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

void createAcc(string& tempUsername, string& tempPassword, string& tempAuthority)
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
	int lineNumber = 0;
	tempAuthority = "0";
	tempPassword = "placeholder";
	
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
				createAcc(tempUsername, tempPassword, tempAuthority);
				return;
			}
	}
	accountsFile << userInput << endl;
	tempUsername = userInput;
	cout << "Input password: ";
	getline(cin, userInput);
	accountsFile << userInput << endl << "0" << endl;
	tempPassword = userInput;
	tempAuthority = "0";
	
	accountsFile.close();
	usernameCheck.close();
	cout << "Successfully created account." << endl;
}

void loginUsername(string& tempUsername, string& tempPassword, string& tempAuthority)
{
	ifstream accountsFile;
	accountsFile.open("accounts.txt");
	if (accountsFile.fail())
	{
		cout << "Input file failed to open.";
		exit(1);
	}

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
	loginUsername(tempUsername, tempPassword, tempAuthority);
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
	int lineNumber = 0;
	usernamesFile.seekg(0, ios::beg);
	while (getline(usernamesFile, temp))
	{
		lineNumber++;
		if (lineNumber % 3 == 0)
			if (temp == "1")
			{
				usernamesFile.close();
				accountsFile.close();
				return;
			}
	}
	accountsFile << "admin" << endl << "123456" << endl << "1" << endl;
	accountsFile.close();
	usernamesFile.close();
}

void sendMessages(string tempUsername)
{
	ifstream accountsFile("accounts.txt");
	ofstream messageFile;
	string input, message, username, temp;
	int lineNumber = 0, choice;

	cout << "=================Monkey Business=================" << endl
		<< "User: " << tempUsername << endl
		<< "-------------------------------------------------" << endl
		<< "|Send Messages. " << endl
		<< "|Input reciever's username. " << endl
		<< "|Input: ";

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

				cout << "\n=================Monkey Business=================" << endl
					<< "User: " << tempUsername << endl
					<< "-------------------------------------------------" << endl
					<< "|Send Messages. " << endl
					<< "|Input message: ";

				getline(cin, message);

				messageFile << "=================================================" << endl;
				messageFile << "From: " << tempUsername << endl;
				messageFile << "To: " << temp << endl << endl;

				messageFile << message << endl << endl;

				messageFile.close();
				
				cout << "|" << endl
					<< "|Sent!" << endl
					<< "|[1] Back." << endl
					<< "|Input: ";

				getChoice(choice, 1);

				switch (choice)
				{
				case 1:
					cout << "Back." << endl;
					return;
				}
			}
		}
	}
	cout << "User does not exist, try again." << endl;
	sendMessages(tempUsername);
}

void mainMenu(string username, string authority)
{
	cout << "\n=================Monkey Business=================" << endl
		<< " User: " << username << endl
		<< "-------------------------------------------------" << endl
		<< "|Profile  [1]|" << endl
		<< "|Schedule [2]|" << endl
		<< "|Messages [3]|" << endl
		<< "|Inbox    [4]|" << endl;

	if (authority == "1")
		cout << "|Manage   [5]|" << endl
		<< "|Exit     [6]|" << endl;
	else
		cout << "|Exit     [5]|" << endl;

	cout << "|Input: ";

	return;
}

void inbox(string tempUsername)
{
	string contents;
	ifstream inbox;

	cout << "=================Monkey Business=================" << endl
		<< "User: " << tempUsername << "'s Inbox" << endl << endl << endl;

	tempUsername += ".txt";

	inbox.open(tempUsername);
	if (inbox.fail())
	{
		cout << "Inbox Empty: No messages.";
	}

	while (getline(inbox, contents))
	{
		cout << contents << endl;
	}
}

void profile(string& tempUsername, string& tempPassword, string tempAuthority)
{

	ifstream fin("accounts.txt");
	ofstream fout("accounts.txt", ios::app);

	string line, replacement;

	int choice, lineNumber = 0;

	if (tempAuthority == "1")
	{
		cout << "=================Monkey Business=================" << endl
			<< "User: " << tempUsername << endl
			<< "-------------------------------------------------" << endl
			<< "|Profile  [*]| Username: " << tempUsername << endl
			<< "|Schedule [ ]| Password: " << tempPassword << endl
			<< "|Messages [ ]| Salary: " << endl
			<< "|Inbox    [ ]|" << endl
			<< "|Manage   [ ]|                            Back[1]" << endl
			<< "|Input : ";
	}
	else
	{
		cout << "=================Monkey Business=================" << endl
			<< "User: " << tempUsername << endl
			<< "-------------------------------------------------" << endl
			<< "|Profile  [*]| Username: " << tempUsername << endl
			<< "|Schedule [ ]| Password: " << tempPassword << endl
			<< "|Messages [ ]| " << endl
			<< "|Inbox    [ ]|                            Back[1]" << endl
			<< "|Input : ";
	}

	getChoice(choice, 1);

	switch (choice)
	{
	case 1:
		return;
	}

}

void manage(string username)
{
	ifstream accountList("accounts.txt");
	ofstream promotion("accounts.txt", ios::app);
	string line, temp, eName;
	int lineNum = 0, choice;

	cout << "\n=================Monkey Business=================" << endl
		<< " User: " << username << endl
		<< "-------------------------------------------------" << endl
		<< "|Profile  [ ]| [1] Account list" << endl
		<< "|Schedule [ ]| [2] Promote" << endl
		<< "|Messages [ ]|" << endl
		<< "|Inbox    [ ]|                            Back[4]" << endl
		<< "|Manage   [*]|" << endl
		<< "|Input : ";

	getChoice(choice, 3);

	switch (choice)
	{
	case 1:
		lineNum = 0;
		cout << "Account list.\n";

		cout << "\n=================Monkey Business=================" << endl
			<< " User: " << username << endl
			<< "-------------------------------------------------" << endl
			<< "| Account List |" << endl;

		accountList.seekg(0, ios::beg);
		while (getline(accountList, line))
		{
			lineNum++;

			if (lineNum % 3 == 1)
			{
				cout << line << endl;
			}
		}

		cout << "                                          Back[1]" << endl;
		cout << "Input: ";

		getChoice(choice, 1);

		switch (choice)
		{
		case 1:
			manage(username);
		}

	case 2:
		lineNum = 0;
		cout << "Promote. \n";
		
		cout << "\n=================Monkey Business=================" << endl
			<< " User: " << username << endl
			<< "-------------------------------------------------" << endl
			<< "| Promote " << endl
			<< "| Enter employee username." << endl
			<< "| Input: ";

		getline(cin, eName);

		

		accountList.seekg(0, ios::beg);
		while (getline(accountList, line))
		{
			lineNum++;

			if (lineNum % 3 == 1)
			{
				if (line == eName)
				{
					accountList.seekg(0, ios::beg);
					for (int i = 0; i < lineNum + 2; i++)
					{
						getline(accountList, line);
					}
					
					if (line == "0")
					{

						accountList.seekg((lineNum - 1) * line.length(), ios::beg);// Somehow get this to replace the 0 with a 1!
						promotion.write("1", 1);
						cout << "User " << eName << " promoted to admin." << endl;
						promotion.close();
						exit(12);
					}
					else
					{
						cout << "This user is already an admin." << endl;
					}
				}
			}
		}
		exit(13);

	case 3:
		cout << "Back. \n";
		return;
	}

}

void schedule(string username, string authority) {

	int choice;

	if (authority == "1")
	{
		cout << "=========================Monkey Business================================" << endl
			<< "User: " << username << endl
			<< "-------------------------------------------------------------------------" << endl
			<< "|Profile  [ ]|	M	T	W	R	F	S	U	" << endl
			<< "|Schedule [*]|	9am	9am	9am	9am	9am	10am	10am" << endl
			<< "|Messages [ ]|	to	to	to	to	to	to	to	" << endl
			<< "|Inbox    [ ]|	5pm	5pm	5pm	5pm	5pm	4pm	4pm	" << endl
			<< "|Manage   [ ]|-----------------------------------------------------------" << endl
			<< "							       Back[1]" << endl;
	}
	else
	{
		cout << "=========================Monkey Business================================" << endl
			<< "User: " << username << endl
			<< "-------------------------------------------------------------------------" << endl
			<< "|Profile  [ ]|	M	T	W	R	F	S	U	" << endl
			<< "|Schedule [*]|	9am	9am	9am	9am	9am	10am	10am" << endl
			<< "|Messages [ ]|	to	to	to	to	to	to	to	" << endl
			<< "|Inbox    [ ]|	5pm	5pm	5pm	5pm	5pm	4pm	4pm	" << endl
			<< "-------------------------------------------------------------------------" << endl
			<< "							       Back[1]" << endl;
	}

	getChoice(choice, 1);

	switch (choice)
	{
	case 1:
		return;
	}

}
