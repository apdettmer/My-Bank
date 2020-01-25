#include "MenuH.h"
#include "MenuItemH.h"
#include "iostream"

using std::cout;
using std::cin;
using std::endl;

Menu::Menu(MenuItem* items[], int size, char cmd, std::string title) : MenuItem(cmd, title) {
	for (int i = 0; i < size; i++) {
		Menu::items.push_back(items[i]);
	}
}

std::string Menu::getTitle() {
	return Menu::mTitle + "> ";
}

bool Menu::select() {
	char cInput;
	bool promptState = true;
	while (promptState) {
		cout << "====" << Menu::mTitle << " MENU====" << endl;
		for (MenuItem* mItem : Menu::items) {
			cout << mItem->getCommandChar() << "> " << mItem->getTitle() << endl;
		}
		cInput = promptUser();
		int cntr = 0;
		for (MenuItem* item : Menu::items) {
			if (cInput == item->getCommandChar()) {
				promptState = item->select();
				break;
			}
			cntr++;
		}
		if (cntr == Menu::items.size())
			cout << "Invalid selection" << endl;
	}
	return true;
}

void Menu::display() {
	cout << Menu::getCommandChar() << "> " << Menu::getTitle()
		<< ">" << endl;
}

char Menu::promptUser() {
	char c;
	cout << "Enter choice> ";
	cin >> c;
	return c;
}