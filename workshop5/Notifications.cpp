/* OOP345 Workshop 5
Name - Karan Shah
Student_Id: 129965166
Date - 28th Decemeber 2017*/

#include "Notifications.h"

using namespace w5;

Notifications::Notifications() {
	capacity = 10;
	messageTable = new Message[capacity];
	count = 0;
}

Notifications::Notifications(const Notifications& obj) {
	capacity = 10;
	messageTable = new Message[capacity];
	count = 0;
	count = obj.count;
	for (size_t i; i < count; i++) {
		messageTable[i] = obj.messageTable[i];
	}
}

Notifications& Notifications::operator=(const Notifications& obj) {
	capacity = 10;
	if (this != &obj) {
		if (count == 0 && obj.count == 0) {

		}
		else if (count == 0 && obj.count != 0) {
			messageTable = new Message[capacity];
			count = obj.count;
			for (size_t i = 0; i < count; i++) {
				messageTable[i] = obj.messageTable[i];
			}
		}
		else if (count != 0 && obj.count == 0) {
			delete[] messageTable;
			messageTable = nullptr;
			count = 0;
		}
		else if (count != 0 && obj.count != 0) {
			count = obj.count;
			for (size_t i = 0; i < count; i++) {
				messageTable[i] = obj.messageTable[i];
			}
		}
	}

	return *this;
}

Notifications::Notifications(Notifications&& rhs) {
	capacity = 10;
	count = 0;
	messageTable = new Message[capacity];
	delete[] messageTable;
	count = rhs.count;
	messageTable = rhs.messageTable;
	rhs.count = 0;
	rhs.messageTable = nullptr;
}

Notifications&& Notifications::operator=(Notifications&& obj) {
	if (this != &obj) {
		delete[] messageTable;
		count = obj.count;
		messageTable = obj.messageTable;
		obj.count = 0;
		obj.messageTable = nullptr;
	}
	return std::move(*this);
}

Notifications::~Notifications() {
	delete[] messageTable;
}

void Notifications::operator+=(const Message& msg) {
	capacity = 10;
	if (count == 0) {
		messageTable = new Message[capacity];
	}
	if (count < capacity) {
		messageTable[count] = msg;
		count++;
	}
}

void Notifications::display(std::ostream& os) const {
	for (size_t i = 0; i < count; i++) {
		messageTable[i].display(os);
		os << "\n";
	}
}