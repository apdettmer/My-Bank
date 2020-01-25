#include "BankAccountH.h"
#include <iostream>
BankAccount::BankAccount() {
	BankAccount::mBalance = 0;
	BankAccount::mAccNum = 1;
	BankAccount::mName = "";
}

BankAccount::~BankAccount() {
	//std::cout << "Look! A pointer was deleted" << std::endl;
}

BankAccount::BankAccount(int initialBalance) {
	BankAccount::mBalance = initialBalance;
	BankAccount::mAccNum = 1;
	BankAccount::mName = "";
}

BankAccount::BankAccount(int accountNumber, std::string customerName, int initialBalance) {
	BankAccount::mAccNum = accountNumber;
	BankAccount::mName = customerName;
	BankAccount::mBalance = initialBalance;
}

int BankAccount::getAccountNumber() {
	return BankAccount::mAccNum;
}

std::string BankAccount::getCustomerName() {
	return BankAccount::mName;
}

int BankAccount::getBalance() {
	return BankAccount::mBalance;
}

void BankAccount::setBalance(int newBalance) {
	BankAccount::mBalance = newBalance;
}

bool BankAccount::withdrawal(int amount) {
	if (amount <= BankAccount::mBalance && amount >= 0) {
		BankAccount::mBalance -= amount;
		return true;
	}
	return false;
}

void BankAccount::deposit(int amount) {
	BankAccount::mBalance += amount;
}