#include <ctime>
#include <iostream>


int main()
{
    int a[20], b;
	srand(time(0));
    for (int i = 0; i < 20; i++) {
        a[i] = std::rand() % 20;
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
	
    for (int i = 0; i < 10; i++) {
        b = a[i];
        a[i] = a[19 - i];
        a[19 - i] = b;
    }
	
    for (int i = 0; i < 20; i++) {
        std::cout << a[i] << ' ';
    }
	std::cout << std::endl;

    return 0;
}
