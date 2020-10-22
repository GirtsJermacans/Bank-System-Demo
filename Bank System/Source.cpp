#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>

using namespace std;
struct account {
	string accType = "available";
	int sortCode;
	int accNo;
	string accHolder;
	// int dayOpen;
	// int yearOpen;
	// string monthOpen;
	char status;
	double initDeposit;
	double availBalance;
	double latestTxn;
	char overdraftStatus;
	double overdraftLimit;
};

void MainDisplay(int&);
void CreateNewAccount(account[]);
void TurnOff(bool&);
void ViewCurrentAccountHolders(account[]);
void WithdrawMoney(account[]);
void DepositMoney(account[]);
void ViewAccountBalance(account[]);
void AdditionalOptions(int&);
void DisplayAccount(account[], int);
void ChangeAccountType(account[], int);
void DepositMoneyFromAccount(account[], int);
void CashOutFromAccount(account[], int);
void Overdraft(account[], int);
void ChangeAccountStatus(account[], int);
void LoadAccountsFromFile(account[]);
void WriteToFile(account[], int);
void UpdateFile(account[]);

int main()
{
	account AllAccounts[1000];
	LoadAccountsFromFile(AllAccounts);
	bool systemOn = true;
	while (systemOn)
	{
		system("CLS");
		int option = 0;
		cout << "::: Welcome to The Bank :::\n\n";
		MainDisplay(option);
		while (option < 1 || option > 6)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("CLS");
			cout << "Wrong Input" << endl;
			MainDisplay(option);
		}
		switch (option)
		{
		case 1: 
			system("CLS");
			CreateNewAccount(AllAccounts);
			break;
		case 2:
			system("CLS");
			ViewCurrentAccountHolders(AllAccounts);
			break;
		case 3:
			system("CLS");
			WithdrawMoney(AllAccounts);
			break;
		case 4:
			system("CLS");
			DepositMoney(AllAccounts);
			break;
		case 5:
			system("CLS");
			ViewAccountBalance(AllAccounts);
			break;
		case 6:
			system("CLS");
			TurnOff(systemOn);
			break;
		default:
			break;
		}

		system("Pause");
	}
	return 0;
}

void MainDisplay(int &option)
{
	cout << "Branch Girts System" << endl;
	cout << "Select from the menu below: " << endl;
	cout << "\t1 : Create a New Account" << endl;
	cout << "\t2 : View Current Account Holders" << endl;
	cout << "\t3 : Withdrawal - Over the Counter" << endl;
	cout << "\t4 : Deposit - Over the Counter" << endl;
	cout << "\t5 : Account Balance" << endl; // Show the balance for the given sort code and account number
	cout << "\t6 : Logout" << endl;
	cin >> option;
}

