#pragma once

#include "menu.hpp"

namespace IBusko {
	const Menu_item* exit (const Menu_item* current);
	
	const Menu_item* show_menu (const Menu_item* current);
		
	//const Menu_item* study_algebra(const Menu_item* current);
	//const Menu_item* study_analysis(const Menu_item* current);
	//const Menu_item* study_multiply(const Menu_item* current);
	//const Menu_item* study_divide(const Menu_item* current);
	const Menu_item* go_back (const Menu_item* current);
	
	const Menu_item* algebra_summ (const Menu_item* current);
	const Menu_item* algebra_substract (const Menu_item* current);
	const Menu_item* algebra_multiply (const Menu_item* current);
	const Menu_item* algebra_divide (const Menu_item* current);
	
	const Menu_item* analysis_diffcalc (const Menu_item* current);
	const Menu_item* analysis_intecalc (const Menu_item* current);
}
