#include <cstdlib>
#include <ctime>
#include <iostream>

int main () {
	int array_size;
	std::cin >> array_size;
	
	int *array = new int[array_size];
	
	srand(time(0));
	for (int i = 0; i < array_size; i++) {
		*(array + i) = std::rand();
	}
	
	for (int i = 0; i < array_size; i++) {
		std::cout << array[0 + i] << ' ';
	}
	std::cout << std::endl;
}