void CreateNewAccount(account list[])
{
	int accountIndex;
	for (int i = 0; i < 1000; i++)
	{
		if (list[i].accType == "available")
		{
			accountIndex = i;
			i = 1000;
		}
	}
	int input = 0;
	string name = "";
	string surname = "";
	bool falseName = false;
	double deposit = 0;

	// setting up the type of account
	cout << "::: Create New Account :::\n" << endl;
	cout << "Please Select the Type of Account Required:" << endl;
	cout << "\t1 : Basic Current Account" << endl;
	cout << "\t2 : Advance Current Account" << endl;
	cin >> input;
	system("CLS");
	while (input < 1 || input > 2)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "::: Create New Account :::\n" << endl;
		cout << "Wrong Input - Please Select From Below Options: " << endl;
		cout << "\t1 : Basic Current Account" << endl;
		cout << "\t2 : Advance Current Account" << endl;
		cin >> input;
		system("CLS");
	}
	if (input == 1)
		list[accountIndex].accType = "Basic Current Account";
	if (input == 2)
		list[accountIndex].accType = "Advance Current Account";

	// setting up account holder name

	while (name == "")
	{
		cout << "::: Create New Account :::\n" << endl;
		cout << "Please Enter a First Name Of Account Holder: " << endl;
		cin.ignore();
		getline(cin, name);
		for (int i = 0; i < name.length(); i++)
		{
			if (name[i] == ' ')
			{
				falseName = true;
				i = name.length();
			}
		}
		while (falseName)
		{
			falseName = false;
			system("CLS");
			cout << "::: Create New Account :::\n" << endl;
			cout << "No Spaces Allowed" << endl;
			cout << "Please Enter a First Name Of Account Holder: " << endl;
			cin.ignore(0);
			getline(cin, name);
			for (int i = 0; i < name.length(); i++)
			{
				if (name[i] == ' ')
				{
					falseName = true;
					i = name.length();
				}
			}
		}
		system("CLS");
	}

	while (surname == "")
	{
		cout << "::: Create New Account :::\n" << endl;
		cout << "Please Enter a Surname Of Account Holder: " << endl;
		cin.ignore(0);
		getline(cin, surname);
		for (int j = 0; j < surname.length(); j++)
		{
			if (surname[j] == ' ')
			{
				falseName = true;
				j = surname.length();
			}
		}
		while (falseName)
		{
			system("CLS");
			falseName = false;
			cout << "::: Create New Account :::\n" << endl;
			cout << "No Spaces Allowed" << endl;
			cout << "Please Enter a Surname Of Account Holder: " << endl;
			cin.ignore(0);
			getline(cin, surname);
			for (int i = 0; i < surname.length(); i++)
			{
				if (surname[i] == ' ')
				{
					falseName = true;
					i = surname.length();
				}
			}
		}
		list[accountIndex].accHolder = name + " " + surname;
		system("CLS");
	}

	// setting up initial deposit and account balance, and latest transaction
	cout << "::: Create New Account :::\n" << endl;
	cout << "How Much Money Would You Like to Deposit? Minimum \x9c" << "10" << endl;
	cin >> deposit;
	system("CLS");
	if (list[accountIndex].accType == "Basic Current Account")
	{
		while (deposit < 10 || deposit > 85000)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "::: Create New Account :::\n" << endl;
			cout << "For Basic Current Account Minimum Deposit is \x9c" << "10 and Maximum Deposit is \x9c" << "85000 : " << endl;
			cin >> deposit;
			system("CLS");
		}
		list[accountIndex].initDeposit = deposit;
	}

	if (list[accountIndex].accType == "Advance Current Account")
	{
		while (deposit < 10 || deposit > 150000)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "::: Create New Account :::\n" << endl;
			cout << "For Advance Current Account minimum deposit is \x9c" << "10 and maximum deposit is \x9c" << "150000 : " << endl;
			cin >> deposit;
			system("CLS");
		}
		list[accountIndex].initDeposit = deposit;
	}

	// setting up overdraft status and limit
	cout << "::: Create New Account :::\n" << endl;
	cout << "1. Set Up Overdraft " << endl;
	cout << "2. Skip Overdraft " << endl;
	int input3 = 0;
	cin >> input3;
	system("CLS");
	while (input3 < 1 || input3 > 2)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "::: Create New Account :::\n" << endl;
		cout << "Please Select From Options Below: " << endl;
		cout << "1. Set Up Overdraft " << endl;
		cout << "2. Skip Overdraft " << endl;
		cin >> input3;
		system("CLS");
	}

	if (input3 == 1)
	{
		list[accountIndex].overdraftStatus = 'A';
		if (list[accountIndex].accType == "Basic Current Account")
			list[accountIndex].overdraftLimit = 200;

		if (list[accountIndex].accType == "Advance Current Account")
			list[accountIndex].overdraftLimit = 1000;
	}

	if (input3 == 2)
	{
		list[accountIndex].overdraftStatus = 'I';
		list[accountIndex].overdraftLimit = 0;
	}

	// setting up sort-code and account number
	int accountNumber = rand() % 89999999 + 10000000;
	for (int i = 0; i < 1000; i++)
	{
		if (list[i].accNo == accountNumber)
		{
			accountNumber = rand() % 89999999 + 10000000;
			i = -1;
		}
		else
		{
			list[accountIndex].accNo = accountNumber;
			i = 1000;
		}
	}

	int sortCode = rand() % 899999 + 100000;
	for (int i = 0; i < 1000; i++)
	{
		if (list[i].sortCode == sortCode)
		{
			sortCode = rand() % 899999 + 100000;
			i = -1;
		}
		else
		{
			list[accountIndex].sortCode = sortCode;
			i = 1000;
		}
	}

	// setting up status of new account, balance, latest transaction
	list[accountIndex].status = 'A';
	list[accountIndex].availBalance = deposit;
	list[accountIndex].latestTxn = deposit;

	WriteToFile(list, accountIndex);

	// confirm account created
	cout << "::: Create New Account :::\n" << endl;
	cout << "New Account Has Been Created" << endl;
}

void TurnOff(bool &Off)
{
	Off = false;
	cout << "::: Branch Girts System :::\n" << endl;
	cout << "Thank You For Using Branch Girts System" << endl;
}

void ViewCurrentAccountHolders(account list[])
{
	cout << "::: All Accounts :::\n" << endl;
	for (int i = 0; i < 1000; i++)
	{
		if (list[i].accType != "available")
		{
			cout << "Account Holder: " << list[i].accHolder << endl;
			cout << "Account Number: " << list[i].accNo << endl;
			cout << "Account Sort-Code: " << list[i].sortCode << endl;
			cout << "Account Status: " << list[i].status << endl;
			if (list[i].availBalance > list[i].latestTxn)
				cout << "Latest Transaction : Deposit \x9c" << list[i].availBalance - list[i].latestTxn << "\n\n";
			if (list[i].availBalance < list[i].latestTxn)
				cout << "Latest Transacton : CashOut \x9c" << list[i].latestTxn - list[i].availBalance << "\n\n";
			if (list[i].availBalance == list[i].latestTxn)
				cout << "Latest Transaction : None" << "\n\n";
		}
		else
		{
			i = 1000;
			cout << "Press Enter To Continue" << endl;
		}
	}
}

