#pragma once
#include "MenuItemH.h"
#include <vector>
#include <iostream>

class Menu : public MenuItem
{
private:
	std::vector<MenuItem*> items; //maintains all menu items for the menu display
public:
	Menu(MenuItem* items[], int size, char cmd, std::string title);
	bool select(); //for menu, select displays the contents of the menu
	void display(); //displays the titles of all menu items in the menu
	char promptUser(); //prompts user for char input
	std::string getTitle(); //gives the title of the menu with >
};

