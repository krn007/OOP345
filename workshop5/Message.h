/* OOP345 Workshop 5
Name - Karan Shah
Student_Id: 129965166
Date - 28th Decemeber 2017*/

#pragma once
#include <iostream>

namespace w5 {

	class Message {
		std::string user, tweet, reply;
	public:
		Message();
		Message(std::ifstream& in, char c);
		bool empty() const;
		void display(std::ostream&) const;
	};

}