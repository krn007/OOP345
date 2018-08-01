#include "CustomerItem.h"
#include "Item.h"
#include <iomanip>

CustomerItem::CustomerItem(const std::string& strName) : code(0), filled(false)
{
	name = strName;
}

bool CustomerItem::asksFor(const Item&) const
{
	return false;
}
bool CustomerItem::isFilled() const
{
	return filled;
}
void CustomerItem::fill(const unsigned int _code)
{
	code = _code;
	filled = true;
}
void CustomerItem::clear()
{
	code = 0;
	filled = false;
}
const std::string& CustomerItem::getName() const
{
	return name;
}
void CustomerItem::display(std::ostream& os) const
{
	char cSign;
	if (filled)	cSign = '+';
	else cSign = '-';

	if (!name.empty()) {
		os << " " << cSign << " [" << std::right << std::setw(CODE_WIDTH)
			<< std::setfill('0') << code << std::setfill(' ') << "] "
			<< name << std::endl;
	}
}
