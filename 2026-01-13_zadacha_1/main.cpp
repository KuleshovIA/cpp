#include <iostream>

int main () {
	int array[] = {3, 6, 5, 9, 10};
	
	int lesser, bigger;
	lesser = array[0];
	bigger = array[0];
	
	for (int item : array) {
		if (item < lesser) {
			lesser = item;
		}
		if (item > bigger) {
			bigger = item;
		}
	}
	
	std::cout << "Массив:" << std::endl;
	for (int item : array) {
		std::cout << item << ' ';
	}
	std::cout << std::endl;
	std::cout << "Наибольшее значение:" << std::endl;
	std::cout << bigger << std::endl;
	std::cout << "Наименьшее значение:" << std::endl;
	std::cout << lesser << std::endl;
	std::cout << "Наибольшее значение больше наименьшего в " << (static_cast <double> (bigger)) / lesser << " раз" << std::endl;
}