void WithdrawMoney(account list[])
{
	int sortCode = 0;
	int bankAccount = 0;
	int index = 0;
	bool falseSortCode = true;
	bool falseAccountNumber = true;
	cout << "::: Withdraw Money :::\n" << endl;
	while (falseSortCode)
	{
		cout << "Please Insert Sort-Code: " << endl;
		cin >> sortCode;
		while (sortCode < 100000 || sortCode > 999999)
		{
			system("CLS");
			cout << "::: Withdraw Money :::\n" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Max 6 Digits Allowed For Sort-Code: " << endl;
			cin >> sortCode;
		}
		for (int i = 0; i < 1000; i++)
		{
			if (list[i].sortCode == sortCode)
			{
				falseSortCode = false;
				index = i;
				i = 1000;
			}
			if (i == 999 && list[i].sortCode != sortCode)
			{
				cout << "Wrong Sort-Code Inserted" << endl;
				falseSortCode = false;
				falseAccountNumber = false;
			}
		}
	}

	while (falseAccountNumber)
	{
		cout << "Please Insert Account Number: " << endl;
		cin >> bankAccount;
		while (bankAccount < 10000000 || bankAccount > 99999999)
		{
			cout << "::: Withdraw Money :::\n" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Max 8 Digits Allowed For Account Number: " << endl;
			cin >> bankAccount;
			system("CLS");
		}
		if (list[index].accNo != bankAccount)
		{
			cout << "::: Withdraw Money :::\n" << endl;
			cout << "Wrong Account Number Inserted" << endl;
			falseAccountNumber = false;
		}
		if (list[index].accNo == bankAccount && list[index].status == 'A')
		{
			double input = 0;
			system("CLS");
			cout << "::: Withdraw Money :::\n" << endl;
			cout << "Account Type: " << list[index].accType << endl;
			cout << "Account Holder Name: " << list[index].accHolder << endl;
			cout << "Account Balance: \x9c" << list[index].availBalance << "\n\n";
			cout << "How Much Would You Like To Withdraw? " << endl;
			cin >> input;
			while ((input < 0.01 || input > list[index].availBalance) || (input > 400))
			{
				system("CLS");
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "::: Withdraw Money :::\n" << endl;
				cout << "Account Type: " << list[index].accType << endl;
				cout << "Account Holder Name: " << list[index].accHolder << endl;
				cout << "Account Balance: \x9c" << list[index].availBalance << "\n\n";
				if (input < 0.01)
					cout << "Please Input Valid Amount You Would Like To Withdraw: " << endl;
				if ((input > list[index].availBalance) && (input < 400))
					cout << "You Don't Have So Much Money : " << endl;
				if (input > 400)
					cout << "Max Withdrawal Today is \x9c" << "400 : " << endl;
				cin >> input;
			}
			list[index].latestTxn = list[index].availBalance;
			list[index].availBalance = list[index].availBalance - input;
			system("CLS");
			cout << "::: Withdraw Money :::\n" << endl;
			cout << "Account Type: " << list[index].accType << endl;
			cout << "Account Holder Name: " << list[index].accHolder << endl;
			cout << "Account Balance: \x9c" << list[index].availBalance << "\n\n";
			cout << "You Have Cashed Out: \x9c" << input << endl;
			UpdateFile(list);
		}
		if (list[index].accNo == bankAccount && list[index].status == 'I')
		{
			system("CLS");
			cout << "::: Withdraw Money :::\n" << endl;
			cout << "Account Is Closed - Can't Withdraw Money" << endl;
		}
		if (list[index].accNo == bankAccount && list[index].status == 'S')
		{
			system("CLS");
			cout << "::: Withdraw Money :::\n" << endl;
			cout << "Account Is Suspended - Can't Withdraw Money" << endl;
		}
		if (list[index].accNo == bankAccount && list[index].status == 'U')
		{
			system("CLS");
			cout << "::: Withdraw Money :::\n" << endl;
			cout << "Account Is Under Investigation - Can't Withdraw Money" << endl;
		}
		falseAccountNumber = false;
	}
}

