#include <cstdlib>
#include <ctime>
#include <iostream>

int main () {
	int number_of_array_elements;
	std::cin >> number_of_array_elements;
	
	int *array = new int[number_of_array_elements];
	
	for (int i = 0; i < number_of_array_elements; i++) {
		srand(time(0));
		*(array + i) = std::rand();
	}
	
	for (int i = 0; i < number_of_array_elements; i++) {
		std::cout << *array + i << ' ';
	}
	std::cout << std::endl;
}
