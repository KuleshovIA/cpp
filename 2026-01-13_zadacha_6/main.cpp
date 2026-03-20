#include <iostream>
#include <string>

int main () {
	int array_size;
	std::cin >> array_size;
	//std::cin.ignore();
	
	int *array = new int[array_size];
	
	for (int i = 0; i < array_size; i++) {
		std::cin >> array[i];
	}
	
	for (int i = array_size - 1; i >= 0; i--) {
		std::cout << array[i] << ' ';
	}
	
}