void DepositMoney(account list[])
{
	int sortCode = 0;
	int bankAccount = 0;
	int index = 0;
	bool falseSortCode = true;
	bool falseAccountNumber = true;
	cout << "::: Deposit Money :::\n" << endl;
	while (falseSortCode)
	{
		cout << "Please Insert Sort-Code: " << endl;
		cin >> sortCode;
		while (sortCode < 100000 || sortCode > 999999)
		{
			system("CLS");
			cout << "::: Deposit Money :::\n" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Max 6 Digits Allowed For Sort-Code: " << endl;
			cin >> sortCode;
		}
		for (int i = 0; i < 1000; i++)
		{
			if (list[i].sortCode == sortCode)
			{
				falseSortCode = false;
				index = i;
				i = 1000;
			}
			if (i == 999 && list[i].sortCode != sortCode)
			{
				cout << "Wrong Sort-Code Inserted" << endl;
				falseAccountNumber = false;
				falseSortCode = false;
			}
		}
	}

	while (falseAccountNumber)
	{
		cout << "Please Insert Account Number: " << endl;
		cin >> bankAccount;
		while (bankAccount < 10000000 || bankAccount > 99999999)
		{
			cout << "::: Deposit Money :::\n" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Max 8 Digits Allowed For Account Number: " << endl;
			cin >> bankAccount;
			system("CLS");
		}
		if (list[index].accNo != bankAccount)
		{
			cout << "::: Deposit Money :::\n" << endl;
			cout << "Wrong Account Number Inserted" << endl;
			falseAccountNumber = false;
		}
		if (list[index].accNo == bankAccount && list[index].status == 'A')
		{
			double input = 0;
			system("CLS");
			cout << "::: Deposit Money :::\n" << endl;
			cout << "Account Type: " << list[index].accType << endl;
			cout << "Account Holder Name: " << list[index].accHolder << endl;
			cout << "Account Balance: \x9c" << list[index].availBalance << "\n\n";
			cout << "How Much Would You Like To Deposit? " << endl;
			cin >> input;
			if (list[index].accType == "Basic Current Account")
			{
				while (input < 0.01 || list[index].availBalance + input > 85000)
				{
					system("CLS");
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cout << "::: Deposit Money :::\n" << endl;
					cout << "Account Type: " << list[index].accType << endl;
					cout << "Account Holder Name: " << list[index].accHolder << endl;
					cout << "Account Balance: \x9c" << list[index].availBalance << "\n\n";
					cout << "Max Available Deposit is \x9c" << 85000 - list[index].availBalance << endl;
					cout << "Please Input Valid Amount You Would Like To Deposit: " << endl;
					cin >> input;
				}
			}
			if (list[index].accType == "Advance Current Account")
			{
				while (input < 0.01 || list[index].availBalance + input > 150000)
				{
					system("CLS");
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cout << "::: Deposit Money :::\n" << endl;
					cout << "Account Type: " << list[index].accType << endl;
					cout << "Account Holder Name: " << list[index].accHolder << endl;
					cout << "Account Balance: \x9c" << list[index].availBalance << "\n\n";
					cout << "Max Available Deposit is \x9c" << 150000 - list[index].availBalance << endl;
					cout << "Please Input Valid Amount You Would Like To Deposit" << endl;
					cin >> input;
				}
			}
			list[index].latestTxn = list[index].availBalance;
			list[index].availBalance = list[index].availBalance + input;
			system("CLS");
			cout << "::: Deposit Money :::\n" << endl;
			cout << "Account Type: " << list[index].accType << endl;
			cout << "Account Holder Name: " << list[index].accHolder << endl;
			cout << "Account Balance: \x9c" << list[index].availBalance << "\n\n";
			cout << "You Have Deposited : \x9c" << input << endl;
			UpdateFile(list);
		}

		if (list[index].accNo == bankAccount && list[index].status == 'I')
		{
			system("CLS");
			cout << "::: Deposit Money :::\n" << endl;
			cout << "Account Is Closed - Can't Deposit Money" << endl;
		}

		if (list[index].accNo == bankAccount && list[index].status == 'S')
		{
			system("CLS");
			cout << "::: Deposit Money :::\n" << endl;
			cout << "Account Is Suspended - Can't Deposit Money" << endl;
		}

		if (list[index].accNo == bankAccount && list[index].status == 'U')
		{
			system("CLS");
			cout << "::: Deposit Money :::\n" << endl;
			cout << "Account Is Under Investigation - Can't Deposit Money" << endl;
		}
		falseAccountNumber = false;
	}
}

void ViewAccountBalance(account list[])
{
	int sortCode = 0;
	int bankAccount = 0;
	int index = 0;
	bool falseSortCode = true;
	bool falseAccountNumber = true;
	cout << "::: Account Balance :::\n" << endl;
	while (falseSortCode)
	{
		cout << "Please Insert Sort-Code: " << endl;
		cin >> sortCode;
		while (sortCode < 100000 || sortCode > 999999)
		{
			system("CLS");
			cout << "::: Account Balance :::\n" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Max 6 Digits Allowed For Sort-Code: " << endl;
			cin >> sortCode;
		}
		for (int i = 0; i < 1000; i++)
		{
			if (list[i].sortCode == sortCode)
			{
				falseSortCode = false;
				index = i;
				i = 1000;
			}
			if (i == 999 && list[i].sortCode != sortCode)
			{
				cout << "Wrong Sort-Code Inserted" << endl;
				falseSortCode = false;
				falseAccountNumber = false;
			}
		}
	}

	while (falseAccountNumber)
	{
		cout << "Please Insert Account Number: " << endl;
		cin >> bankAccount;
		while (bankAccount < 10000000 || bankAccount > 99999999)
		{
			cout << "::: Account Balance :::\n" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Max 8 Digits Allowed For Account Number: " << endl;
			cin >> bankAccount;
			system("CLS");
		}
		if (list[index].accNo != bankAccount)
		{
			cout << "::: Account Balance :::\n" << endl;
			cout << "Wrong Account Number Inserted" << endl;
			falseAccountNumber = false;
		}
		if (list[index].accNo == bankAccount)
		{
			system("CLS");
			cout << "::: Account Balance :::\n" << endl;
			cout << "Account Holder: " << list[index].accHolder << endl;
			cout << "Available Balance: \x9c" << list[index].availBalance << "\n" << endl;
			falseAccountNumber = false;

			int option = 0;
			AdditionalOptions(option);
			while (option < 1 || option > 2)
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				system("CLS");
				cout << "::: Account Balance :::\n" << endl;
				cout << "Account Holder: " << list[index].accHolder << endl;
				cout << "Available Balance: \x9c" << list[index].availBalance << endl;
				cout << "Wrong Input\n" << endl;
				AdditionalOptions(option);
			}

			switch (option)
			{
			case 1:
				system("CLS");
				DisplayAccount(list, index);
				break;
			default:
				break;
			}
		}
	}
}

