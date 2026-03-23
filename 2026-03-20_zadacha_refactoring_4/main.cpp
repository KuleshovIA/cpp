#include <iostream>
#include <cmath>



int main() {
	double angle, s1, s2;
	
	std::cout << "Введите угол:" << std::endl;
	std::cin >> angle;
	
	if (cos(2 * angle) != 1) {
		s1 = (1 + sin(2 * angle)) / (1 - cos(2 * angle));
		std::cout << "F(x1)=" << s1 << std::endl;
	}
	else if (cos(2 * angle) == 1) {
		std::cout <<"Неверный ввод для F(x1) " << std::endl;
	}
	
	if (tan(angle) != 1) {
		s2 = (1 + tan(angle) * tan(angle)) / (1 - tan(angle) * tan(angle));
		std::cout << "F(X2)=" << s2 << std::endl;
	}
	else if (tan(angle) == 1) {
		std::cout << "Неверный ввод для F(x2) " << std::endl;
	}
	
	return 0;
}
