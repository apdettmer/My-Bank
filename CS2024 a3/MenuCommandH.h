#pragma once
#include "MenuItemH.h"
#include <functional>

class MenuCommand : public MenuItem
{
private:
	std::function<bool()> mFunc; //member function pointer to be used in select
public:
	bool select(); //returns false if title is "Quit" or "Back," otherwise true
	void display(); //echoes the title of the command
	std::string getTitle(); //gives the title of the command
	MenuCommand(char c, std::string title, std::function<bool()> f);
	using MenuItem::MenuItem;
};
