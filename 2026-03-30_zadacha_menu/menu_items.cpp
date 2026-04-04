#include "menu_items.hpp"

#include <cstddef>

#include "menu_functions.hpp"

const IBusko::Menu_item IBusko::ALGEBRA_SUMM = {
	"1 — Хочу научиться складывать", IBusko::algebra_summ, nullptr, 0, &IBusko::STUDY_ALGEBRA
};
const IBusko::Menu_item IBusko::ALGEBRA_SUBSTRACT = {
	"2 — Хочу научиться вычитать", IBusko::algebra_substract, nullptr, 0, &IBusko::STUDY_ALGEBRA
};
const IBusko::Menu_item IBusko::ALGEBRA_MULTIPLY = {
	"3 — Хочу научиться умножать", IBusko::algebra_multiply, nullptr, 0, &IBusko::STUDY_ALGEBRA
};
const IBusko::Menu_item IBusko::ALGEBRA_DIVIDE = {
	"4 — Хочу научиться делить", IBusko::algebra_divide, nullptr, 0, &IBusko::STUDY_ALGEBRA
};
const IBusko::Menu_item IBusko::ALGEBRA_GO_SUBJECTS = {
	"0 — Вернуться к предметам", IBusko::go_back, nullptr, 0, &IBusko::STUDY_ALGEBRA
};

namespace {
	const IBusko::Menu_item* const algebra_children[] = {
		&IBusko::ALGEBRA_GO_SUBJECTS,
		&IBusko::ALGEBRA_SUMM,
		&IBusko::ALGEBRA_SUBSTRACT,
		&IBusko::ALGEBRA_MULTIPLY,
		&IBusko::ALGEBRA_DIVIDE
	};
	const int algebra_size = sizeof(algebra_children) / sizeof(algebra_children[0]);
}


const IBusko::Menu_item IBusko::ANALYSIS_DIFFCALC = {
	"1 — Хочу изучать дифференциальное исчисление", IBusko::analysis_diffcalc, nullptr, 0, &IBusko::STUDY_ANALYSIS
};
const IBusko::Menu_item IBusko::ANALYSIS_INTECALC = {
	"2 — Хочу изучать интегральное исчисление", IBusko::analysis_intecalc, nullptr, 0, &IBusko::STUDY_ANALYSIS
};
const IBusko::Menu_item IBusko::ANALYSIS_GO_SUBJECTS = {
	"0 — Вернуться к предметам", IBusko::go_back, nullptr, 0, &IBusko::STUDY_ANALYSIS
};

namespace {
	const IBusko::Menu_item* const analysis_children[] = {
		&IBusko::ANALYSIS_GO_SUBJECTS,
		&IBusko::ANALYSIS_DIFFCALC,
		&IBusko::ANALYSIS_INTECALC
	};
	const int analysis_size = sizeof(analysis_children) / sizeof(analysis_children[0]);
}


const IBusko::Menu_item IBusko::STUDY_ALGEBRA = {
	"1 — Хочу изучать алгебру!", IBusko::show_menu, algebra_children, algebra_size, &IBusko::STUDY
};
const IBusko::Menu_item IBusko::STUDY_ANALYSIS = {
	"2 — Хочу изучать мат. анализ!", IBusko::show_menu, analysis_children, analysis_size, &IBusko::STUDY
};
const IBusko::Menu_item IBusko::STUDY_GO_BACK = {
	"0 — Выйти в главное меню", IBusko::go_back, nullptr, 0, &IBusko::STUDY
};

namespace {
	const IBusko::Menu_item* const study_children[] = {
		&IBusko::STUDY_GO_BACK,
		&IBusko::STUDY_ALGEBRA,
		&IBusko::STUDY_ANALYSIS,
	};
	const int study_size = sizeof(study_children) / sizeof(study_children[0]);	
}

const IBusko::Menu_item IBusko::STUDY = {
	"1 — Хочу учиться", IBusko::show_menu, study_children, study_size, &IBusko::MAIN
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