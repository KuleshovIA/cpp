#include <iostream>

int sum_of_two_numbers (int a, int b);

int main () {
	std::cout << "Введите два числа (каждое на отдельной строке), чтобы узнать их сумму:" << std::endl;
	
	int first_number;
	int second_number;
	
	std::cin >> first_number;
	std::cin >> second_number;
	
	std::cout <<  "Сумма чисел равна " ;
	std::cout << sum_of_two_numbers (first_number, second_number) << std::endl;
}

int sum_of_two_numbers (int a, int b) {
	return (a+b);
}
