#include <iostream>
#include <windows.h>

#include "menu.hpp"
#include "menu_functions.hpp"
#include "menu_items.hpp"

int main () {
	SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
	//std::setlocale (LC_ALL, "");
	
	const IBusko::Menu_item* current = &IBusko::MAIN;
	
	do {		
		current = current->func(current);
	} while (true);
	
	return 0;
}
