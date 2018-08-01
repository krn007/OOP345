#include "ItemManager.h"
#include "Item.h"

void ItemManager::display(std::ostream& os, bool isFull) const
{
	std::vector<Item>::const_iterator iter = this->cbegin();
	for (; iter != this->cend(); iter++) {
		iter->display(os, isFull);
	}
}