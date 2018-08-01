/* OOP345 Workshop 2
Name - Karan Shah
Student_Id: 129965166
Date - 28th Decemeber 2017*/

#pragma once
#include "Station.h"

namespace w2 {

	class Stations {
		char* file;
		int num_stations;
		Station* ptr;
	public:
		Stations(char*);
		~Stations();
		void update() const;
		void restock() const;
		void report() const;
	};

}
/*
public:
Stations(char* f) : file(f){
}
*/