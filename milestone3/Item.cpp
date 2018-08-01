#include "Item.h"
#include "Utilities.h"
#include <iomanip>


size_t Item::field_width = 1;

Item::Item(const std::string& record)
	: name(""), filler(""), remover(""), description("no detailed description"), code(1) {
	size_t position = 0;
	bool ok = true;

	Utilities util(field_width);
	name = util.nextToken(record, position, ok);
	if (!name.empty()) {
		if (ok) filler = util.nextToken(record, position, ok);
		field_width = util.getFieldWidth();

		if (ok) remover = util.nextToken(record, position, ok);
		if (ok) code = std::stoi(util.nextToken(record, position, ok));
		if (ok) description = util.nextToken(record, position, ok);

		if (description.empty()) {
			description = "no detailed description";
		}
	}
}

bool Item::empty() const {
	return name.empty();
}


Item& Item::operator++(int) {
	code++;
	return *this;

}
unsigned int Item::getCode() const {
	return code;
}

const std::string& Item::getName() const {
	return name;
}

const std::string& Item::getFiller() const {
	return filler;
}

const std::string& Item::getRemover() const {
	return remover;
}

void Item::display(std::ostream& os, bool full) const {
	os << std::left << std::setw(field_width) << name;
	os << " [" << std::right << std::setw(CODE_WIDTH) << std::setfill('0') << code << "]";
	os << std::left << std::setfill(' ');

	if (full) {
		os << " From " << std::setw(field_width) << filler;
		os << " To " << std::setw(field_width) << remover << std::endl;
		os << std::right << std::setw(field_width + CODE_WIDTH + 4) << " : " << description;
	}

	os << std::left << std::endl;
}