void AdditionalOptions(int &option)
{
	cout << "Select From Options Below : " << endl;
	cout << "\t1 : View Full Account Details" << endl;
	cout << "\t2 : Go Back" << endl;
	cin >> option;
}

void DisplayAccount(account list[], int index)
{
	bool processActive = true;
	while (processActive)
	{
		int selection = 0;
		cout << "::: Account Full Info :::\n" << endl;
		cout << "Account Type : " << list[index].accType << endl;
		cout << "Account Holder : " << list[index].accHolder << endl;
		cout << "Account Number : " << list[index].accNo << endl;
		cout << "Account Sort-Code : " << list[index].sortCode << endl;
		cout << "Available Balance : \x9c" << list[index].availBalance << endl;
		if (list[index].availBalance > list[index].latestTxn)
			cout << "Latest Transaction : Deposit \x9c" << list[index].availBalance - list[index].latestTxn << "\n\n";
		if (list[index].availBalance < list[index].latestTxn)
			cout << "Latest Transacton : CashOut \x9c" << list[index].latestTxn - list[index].availBalance << "\n\n";
		if (list[index].availBalance == list[index].latestTxn)
			cout << "Latest Transaction : None" << "\n\n";
		cout << "Initial Deposit : \x9c" << list[index].initDeposit << endl;
		cout << "Overdraft Status : " << list[index].overdraftStatus << endl;
		cout << "Overdraft Limit : \x9c" << list[index].overdraftLimit << endl;
		cout << "Account Status : " << list[index].status << "\n" << endl;

		if (list[index].accType == "Basic Current Account")
			cout << "\t1 : Upgrade Account Type to Advanced" << endl;
		if (list[index].accType == "Advance Current Account")
			cout << "\t1 : Change Account Type To Basic" << endl;
		cout << "\t2 : Deposit Cash" << endl;
		cout << "\t3 : Withdraw Cash" << endl;
		if (list[index].overdraftStatus == 'I')
			cout << "\t4 : Set Up Overdraft" << endl;
		else if (list[index].overdraftStatus == 'A')
			cout << "\t4 : Cancel Overdraft" << endl;
		cout << "\t5 : Change Account Status" << endl;
		cout << "\t6 : Exit Account" << endl;
		cin >> selection;

		while (selection < 1 || selection > 6)
		{
			system("CLS");
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "::: Account Full Info :::\n" << endl;
			cout << "Account Type : " << list[index].accType << endl;
			cout << "Account Holder : " << list[index].accHolder << endl;
			cout << "Account Number : " << list[index].accNo << endl;
			cout << "Account Sort-Code : " << list[index].sortCode << endl;
			cout << "Available Balance : \x9c" << list[index].availBalance << endl;
			if (list[index].availBalance > list[index].latestTxn)
				cout << "Latest Transaction : Deposit \x9c" << list[index].availBalance - list[index].latestTxn << "\n\n";
			if (list[index].availBalance < list[index].latestTxn)
				cout << "Latest Transacton : CashOut \x9c" << list[index].latestTxn - list[index].availBalance << "\n\n";
			if (list[index].availBalance == list[index].latestTxn)
				cout << "Latest Transaction : None" << "\n\n";
			cout << "Initial Deposit : \x9c" << list[index].initDeposit << endl;
			cout << "Overdraft Status : " << list[index].overdraftStatus << endl;
			cout << "Overdraft Limit : \x9c" << list[index].overdraftLimit << endl;
			cout << "Account Status : " << list[index].status << "\n" << endl;
			cout << "Please Select Option From Below:" << endl;
			if (list[index].accType == "Basic Current Account")
				cout << "\t1 : Upgrade Account Type to Advanced" << endl;
			if (list[index].accType == "Advance Current Account")
				cout << "\t1 : Change Account Type To Basic" << endl;
			cout << "\t2 : Deposit Cash" << endl;
			cout << "\t3 : Withdraw Cash" << endl;
			if (list[index].overdraftStatus == 'I')
				cout << "\t4 : Set Up Overdraft" << endl;
			else if (list[index].overdraftStatus == 'A')
				cout << "\t4 : Cancel Overdraft" << endl;
			cout << "\t5 : Change Account Status" << endl;
			cout << "\t6 : Exit Account" << endl;
			cin >> selection;
		}

		switch (selection)
		{
		case 1:
			system("CLS");
			ChangeAccountType(list, index);
			break;
		case 2:
			system("CLS");
			DepositMoneyFromAccount(list, index);
			break;
		case 3:
			system("CLS");
			CashOutFromAccount(list, index);
			break;
		case 4:
			system("CLS");
			Overdraft(list, index);
			break;
		case 5:
			system("CLS");
			ChangeAccountStatus(list, index);
			break;
		case 6:
			system("CLS");
			processActive = false;
			break;
		default:
			break;
		}
	}
}

