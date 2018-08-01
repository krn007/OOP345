#include "OrderManager.h"
#include "CustomerOrder.h"
#include <algorithm>
#include "ItemManager.h"
#include "Item.h"

CustomerOrder&& OrderManager::extract()
{
	return std::move(this->back());
}

void OrderManager::validate(const ItemManager& itemMng, std::ostream& os)
{
	std::vector<CustomerOrder>::iterator iter = this->begin();
	for (; iter != this->end(); iter++) {
		for (unsigned int i = 0; i < iter->noOrders(); i++) {
			// lamda function ============================//
			auto lamda_vaildate = [&](const Item& item) {
				return !item.getName().compare((*iter)[i]);
			};

			if (std::find_if(itemMng.cbegin(), itemMng.cend(), lamda_vaildate) == itemMng.cend()) {
				os << (*iter)[i] << " is unavailable " << std::endl;
			}
		}
	}
}
void OrderManager::display(std::ostream& os) const
{
	for (auto& n : *this) {
		n.display(os);
	}

}