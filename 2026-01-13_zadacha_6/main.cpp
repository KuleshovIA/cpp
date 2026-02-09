#include <iostream>
#include <string>

int main () {
	int number_of_array_elements;
	std::cin >> number_of_array_elements;
	
	int *array = new int[number_of_array_elements];
	
	std::string str;
	std::getline(std::cin, str);
	std::cout << str << std::endl;
	
	/*
	for (int i = 0; i < number_of_array_elements; i++) {
		for (int j = 0; j < str.length(); j++) {
			std::cout << "!";
		}
		//*array + i = 
	}
	
	
	/*
	for (int i = 0; i < number_of_array_elements; i++) {
		std::cout << *array + i << ' ';
	}
	std::cout << std::endl; 
	*/
}
