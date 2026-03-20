#include <iostream>

int sum (int a, int b);

int main () {
	std::cout << "Введите два числа (каждое на отдельной строке), чтобы узнать их сумму:" << std::endl;
	
	int first_number;
	int second_number;
	
	std::cin >> first_number;
	std::cin >> second_number;
	
	std::cout <<  "Сумма чисел равна " ;
	std::cout << sum (first_number, second_number) << std::endl;
}

int sum (const int a, const int b) {
	return a+b;
}
