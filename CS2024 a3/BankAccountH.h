#pragma once
#include <string>
class BankAccount {
public:
	BankAccount();
	~BankAccount();
	BankAccount(int initialBalance);
	BankAccount(int accountNumber, std::string customerName, int initialBalance);

	int getBalance();
	std::string getCustomerName();
	int getAccountNumber();
	void setBalance(int newBalance);
	bool withdrawal(int amount);
	void deposit(int amount);

private:
	std::string mName;
	int mBalance;
	int mAccNum;
};