/* OOP345 Workshop 2
Name - Karan Shah
Student_Id: 129965166
Date - 28th Decemeber 2017*/
#include <cstdlib>
#include "Stations.h"
#include "Station.h"
#include <fstream>
#include <iostream>
#include <iomanip>

w2::Stations::~Stations() {
	PassType type1, type2;
	type1 = student;
	type2 = adult;
	std::fstream newfile("output.txt", std::ios::out);
	newfile << num_stations << ";" << endl;
	for (int i = 0; i < num_stations; i++) {
		newfile << ptr[i].Station::getName() << ";" << ptr[i].Station::inStock(type1) << " " << ptr[i].Station::inStock(type2) << endl;
	}

	newfile.close();
	delete[] ptr;
}

w2::Stations::Stations(char* input) {

	int stations = 0;

	std::fstream myfile(input);

	if (!myfile.is_open()) {
		std::cout << "File is not found" << std::endl;
		myfile.clear();
		myfile.close();
		exit(1);
	}
	else {

		myfile >> stations;
		num_stations = stations;
		myfile.ignore(1, ';');
		myfile.ignore(1, ' ');

		ptr = new Station[stations];

		char station_name[40];
		int adultpass;
		int studentpass;
		int count = 0;

		while (true) {
			myfile.getline(station_name, 40, ';');

			myfile >> studentpass;
			myfile >> adultpass;
			myfile.ignore(1, ' ');
			ptr[count].set(station_name, adultpass, studentpass);
			count++;
			if (myfile.eof()) break;
		}

	}

};

void w2::Stations::update() const {
	int s_passes = 0;
	int a_passes = 0;
	PassType type1, type2;
	type1 = student;
	type2 = adult;
	cout << endl;
	cout << "Passes Sold : " << endl;
	cout << "--------------" << endl;
	for (int i = 0; i < num_stations; i++) {
		cout << ptr[i].getName() << endl;
		cout << " Student Passes sold : ";
		cin >> s_passes;
		s_passes *= -1;
		ptr[i].update(type1, s_passes);
		cout << " Adult   Passes sold : ";
		cin >> a_passes;
		a_passes *= -1;
		ptr[i].update(type2, a_passes);
	};

};

void w2::Stations::restock() const {
	int s_passes = 0;
	int a_passes = 0;
	PassType type1, type2;
	type1 = student;
	type2 = adult;

	cout << endl;
	cout << "Passes added : " << endl;
	cout << "---------------" << endl;
	for (int i = 0; i < num_stations; i++) {
		cout << ptr[i].Station::getName() << endl;
		cout << " Student Passes sold : ";
		cin >> s_passes;
		ptr[i].update(type1, s_passes);
		cout << " Adult   Passes sold : ";
		cin >> a_passes;
		ptr[i].update(type2, a_passes);
	}
};

void w2::Stations::report() const {
	PassType type1, type2;
	type1 = student;
	type2 = adult;
	cout << endl;

	cout << "Passes in Stock : Student Adult" << endl;
	cout << "-------------------------------" << endl;
	for (int i = 0; i < num_stations; i++) {
		cout << setw(18) << left << ptr[i].Station::getName()
			<< setw(10)
			<< ptr[i].Station::inStock(type1)
			<< setw(4)
			<< ptr[i].Station::inStock(type2)
			<< endl;
	}
};