void ChangeAccountType(account list[], int index)
{
	int answer = 0;
	if (list[index].status == 'A')
	{
		cout << "::: Change Account Type :::\n" << endl;
		if (list[index].accType == "Basic Current Account")
		{
			cout << "Do You Want To Upgrade Your Account From Basic to Advanced?" << endl;
			cout << "\t1 : Yes" << endl;
			cout << "\t2 : No" << endl;
			cin >> answer;
			while (answer < 1 || answer > 2)
			{
				system("CLS");
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "::: Change Account Type :::\n" << endl;
				cout << "Do You Want To Upgrade Your Account From Basic to Advanced?" << endl;
				cout << "\t1 : Yes" << endl;
				cout << "\t2 : No" << endl;
				cin >> answer;
			}
			if (answer == 1)
			{
				system("CLS");
				list[index].accType = "Advance Current Account";
				cout << "Account Type Has Been Changed Succesfully\n" << endl;
				if (list[index].overdraftStatus == 'A')
				{
					list[index].overdraftLimit = 1000;
					UpdateFile(list);
				}
			}
			if (answer == 2)
			{
				system("CLS");
				cout << "Account Type Has Not Been Changed\n" << endl;
			}
		}

		else if (list[index].accType == "Advance Current Account")
		{
			cout << "Do You Want To Change Your Account From Advanced to Basic?" << endl;
			cout << "\t1 : Yes" << endl;
			cout << "\t2 : No" << endl;
			cin >> answer;
			while (answer < 1 || answer > 2)
			{
				system("CLS");
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "::: Change Account Type :::\n" << endl;
				cout << "Do You Want To Change Your Account From Advanced to Basic?" << endl;
				cout << "\t1 : Yes" << endl;
				cout << "\t2 : No" << endl;
				cin >> answer;
			}
			if (answer == 1)
			{
				system("CLS");
				list[index].accType = "Basic Current Account";
				cout << "Account Type Has Been Changed Succesfully\n" << endl;
				if (list[index].overdraftStatus == 'A')
				{
					list[index].overdraftLimit = 200;
					UpdateFile(list);
				}
			}
			if (answer == 2)
			{
				system("CLS");
				cout << "Account Type Has Not Been Changed\n" << endl;
			}
		}
	}
	if (list[index].status == 'I')
		cout << "Account Is Closed - Can't Change Account Type\n" << endl;
	if (list[index].status == 'U')
		cout << "Account Is Under Investigation - Can't Change Account Type\n" << endl;
	if (list[index].status == 'S')
		cout << "Account Is Suspended- Can't Change Account Type\n" << endl;
}

void DepositMoneyFromAccount(account list[], int index)
{
	double input = 0;
	if (list[index].status == 'A')
	{
		cout << "::: Deposit Money :::\n" << endl;
		cout << "How Much Would You Like To Deposit? " << endl;
		cin >> input;
		if (list[index].accType == "Basic Current Account")
		{
			while (input < 0.01 || list[index].availBalance + input > 85000)
			{
				system("CLS");
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "::: Deposit Money :::\n" << endl;
				cout << "Max Available Deposit is \x9c" << 85000 - list[index].availBalance << endl;
				cout << "Please Input Valid Amount You Would Like To Deposit: " << endl;
				cin >> input;
			}
		}
		if (list[index].accType == "Advance Current Account")
		{
			while (input < 0.01 || list[index].availBalance + input > 150000)
			{
				system("CLS");
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "::: Deposit Money :::\n" << endl;
				cout << "Max Available Deposit is \x9c" << 150000 - list[index].availBalance << endl;
				cout << "Please Input Valid Amount You Would Like To Deposit" << endl;
				cin >> input;
			}
		}
		list[index].latestTxn = list[index].availBalance;
		list[index].availBalance = list[index].availBalance + input;
		system("CLS");
		cout << "Deposit Has Been Accepted\n" << endl;
		UpdateFile(list);
	}
	if (list[index].status == 'I')
		cout << "Account Is Closed - Can't Make Any Deposit\n" << endl;
	if (list[index].status == 'S')
		cout << "Account Is Suspended - Can't Make Any Deposit\n" << endl;
	if (list[index].status == 'U')
		cout << "Account Is Under Investigation - Can't Make Any Deposit\n" << endl;
}

void CashOutFromAccount(account list[], int index)
{
	double input = 0;
	if (list[index].status == 'A')
	{
		cout << "::: Withdraw Money :::\n" << endl;
		cout << "Account Balance: \x9c" << list[index].availBalance << endl;
		cout << "How Much Would You Like To Cash Out? " << endl;
		cin >> input;
		while ((input < 0.01 || input > list[index].availBalance) || (input > 400))
		{
			system("CLS");
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "::: Withdraw Money :::\n" << endl;
			cout << "Available Balance: \x9c" << list[index].availBalance << endl;
			if (input < 0.01)
				cout << "Please Input Valid Amount You Would Like To Withdraw: " << endl;
			if ((input > list[index].availBalance) && (input < 400))
				cout << "You Don't Have So Much Money : " << endl;
			if (input > 400)
				cout << "Max Withdrawal Today is \x9c" << "400 : " << endl;
			cin >> input;
		}
		list[index].latestTxn = list[index].availBalance;
		list[index].availBalance = list[index].availBalance - input;
		system("CLS");
		cout << "Cash Out Has Been Complete\n" << endl;
		UpdateFile(list);
	}
	if (list[index].status == 'I')
		cout << "Account Is Closed - Can't Withdraw Any Money\n" << endl;
	if (list[index].status == 'S')
		cout << "Account Is Suspended - Can't Withdraw Any Money\n" << endl;
	if (list[index].status == 'U')
		cout << "Account Is Under Investigation - Can't Withdraw Any Money\n" << endl;
}

