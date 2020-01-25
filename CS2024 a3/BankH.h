#pragma once
#include <map>
#include "BankAccountH.h"
#include <fstream>
using namespace std;
class Bank
{
public:
	~Bank();
	void newAccount();
	void listAccounts(); //lists the number, name, and balance associated with each account
	void selectAccount(); //adjusts current account to one selected by user
	void addAccount(int num, std::string name, int balance);
	weak_ptr<BankAccount> getCurrentAccount() { return mCurrentAccount;  }
	void readAccounts(); //creates bank accounts for previously written data
	void updateAccount(shared_ptr<BankAccount> ba); //updates the information of the current account in the data file
	void appendAccount(shared_ptr<BankAccount> ba); //adds data for a new account to the data file
private:
	std::map<int, shared_ptr<BankAccount>> mAccounts; //map of key:account number, value: account pairings
	std::map<int, int> order; //maps account numbers to when they were added, for use in file manipulation
	weak_ptr<BankAccount> mCurrentAccount; //the account currently selected by the user
	void cleanUp();
	fstream mFile;
};
