#include <iostream>
#include <string>

const unsigned int CODE_WIDTH = 5;

class Item {
	std::string name;          // name of the component
	std::string filler;        // name of the filler task
	std::string remover;       // name of the remover task 
	std::string description;   // detailed description
	unsigned int code;         // next shipping label
	static size_t field_width; // current maximum field width
public:
	Item(const std::string& strRecord = std::string());
	bool empty() const;
	Item& operator++(int);
	unsigned int getCode() const;
	const std::string& getName() const;
	const std::string& getFiller() const;
	const std::string& getRemover() const;
	void display(std::ostream&, bool full = false) const;
};


