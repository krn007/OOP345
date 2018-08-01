/* OOP345 Workshop 2
Name - Karan Shah
Student_Id: 129965166
Date - 28th Decemeber 2017*/

#pragma once
#include <iostream>
#include <string>

using namespace std;

enum PassType { adult, student };

class Station {
	string station_name;
	unsigned s_pass;
	unsigned a_pass;
public:
	Station() : station_name(""), s_pass(0), a_pass(0) {}
	void set(const std::string&, unsigned, unsigned);
	void update(PassType, int);
	unsigned inStock(PassType) const;
	const std::string& getName() const;
};