#include "ItemManager.h"
#include "Item.h"

void ItemManager::display(std::ostream& os, bool isFull) const
{
	//size_t num = this->size();  // inheritated from vector //
	//size_t i = 0;	
	//for (; i < num; i++){
	//	this->at(i).display(os, isFull);
	//}

	std::vector<Item>::const_iterator iter = this->cbegin();
	//	auto iter = this->cbegin();
	for (; iter != this->cend(); iter++) {
		iter->display(os, isFull);
	}
}