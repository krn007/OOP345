/* OOP345 Workshop 7
Name - Karan Shah
Student_Id: 129965166
Date - 28th Decemeber 2017*/

#include <iostream>
#include <string>
#include "Sale.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << argv[0] << ": incorrect number of arguments\n";
		std::cerr << "Usage: " << argv[0] << " file_name\n";
		return 1;
	}

	w7::Sale sale(argv[1]);
	sale.display(std::cout);

	std::cout << "\nPress any key to continue ... ";
	std::cin.get();
}

