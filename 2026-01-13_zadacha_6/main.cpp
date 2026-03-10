#include <iostream>
#include <string>

int main () {
	int number_of_array_elements;
	std::cin >> number_of_array_elements;
	//std::cin.ignore();
	
	int *array = new int[number_of_array_elements];
	
	for (int i = 0; i < number_of_array_elements; i++) {
		std::cin >> array[i];
	}
	
	for (int i = number_of_array_elements-1; i >= 0; i--) {
		std::cout << array[i] << " ";
	}
	
}