void Overdraft(account list[], int index)
{
	int input = 0;
	if (list[index].status == 'A')
	{
		if (list[index].overdraftStatus == 'I')
		{
			cout << "::: Overdraft :::\n" << endl;
			cout << "Do You Want To Set Up Overdraft?" << endl;
			cout << "\t1 : Yes" << endl;
			cout << "\t2 : No" << endl;
			cin >> input;
			while (input < 1 || input > 2)
			{
				system("CLS");
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "::: Overdraft :::\n" << endl;
				cout << "Do You Want To Set Up Overdraft?" << endl;
				cout << "\t1 : Yes" << endl;
				cout << "\t2 : No" << endl;
				cin >> input;
			}
			if (input == 1)
			{
				system("CLS");
				list[index].overdraftStatus = 'A';
				if (list[index].accType == "Basic Current Account")
					list[index].overdraftLimit = 200;
				if (list[index].accType == "Advance Current Account")
					list[index].overdraftLimit = 1000;
				cout << "Overdraft Has Been Set Up\n" << endl;
				UpdateFile(list);
			}
			if (input == 2)
			{
				system("CLS");
				cout << "Overdraft Is Not Set Up\n" << endl;
			}
		}

		else if (list[index].overdraftStatus == 'A')
		{
			cout << "::: Overdraft :::\n" << endl;
			cout << "Do You Want To Cancel Overdraft?" << endl;
			cout << "\t1 : Yes" << endl;
			cout << "\t2 : No" << endl;
			cin >> input;
			while (input < 1 || input > 2)
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "::: Overdraft :::\n" << endl;
				cout << "Do You Want To Cancel Overdraft?" << endl;
				cout << "\t1 : Yes" << endl;
				cout << "\t2 : No" << endl;
				cin >> input;
			}
			if (input == 1)
			{
				system("CLS");
				list[index].overdraftStatus = 'I';
				list[index].overdraftLimit = 0;
				cout << "Overdraft Has Been Cancelled Up\n" << endl;
				UpdateFile(list);
			}
			if (input == 2)
			{
				system("CLS");
				cout << "Overdraft Is Still Active\n" << endl;
			}
		}
	}
	if (list[index].status == 'I')
		cout << "Account Is Closed - Can't Change Overdraft Status\n" << endl;
	if (list[index].status == 'S')
		cout << "Account Is Suspended - Can't Change Overdraft Status\n" << endl;
	if (list[index].status == 'U')
		cout << "Account Is Under Investigation - Can't Change Overdraft Status\n" << endl;
}

