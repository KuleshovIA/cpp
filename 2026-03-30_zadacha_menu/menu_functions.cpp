#include "menu_functions.hpp"
#include "menu.hpp"
#include <cstdlib>
#include <iostream>

const IBusko::Menu_item* IBusko::exit (const Menu_item* current) {
	std::exit (0);
}

const IBusko::Menu_item* IBusko::show_menu (const Menu_item* current) {
	std::cout << "Обучайка приветствует вас." << std::endl;
	for (int i = 1; i < current->children_count; i++) {
		std::cout << current->children[i]->title << std::endl;
	}
	std::cout << current->children[0]->title << std::endl;
	std::cout << "Обучайка > ";
	
	int user_input;
	std::cin >> user_input;
	std::cout << std::endl;
	
	return current->children[user_input];
}

const IBusko::Menu_item* IBusko::study_summ(const Menu_item* current) {
	std::cout << current->title << std::endl;
	return current->parent;
}

const IBusko::Menu_item* IBusko::study_substract(const Menu_item* current) {
	std::cout << current->title << std::endl;
	return current->parent;
}

const IBusko::Menu_item* IBusko::study_multiply(const Menu_item* current) {
	std::cout << current->title << std::endl;
	return current->parent;
}

const IBusko::Menu_item* IBusko::study_divide(const Menu_item* current) {
	std::cout << current->title << std::endl;
	return current->parent;
}

const IBusko::Menu_item* IBusko::study_go_back(const Menu_item* current) {
	std::cout << current->title << std::endl;
	return current->parent->parent;
}
