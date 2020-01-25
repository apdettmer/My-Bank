#pragma once
#include <string>
#include <iostream>
class MenuItem {
public:   
	MenuItem(char c, std::string title){
		mCommandCharacter = c;
		mTitle = title;
	};
	virtual bool select() = 0;   
	virtual void display() = 0;
	char getCommandChar() { return mCommandCharacter; }
	virtual std::string getTitle() = 0;
protected:   
	char mCommandCharacter;   
	std::string mTitle;
};