void ChangeAccountStatus(account list[], int index)
{
	int input = 0;
	if (list[index].status == 'A')
	{
		cout << "::: Change Account Status :::\n" << endl;
		cout << "\t1 : Close Account" << endl;
		cout << "\t2 : Suspend Account" << endl;
		cout << "\t3 : Set Under Investigation" << endl;
		cout << "\t4 : Go Back" << endl;
		cin >> input;
		while (input < 1 || input > 4)
		{
			system("CLS");
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "::: Change Account Status :::\n" << endl;
			cout << "\t1 : Close Account" << endl;
			cout << "\t2 : Suspend Account" << endl;
			cout << "\t3 : Set Under Investigation" << endl;
			cout << "\t4 : Go Back" << endl;
			cin >> input;
		}

		if (input == 1)
		{
			list[index].status = 'I';
			list[index].availBalance = 0;
			list[index].overdraftStatus = 'I';
			list[index].overdraftLimit = 0;
			list[index].initDeposit = 0;
			list[index].latestTxn = 0;
			system("CLS");
			cout << "Account Has Been Closed\n" << endl;
			UpdateFile(list);
		}
		if (input == 2)
		{
			list[index].status = 'S';
			system("CLS");
			cout << "Account Has Been Suspended\n" << endl;
			UpdateFile(list);
		}
		if (input == 3)
		{
			list[index].status = 'U';
			system("CLS");
			cout << "Account Is Set Under Investigation\n" << endl;
			UpdateFile(list);
		}
		if (input == 4)
		{
			system("CLS");
			cout << "No Change Has been Made" << endl;
		}
	}
	else if (list[index].status == 'I')
	{
		cout << "Account Is Closed - No Change Can Be Made\n" << endl;
	}

	else if (list[index].status == 'S')
	{
		cout << "::: Change Account Status :::\n" << endl;
		cout << "\t1 : Re-Open Account" << endl;
		cout << "\t2 : Close Account" << endl;
		cout << "\t3 : Go Back" << endl;
		while (input < 1 || input > 3)
		{
			system("CLS");
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "::: Change Account Status :::\n" << endl;
			cout << "\t1 : Re-Open Account" << endl;
			cout << "\t2 : Close Account" << endl;
			cout << "\t3 : Go Back" << endl;
			cin >> input;
		}
		if (input == 1)
		{
			list[index].status = 'A';
			system("CLS");
			cout << "Account Has Been Re-Opened\n" << endl;
			UpdateFile(list);
		}
		if (input == 2)
		{
			list[index].status = 'I';
			list[index].availBalance = 0;
			list[index].overdraftStatus = 'I';
			list[index].overdraftLimit = 0;
			list[index].initDeposit = 0;
			list[index].latestTxn = 0;
			system("CLS");
			cout << "Account Has Been Closed\n" << endl;
			UpdateFile(list);
		}
		if (input == 3)
		{
			system("CLS");
			cout << "No Change Has Been Made\n" << endl;
		}
	}

	else if (list[index].status == 'U')
	{
		cout << "::: Change Account Status :::\n" << endl;
		cout << "\t1 : Re-Open Account" << endl;
		cout << "\t2 : Close Account" << endl;
		cout << "\t3 : Go Back" << endl;
		while (input < 1 || input > 3)
		{
			system("CLS");
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "::: Change Account Status :::\n" << endl;
			cout << "\t1 : Re-Open Account" << endl;
			cout << "\t2 : Close Account" << endl;
			cout << "\t3 : Go Back" << endl;
			cin >> input;
		}
		
		if (input == 1)
		{
			system("CLS");
			list[index].status = 'A';
			cout << "Account Has Been Re-Opened\n" << endl;
			UpdateFile(list);
		}
		if (input == 2)
		{
			system("CLS");
			list[index].status = 'I';
			list[index].availBalance = 0;
			list[index].overdraftStatus = 'I';
			list[index].overdraftLimit = 0;
			list[index].initDeposit = 0;
			list[index].latestTxn = 0;
			cout << "Account Has Been Closed\n" << endl;
			UpdateFile(list);
		}
		if (input == 3)
		{
			system("CLS");
			cout << "No Change Has Been Made\n" << endl;
		}
	}
}

void LoadAccountsFromFile(account list[])
{
	vector<string> values;
	ifstream file;
	string data;
	file.open("accounts.csv", ios::in);
	if (file.fail())
	{
		cout << "Error Loading Account Information" << endl;
		cout << "Get In Touch With Systems Team\n" << endl;
	}
	else
	{
		int i = 0;
		string character;
		while (getline(file, data, ','))
		{
			values.push_back(data);
		}
		for (int j = 0; j < values.size()-1; j++)
		{
			string stopingNewLine;
			stopingNewLine = values.at(j);
			if (stopingNewLine[0] == '\n')
			{
				stopingNewLine.substr(1);
				stopingNewLine.replace(0, 1, "");
			}
			list[i].accType = stopingNewLine;
			list[i].accNo = stoi(values.at(j+1));
			list[i].accHolder = values.at(j+2);
			list[i].sortCode = stoi(values.at(j+3));
			character = values.at(j+4);
			list[i].overdraftStatus = character[0];
			list[i].overdraftLimit = stoi(values.at(j+5));
			list[i].initDeposit = stoi(values.at(j+6));
			list[i].availBalance = stoi(values.at(j+7));
			list[i].latestTxn = stoi(values.at(j+8));
			character = values.at(j+9);
			list[i].status = character[0];
			j += 9;
			++i;
		}
		file.close();
	}
}

void WriteToFile(account list[], int index)
{
	ofstream file;
	file.open("accounts.csv", ios::app);
	if (file.fail())
	{
		cout << "Issue With Writing To File - Get In Touch With IT Team" << endl;
	}
	else
	{
		file << list[index].accType << ",";
		file << list[index].accNo << ",";
		file << list[index].accHolder << ",";
		file << list[index].sortCode << ",";
		file << list[index].overdraftStatus << ",";
		file << list[index].overdraftLimit << ",";
		file << list[index].initDeposit << ",";
		file << list[index].availBalance << ",";
		file << list[index].latestTxn << ",";
		file << list[index].status << ",";
		file.close();
	}
}

void UpdateFile(account list[])
{
	ofstream file;
	file.open("accounts.csv", ios::out);
	if (file.fail())
		cout << "Issue With Writing To File - Get In Touch With IT Team" << endl;
	else
	{
		for (int i = 0; i < 1000; i++)
		{
			if (list[i].accType == "available")
				i = 1000;
			else
			{
				file << list[i].accType << ",";
				file << list[i].accNo << ",";
				file << list[i].accHolder << ",";
				file << list[i].sortCode << ",";
				file << list[i].overdraftStatus << ",";
				file << list[i].overdraftLimit << ",";
				file << list[i].initDeposit << ",";
				file << list[i].availBalance << ",";
				file << list[i].latestTxn << ",";
				file << list[i].status << ",";
			}
		}
		file.close();
		cout << "File Is Updated\n" << endl;
	}
}
