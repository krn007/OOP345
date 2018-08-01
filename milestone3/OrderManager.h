#include <iostream>
#include <vector>

class ItemManager;
class CustomerOrder;

class OrderManager : public std::vector<CustomerOrder> {
public:
	CustomerOrder&& extract();
	void validate(const ItemManager& itemMng, std::ostream& os);
	void display(std::ostream& os) const;
};

