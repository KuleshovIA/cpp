#pragma once

#include "menu.hpp"

namespace IBusko {
	const Menu_item* exit(const Menu_item* current);
	
	const Menu_item* show_menu(const Menu_item* current);
		
	const Menu_item* study_summ(const Menu_item* current);
	const Menu_item* study_substract(const Menu_item* current);
	const Menu_item* study_multiply(const Menu_item* current);
	const Menu_item* study_divide(const Menu_item* current);
	const Menu_item* study_go_back(const Menu_item* current);
}
