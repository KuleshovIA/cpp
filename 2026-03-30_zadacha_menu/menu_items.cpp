#include "menu_items.hpp"

#include <cstddef>

#include "menu_functions.hpp"

const IBusko::Menu_item IBusko::STUDY_SUMM = {
	"1 — хочу научиться складывать!", IBusko::study_summ, nullptr, 0, &IBusko::STUDY
};
const IBusko::Menu_item IBusko::STUDY_SUBSTRACT = {
	"2 — хочу научиться вычитать", IBusko::study_substract, nullptr, 0, &IBusko::STUDY
};
const IBusko::Menu_item IBusko::STUDY_MULTIPLY = {
	"3 — хочу научиться умножать", IBusko::study_multiply, nullptr, 0, &IBusko::STUDY
};
const IBusko::Menu_item IBusko::STUDY_DIVIDE = {
	"4 — хочу научиться делить", IBusko::study_divide, nullptr, 0, &IBusko::STUDY
};
const IBusko::Menu_item IBusko::STUDY_GO_BACK = {
	"0 — Выйти в главное меню", IBusko::study_go_back, nullptr, 0, &IBusko::STUDY
};

namespace {
	const IBusko::Menu_item* const study_children[] = {
		&IBusko::STUDY_GO_BACK,
		&IBusko::STUDY_SUMM,
		&IBusko::STUDY_SUBSTRACT,
		&IBusko::STUDY_MULTIPLY,
		&IBusko::STUDY_DIVIDE,
	};
	const int study_size =  sizeof(study_children) / sizeof(study_children[0]);	
}

const IBusko::Menu_item IBusko::STUDY = {
	"1 — хочу учиться", IBusko::show_menu, study_children, study_size, &IBusko::MAIN
};
const IBusko::Menu_item IBusko::EXIT = {
	"0 — Не хочу учиться", IBusko::exit, nullptr, 0, &IBusko::MAIN
};

namespace {
	const IBusko::Menu_item* const main_children[] = {
		&IBusko::EXIT,
		&IBusko::STUDY
	};
	const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const IBusko::Menu_item IBusko::MAIN = {
	nullptr, IBusko::show_menu, main_children, main_size, nullptr
};