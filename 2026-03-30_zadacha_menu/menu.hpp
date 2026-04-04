#pragma once

namespace IBusko {
	struct Menu_item {
		const char* const title;
		const Menu_item* (*func) (const Menu_item* current);
		
		const Menu_item* const *children;
		const int children_count;
		
		const Menu_item* parent;
	};
}
