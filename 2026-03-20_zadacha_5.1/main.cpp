#include <iostream>

int main() {
	std::cout << "Введите номер дня недели:" << std::endl;
	
	int day_number;
	std::cin >> day_number;
	
	char array[84] = {"Понедельник Вторник     Среда       Четверг     Пятница     Суббота     Воскресенье"};
	
	if (0 < day_number < 8) {
		for (int i = (day_number - 1) * 12; i<83; i++) {
			if (array[i] == ' ' && array[i + 1] != ' ') {
				std::cout << std::endl;
			}
			else if (array[i] == ' ') {
				i++;
			}
			else {
				std::cout << array[i];
			}
		}
	}
	else {
		std::cout << "Неверный день недели, повторите попытку!" << std::endl;
	}
	std::cout << std::endl;
}
