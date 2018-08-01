#include "Item.h"
#include "Utilities.h"
#include <iomanip>

size_t Item::field_width = 1;
Item::Item(const std::string& strRecord) :code(1)
{
	description = "no detailed description";

	Utilities util;
	util.setFieldWidth(field_width);

	size_t pos = 0;
	bool more = true;
	name = util.nextToken(strRecord, pos, more);
	field_width = util.getFieldWidth();

	if (!name.empty()) {
		if (more) {
			filler = util.nextToken(strRecord, pos, more);
			if (more) {
				remover = util.nextToken(strRecord, pos, more);
				if (more) {
					code = (unsigned int)atoi(util.nextToken(strRecord, pos, more).data());
					if (more) {
						description = util.nextToken(strRecord, pos, more);
					}
				}
			}
		}
	}
	else {
		std::string errmsg = strRecord + "<-- *** no token found before the delimiter ***";
		throw errmsg;
	}
}



bool Item::empty() const {
	return name.empty();
}

Item& Item::operator++(int)
{
	code++;
	return *this;
}

const std::string& Item::getName() const
{
	return name;
}
const std::string& Item::getFiller() const
{
	return filler;
}
const std::string& Item::getRemover() const
{
	return remover;
}

unsigned int Item::getCode() const
{
	return code;
}

void Item::display(std::ostream& os, bool full) const
{
	os << std::left << std::setw(field_width) << name
		<< " [" << std::right << std::setw(CODE_WIDTH) << std::setfill('0') << code << "]"
		<< std::left << std::setfill(' ');

	if (full) {
		os << " From " << std::setw(field_width) << filler;
		os << " To " << std::setw(field_width) << remover << std::endl;
		os << std::right << std::setw(field_width + CODE_WIDTH + 4) << " : " << description;
	}

	os << std::left << std::endl;
}

