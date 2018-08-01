/* OOP345 Workshop 2
Name - Karan Shah
Student_Id: 129965166
Date - 28th Decemeber 2017*/

#include <iostream>
#include "Stations.h"

int main(int argc, char* argv[]) {
	std::cout << "\nCommand Line : ";
	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << ' ';
	}
	std::cout << std::endl;
	if (argc != 2) {
		std::cerr << "\nIncorrect number of arguments\n";
		return 1;
	}
	w2::Stations stations(argv[1]);
	stations.update();
	stations.restock();
	stations.report();
	return 0;
}
