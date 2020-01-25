#include "MenuCommandH.h"
#include <iostream>
#include <functional>
using std::cout;
using std::endl;

std::string MenuCommand::getTitle() {
	return MenuCommand::mTitle;
}

void MenuCommand::display() {
	cout << MenuCommand::getCommandChar() << "> "
		<< MenuCommand::getTitle() << endl;
}

bool MenuCommand::select() {
	if (MenuCommand::mFunc == NULL) {
		cout << "Menu Command: " << MenuCommand::mTitle
			<< " is not yet implemented yet!!!" << endl;
		return true;
	}
	return MenuCommand::mFunc();
}

MenuCommand::MenuCommand(char c, std::string title, std::function<bool()> f) : MenuItem(c, title) {
	MenuCommand::mFunc = f;
}
