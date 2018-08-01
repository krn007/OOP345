/* OOP345 Workshop 5
Name - Karan Shah
Student_Id: 129965166
Date - 28th Decemeber 2017*/

#include "Message.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace w5;


Message::Message() {
	user = '\n';
	tweet = '\n';
	reply = '\n';
}


Message::Message(std::ifstream& in, char c) {
	std::string line;
	getline(in, line, '\n');
	//std::cout << "we here" << std::endl;
	auto cr = line.find('\r');
	if (cr != std::string::npos) {
		line.erase(cr);
	}
	std::cout << "line -->" << line << "<--\n";

	size_t i = 0;
	while (i < line.size() && line[i] != ' ') {
		user += line[i];
		i++;
	}
	i++;

	std::cout << "user" << user << "\n";
	if (i < line.size() && line[i] == '@') {
		i++;

		while (i < line.size() && line[i] != ' ') {
			reply += line[i];
			i++;
		}
		i++;
		std::cout << "reply=" << reply << "\n";
	}
	while (i < line.size()) {
		tweet += line[i];
		i++;
	}

}
bool Message::empty() const {
	return tweet.empty();
}

void Message::display(std::ostream& os) const {
	os << "User :" << user << "\n";

	if (!reply.empty()) {
		os << "Reply:" << reply << "\n";
	}

	os << "Tweet : " << tweet << "\n";
}