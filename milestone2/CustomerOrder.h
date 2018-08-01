#include <iostream>
#include <string>


#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

class Item;
class CustomerItem;

class CustomerOrder {
	std::string name;          // name of the customer
	std::string product;       // name of the product
	CustomerItem* order;       // address of the customer requests 
	unsigned int nOrders;      // number of requests
	static size_t field_width; // current maximum field width
public:
	CustomerOrder(const std::string& strRecord);
	CustomerOrder(const CustomerOrder& cus);
	CustomerOrder& operator=(const CustomerOrder&) = delete;                // copy operator is not permited.
	CustomerOrder(CustomerOrder&& cus);
	CustomerOrder&& operator=(CustomerOrder&& cus);
	~CustomerOrder();
	unsigned int noOrders() const;
	const std::string& operator[](unsigned int) const;
	void fill(Item& item);
	void remove(Item&);
	bool empty() const;
	void display(std::ostream&) const;
};


