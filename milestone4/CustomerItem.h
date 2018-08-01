#include <iostream>
#include <string>

class Item;

class CustomerItem {
	std::string name;  // name of the requested component 
	bool filled;       // status of the request
	unsigned int code; // unique shipping label
public:
	CustomerItem(const std::string& strName = std::string());
	bool asksFor(const Item&) const;
	bool isFilled() const;
	void fill(const unsigned int);
	void clear();
	const std::string& getName() const;
	void display(std::ostream& os) const;
};
