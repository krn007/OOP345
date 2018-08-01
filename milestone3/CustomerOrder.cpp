#include "CustomerOrder.h"
#include "Item.h"
#include "CustomerItem.h"
#include "Utilities.h"
#include <iomanip>
#include <vector>


size_t CustomerOrder::field_width = 1;

CustomerOrder::CustomerOrder(const std::string& record)
	: name(""), product(""), order(nullptr), nOrders(0) {
	size_t position = 0;
	bool ok = true;

	Utilities util(field_width);
	name = util.nextToken(record, position, ok);
	if (!name.empty()) {
		if (ok) {
			product = util.nextToken(record, position, ok);
		}

		std::vector<std::string> vec;
		while (ok) {
			std::string t = util.nextToken(record, position, ok);
			if (t.size() > 0) {
				vec.push_back(t);
			}
		}

		nOrders = vec.size();
		order = new CustomerItem[nOrders];
		for (unsigned int i = 0; i < nOrders; i++) {
			order[i] = CustomerItem(vec[i]);
		}

		field_width = util.getFieldWidth();
	}
}

CustomerOrder::CustomerOrder(const CustomerOrder& rhs) {
	throw std::string("the copy constructor should never be called");
	name = rhs.name;
	product = rhs.product;
	nOrders = rhs.nOrders;

	if (rhs.order) {
		order = new CustomerItem[nOrders];
		for (unsigned int i = 0; i < nOrders; i++) {
			order[i] = rhs.order[i];
		}
	}
	else {
		order = nullptr;
	}
}

CustomerOrder::CustomerOrder(CustomerOrder&& rhs) noexcept {
	order = nullptr;
	*this = std::move(rhs);
}

CustomerOrder&& CustomerOrder::operator=(CustomerOrder&& rhs) noexcept {
	if (this != &rhs) {
		if (order) {
			delete[] order;
		}

		name = rhs.name;
		product = rhs.product;
		nOrders = rhs.nOrders;
		order = rhs.order;

		rhs.name.clear();
		rhs.product.clear();
		rhs.nOrders = 0;
		rhs.order = nullptr;
	}

	return std::move(*this);
}

CustomerOrder::~CustomerOrder() {
	if (order) {
		delete[] order;
	}
}

unsigned int CustomerOrder::noOrders() const {
	return nOrders;
}

const std::string& CustomerOrder::operator[](unsigned int i) const {
	if (i >= nOrders) {
		throw std::string("Out of bound");
	}

	return order[i].getName();
}

void CustomerOrder::fill(Item& item) {
	for (unsigned int i = 0; i < nOrders; i++) {
		if (!order[i].getName().compare(item.getName())) {
			order[i].fill(item.getCode());
			item++;
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

bool CustomerOrder::empty() const {
	return name.empty();
}

void CustomerOrder::display(std::ostream& os) const {
	os << std::left;
	os << std::setw(field_width) << name << " : ";
	os << std::setw(field_width) << product;
	os << std::endl;

	for (unsigned int i = 0; i < nOrders; i++) {
		order[i].display(os);
	}
}

