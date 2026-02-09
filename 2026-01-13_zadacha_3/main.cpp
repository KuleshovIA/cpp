#include <iostream>

int main() {
	std::cout << "Введите номер дня недели:" << std::endl;
	
	int number_of_day;
	std::cin >> number_of_day;
	
	switch (number_of_day) {
		case 1:
			std::cout << "Понедельник" << std::endl;
			break;
		case 2:
			std::cout << "Вторник" << std::endl;
			break;
		case 3:
			std::cout << "Среда" << std::endl;
			break;
		case 4:
			std::cout << "Четверг" << std::endl;
			break;
		case 5:
			std::cout << "Пятница" << std::endl;
			break;
		case 6:
			std::cout << "Суббота" << std::endl;
			break;
		case 7:
			std::cout << "Воскресенье" << std::endl;
			break;
		default:
			std::cout << "Неверный день недели, повторите попытку!" << std::endl;
	}
	
}
