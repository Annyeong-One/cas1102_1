#include<iostream>
#include "math.h"

int main() {
	int x, y, z;
	std::cin >> x >> y >> z;
	std::cout << add(x, y) << std::endl;
	std::cout << add(x, y, z) << std::endl;
	std::cout << add(1.5, 2.3) << std::endl;
	std::cout << multiply(x, y) << std::endl;
}