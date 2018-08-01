#include "CustomerOrder.h"
#include "Utilities.h"
#include "CustomerItem.h"
#include "Item.h"
#include <iomanip>
#include <vector>

size_t CustomerOrder::field_width = 1;
CustomerOrder::CustomerOrder(const std::string& strRecord) : nOrders(0), order(nullptr)
{
	Utilities util;
	util.setFieldWidth(field_width);

	size_t pos = 0;
	bool more = true;
	name = util.nextToken(strRecord, pos, more);
	if (!name.empty()) {
		if (more) {
			product = util.nextToken(strRecord, pos, more);
			// read item
			std::vector<std::string> tmpVec;
			while (more) {
				std::string tmp = util.nextToken(strRecord, pos, more);
				if (!tmp.empty()) {
					tmpVec.push_back(std::move(tmp));
				}
			}

			order = new CustomerItem[nOrders = tmpVec.size()];
			std::vector<std::string>::iterator iter = tmpVec.begin();
			int index = 0;
			for (; iter != tmpVec.end(); iter++) {
				order[index] = CustomerItem(*iter);
				index++;
			}
		}
		field_width = util.getFieldWidth();
	}
	else {
		std::string errmsg = strRecord + "<-- *** no token found before the delimiter ***";
		throw errmsg;
	}
}

CustomerOrder::CustomerOrder(const CustomerOrder& cus) : nOrders(0), order(nullptr)
{
	std::string errmsg = "Error: copy constructor is called";
	throw errmsg;
}

CustomerOrder::CustomerOrder(CustomerOrder&& cus) NOEXCEPT
{
	nOrders = 0;
	order = nullptr;
	*this = std::move(cus);
}

CustomerOrder&& CustomerOrder::operator=(CustomerOrder&& cus) NOEXCEPT
{
	if (this != &cus) {
		if (order) {
			delete[] order;
		}
		name = cus.name;
		product = cus.product;
		nOrders = cus.nOrders;
		order = cus.order;

		cus.name.clear();
		cus.product.clear();
		cus.nOrders = 0;
		cus.order = nullptr;
	}

	return std::move(*this);
}

CustomerOrder::~CustomerOrder()
{
	if (order) {
		delete[] order;
		order = nullptr;
	}
}

bool CustomerOrder::empty() const {
	return name.empty();
}

unsigned int CustomerOrder::noOrders() const {
	return nOrders;
}

const std::string& CustomerOrder::operator[](unsigned int i) const {
	if (i >= nOrders) {
		std::string errmsg = "The index is out of bounds";
		throw errmsg;
	}
	return order[i].getName();
}

void CustomerOrder::fill(Item& item) {
	for (unsigned int i = 0; i < nOrders; i++) {
		if (!order[i].getName().compare(item.getName())) {
			if (order[i].isFilled() == false) {
				order[i].fill(item.getCode());
				item++;
			}
		}
	}
}

void CustomerOrder::remove(Item& item) {
	for (unsigned int i = 0; i < nOrders; i++) {
		if (!order[i].getName().compare(item.getName())) {
			order[i].clear();
		}
	}
}

void CustomerOrder::display(std::ostream& os) const {
	os << std::left << std::setw(field_width) << name << " : " << std::setw(field_width) << product << std::endl;
	for (unsigned int i = 0; i < nOrders; i++) {
		order[i].display(os);
	}
}