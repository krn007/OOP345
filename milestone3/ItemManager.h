#include <iostream>
#include <vector>

class Item;
class ItemManager : public std::vector<Item>
{
public:
	void display(std::ostream& os, bool isFull = false) const;
};
