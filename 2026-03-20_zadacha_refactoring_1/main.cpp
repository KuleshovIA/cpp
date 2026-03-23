#include <iostream>


float fill_array (float *array);


int main()
{
    float a[10], b[10], c[10];
    float average_a, average_b, average_c;
	
	std::cout << "Первая последовательность" << std::endl;
	average_a = fill_array (a);
    std::cout << "Среднее первой последовательности =" << average_a << std::endl;
	
    std::cout << "Вторая последовательность" << std::endl;
    average_b = fill_array (b);
    std::cout << "Среднее второй последовательности =" << average_b << std::endl;
	
    std::cout << "Третья последовательность" << std::endl;
    average_c = fill_array (c);
    std::cout << "Среднее третьей последовательности =" << average_c << std::endl;

    return 0;
}


float fill_array (float *array) {
	float sum; 
	for (int i = 0; i < 10; i++) {
		*(array + i) = std::rand() % 10;
		std::cout << *(array + i) << ' ';
		sum += *(array + i);
	}
	std::cout << std::endl;
	return sum / 10;
}
