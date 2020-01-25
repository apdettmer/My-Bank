#include "BankH.h"
#include "BankAccountH.h"
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;
typedef map<int, shared_ptr<BankAccount>>::value_type IntAccountPair;
typedef map<int, shared_ptr<BankAccount>>::iterator AccountIterator;
typedef map<int, int>::value_type insertPair;
typedef map<int, int>::iterator InsertIterator;

Bank::~Bank() {
	cleanUp();
}

void Bank::newAccount() {
	cout << "NEW ACCOUNT:" << endl;
	int accNum;
	cout << "ENTER ACCOUNT NUMBER: ";
	cin >> accNum;
	std::string accName;
	cout << "ENTER ACCOUNT NAME: ";
	cin.ignore();
	getline(cin, accName);
	int initBal = -1;
	cout << "ENTER OPENING BALANCE: ";
	cin >> initBal;
	while (initBal < 0) {
		cout << "ERROR -- PLEASE ENTER A NON-NEGATIVE BALANCE: ";
		cin >> initBal;
	}
	shared_ptr<BankAccount> bAcc(new BankAccount(accNum, accName, initBal));
	if (bAcc == NULL) {
		cout << "Could not allocate pointer";
		return;
	}
	IntAccountPair ia(accNum, bAcc);
	Bank::mAccounts.insert(ia);
	insertPair p(accNum, Bank::order.size());
	Bank::order.insert(p);
	Bank::mCurrentAccount = bAcc;
	appendAccount(bAcc);
}

void Bank::addAccount(int num, std::string name, int balance) {
	BankAccount* bAcc = new BankAccount(num, name, balance);
	IntAccountPair ia(num, bAcc);
	Bank::mAccounts.insert(ia);
}

void Bank::selectAccount() {
	if (Bank::mAccounts.size() == 0) {
		cout << "No accounts available. Please add an account." << endl;
		return;
	}
	cout << "Enter an account number to select: ";
	int k;
	cin >> k;
	AccountIterator ba = Bank::mAccounts.find(k);
	if (ba == Bank::mAccounts.end()) {
		cout << "Number does not match any accounts" << endl;
		return;
	}
	Bank::mCurrentAccount = ba->second;
}

void Bank::listAccounts() {
	cout << "ACCT# : NAME : BALANCE" << endl;
	for (AccountIterator ba = Bank::mAccounts.begin(); ba != Bank::mAccounts.end(); ba++) {
		cout << (ba->second)->getAccountNumber() << " : " << (ba->second)->getCustomerName() << " : "
			<< (ba->second)->getBalance() << endl;
	}
}

void Bank::readAccounts() {
	Bank::mFile.open("bank.dat", ios::app);
	if (!Bank::mFile) {
		cout << "An error occurred trying to open the file." << endl;
		return;
	}
	else
		Bank::mFile.close();
	Bank::mFile.open("bank.dat", ios::in);
	char buffer[80];
	while (!Bank::mFile.eof()) {
		Bank::mFile.getline(buffer, 80);
		if (Bank::mFile.eof()) break; //empty file or eof
		int accNum;
		accNum = atoi(buffer);
		Bank::mFile.getline(buffer, 80);
		string name(buffer);
		Bank::mFile.getline(buffer, 80);
		int bal;
		bal = atoi(buffer);
		addAccount(accNum, name, bal);
		insertPair p(accNum, Bank::order.size());
		Bank::order.insert(p);
	}
	Bank::mFile.clear();
	Bank::mFile.close();
}

void Bank::updateAccount(shared_ptr<BankAccount> ba) {
	int accNum = ba->getAccountNumber();
	Bank::mFile.open("bank.dat", ios::in | ios::out);
	if (!Bank::mFile) {
		cout << "Error opening file" << endl;
		return;
	}
	else {
		InsertIterator it = Bank::order.find(accNum);
		int offset = it->second;
		Bank::mFile.seekp(offset*28); //confused on this -- newlines seem to not be included in the width, so 28 instead of 25
		if (Bank::mFile.eof()) { //should not happen
			cout << "Error: account not in record" << endl;
			return;
		}
		Bank::mFile << std::left << std::setfill('\0');
		Bank::mFile << std::setw(5) << ba->getAccountNumber() << "\n";
		Bank::mFile << std::setw(10) << ba->getCustomerName() << "\n";
		Bank::mFile << std::setw(7) << ba->getBalance() << "\n";
	}
	Bank::mFile.close();
}

void Bank::appendAccount(shared_ptr<BankAccount> ba) {
	Bank::mFile.open("bank.dat", ios::app);
	if (!Bank::mFile) {
		cout << "Error opening file" << endl;
		return;
	}
	else {
		Bank::mFile << std::left << std::setfill('\0') << std::setw(5);
		Bank::mFile << ba->getAccountNumber() << "\n";
		Bank::mFile << std::setw(10) << ba->getCustomerName() << "\n";
		Bank::mFile << std::setw(7) << ba->getBalance() << "\n";
	}
	Bank::mFile.clear();
	Bank::mFile.close();
}

void Bank::cleanUp() {
	Bank::mAccounts.clear();
}
