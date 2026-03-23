#include <iostream>
#include <cmath>


int main() { 
	int d, s, m, g, y, c;
	
	std::cout << "Введите дату дня:" << std::endl;
	std::cin >> d;
	std::cout << "Введите число месяца:" << std::endl;
	std::cin >> m;
	std::cout << "Введите год:" << std::endl;
	std::cin >> g;
	
	y = g % 100;
	c = g / 100;
	s = (d + (13 * m - 1) / 5 + y / 4 + c / 4 - 2 * c + 777) % 7;
	
	if (s == 0)
		std::cout << "Воскресенье" << std::endl;
	else if (s == 1)
		std::cout << "Понедельник" << std::endl;
	else if (s == 2)
		std::cout << "Вторник" << std::endl;
	else if (s == 3)
		std::cout << "Среда" << std::endl;
	else if (s == 4)
		std::cout << "Четверг" << std::endl;
	else if (s == 5)
		std::cout << "Пятница" << std::endl;
	else if (s == 6)
		std::cout << "Суббота" << std::endl;

	return 0;
}
