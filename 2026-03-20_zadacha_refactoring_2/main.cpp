#include <iostream>


int main()
{
    double a[10];
    for (int i = 0; i < 10; i++)
    {
        std::cout << "Введите " << i + 1 << " элемент" << std::endl;
        std::cin >> a[i];
    }
	
    int b = 1;
	for (int i = 0; i < 9; i++) {
		if (a[i] > a[i + 1]) {
			b = 0;
			break;
		}
	}
	
    if (b == 1) {
        std::cout << "Последовательность возрастающая";
        std::cout << std::endl;
    }
    else {
        std::cout << "Последовательность не возрастающая";
        std::cout << std::endl;
    }
    return 0;
}
