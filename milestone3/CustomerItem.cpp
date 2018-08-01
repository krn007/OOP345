#include "CustomerItem.h"
#include "Utilities.h"
#include <iomanip>

CustomerItem::CustomerItem(const std::string& n) : name(n), filled(false), code(0) {
}

bool CustomerItem::asksFor(const Item& item) const {
	return false;
}

bool CustomerItem::isFilled() const {
	return filled;
}

void CustomerItem::fill(const unsigned int c) {
	code = c;
	filled = true;
}

void CustomerItem::clear() {
	code = 0;
	filled = false;
}

const std::string& CustomerItem::getName() const {
	return name;
}

void CustomerItem::display(std::ostream& os) const {
	if (name.size() > 0) {
		os << " " << (filled ? "+" : "-");
		os << " [" << std::right << std::setw(5) << std::setfill('0') << code << std::setfill(' ') << "] ";
		os << name << std::endl;
	}
}
