//
// CS2024 course project
// Andrew Dettmer -- apd67
//

#include "MenuH.h"
#include "MenuCommandH.h"
#include "MenuItemH.h"
#include "BankH.h"
#include "BankAccountH.h"
#include <iostream>
#include <fstream>
#include <functional>
using std::cout;
using std::endl;
using std::cin;
typedef map<int, int>::value_type insertPair;

void setBalance(shared_ptr<BankAccount> ba);
void withdrawal(shared_ptr<BankAccount> ba);
void deposit(shared_ptr<BankAccount> ba);

void printMyName();
void squareANumber();

int main(int argc, char* argv[]) {
	Bank bank;
	bank.readAccounts();
	std::map<int, int> orderInserted;
	MenuItem* accountMenuItems[] = { //inner menu item declarations
		new MenuCommand('1',"Balance Inquiry", [&bank]() -> bool {
			weak_ptr<BankAccount> ba = bank.getCurrentAccount();
			shared_ptr<BankAccount> bAcc = ba.lock();
			if (!bAcc) {
				cout << "No account selected" << endl;
				return true;
			}
			cout << "Balance is " << bAcc->getBalance() << endl;
			return true;
		}),
		new MenuCommand('2',"Deposit", [&bank]() -> bool {
			weak_ptr<BankAccount> ba = bank.getCurrentAccount();
			shared_ptr<BankAccount> bAcc = ba.lock();
			if (!bAcc) {
				cout << "No account selected" << endl;
				return true;
			}
			deposit(bAcc);
			bank.updateAccount(bAcc);
			return true;
		}),
		new MenuCommand('3',"Withdrawal", [&bank]() -> bool {
			weak_ptr<BankAccount> ba = bank.getCurrentAccount();
			shared_ptr<BankAccount> bAcc = ba.lock();
			if (!bAcc)
				cout << "No account selected" << endl;
			else {
				withdrawal(bAcc);
				bank.updateAccount(bAcc);
			}
			return true;
		}),
		new MenuCommand('b',"Back", []() {return false;}) }; //simple lambda for exit command
	Menu accountMenu(accountMenuItems, 4, '5', "Account");
	MenuItem* mainItems[] = {
		new MenuCommand('1', "List Accounts", [&bank]()-> bool {
			bank.listAccounts();
			return true;}),
		new MenuCommand('2', "New Account", [&bank]()-> bool {
			bank.newAccount();
			return true;}),
		new MenuCommand('3', "Select Account", [&bank]()-> bool {
			bank.selectAccount();
			return true;}),
		new MenuCommand('4', "Show Active Account", [&bank]()-> bool {
			weak_ptr<BankAccount> ba = bank.getCurrentAccount();
			shared_ptr<BankAccount> bAcc = ba.lock();
			if (!bAcc)
				cout << "No account selected" << endl;
			else
				cout << "Selected Account Number: " << bAcc->getAccountNumber() << endl;
			return true;
			}),
		&accountMenu,
		new MenuCommand('b', "Quit", []() {return false;}) }; //simple -- exits
	Menu mainMenu(mainItems, 6, 'a', "Main");
	mainMenu.select();
	cout << "Done" << endl;
	return 0;
}

//prints name 3 times
void printMyName() {
	for (int i = 3; i > 0; i--) {
		cout << "Andrew" << endl;
	}
}

//takes inputted integer and computes its square
void squareANumber() {
	cout << "Enter a Number> ";
	int n;
	cin >> n;
	cout << n * n << endl;
}


//prompts user for new balance amount
void setBalance(shared_ptr<BankAccount> ba) {
	cout << "Please enter your new balance>" << endl;
	int x;
	cin >> x;
	if (x < 0)
		cout << "Error: please enter a positive amount" << endl;
	else
		ba->setBalance(x);
}

//prompts user for withdrawal amount
void withdrawal(shared_ptr<BankAccount> ba) {
	cout << "Withdrawal" << endl;
	cout << "Please enter the amount you would like to withdraw: ";
	int x;
	cin >> x;
	bool b = ba->withdrawal(x);
	if (!b)
		cout << "Error: amount requested was invalid or greater than current balance"
		<< endl;
	else
		cout << "Withdrawal successful" << endl;
}

void deposit(shared_ptr<BankAccount> ba) {
	cout << "Deposit" << endl;
	cout << "Please enter the amount you would like to deposit: ";
	int x;
	cin >> x;
	if (x < 0)
		cout << "Error: please enter a non-negative value" << endl;
	else
		ba->deposit(x);
}

