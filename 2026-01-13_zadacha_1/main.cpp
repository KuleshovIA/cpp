#include <iostream>

int main () {
	int array[] = {3, 6, 5, 9, 10};
	
	float lesser, bigger;
	lesser = array[0];
	bigger = array[0];
	
	for (int i : array) {
		if (i < lesser) {
			lesser = i;
		}
		if (i > bigger) {
			bigger = i;
		}
	}
	
	std::cout << "Массив:" << std::endl;
	for (int i : array) {
		std::cout << i << ' ';
	}
	std::cout << std::endl;
	std::cout << "Наибольшее значение:" << std::endl;
	std::cout << bigger << std::endl;
	std::cout << "Наименьшее значение:" << std::endl;
	std::cout << lesser << std::endl;
	std::cout << "Наибольшее значение больше наименьшего в " << bigger/lesser << " раз" << std::endl;
}
