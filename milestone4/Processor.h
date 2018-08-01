#include <iostream>
#include <fstream>
#include <deque>
#include <list>
#include <functional>
#include "CustomerOrder.h"
#include "Task.h"
#include <vector>

class Item;
class OrderManager;

class Processor : public Task {
	Item* item_;                        // address of item processed by this task 
	std::deque<CustomerOrder> waiting;  // orders to be processed
	std::deque<CustomerOrder> process;  // orders being processed
	std::deque<CustomerOrder> complete; // orders completed 
	unsigned int num_end_slots;         // number of currently empty end slots
	bool is_a_filler;                   // type of processor (filler, retriever)
	std::function<Task::Quality(int)> inspector; // inspects the quality
public:
	Processor(const std::string& record, std::function<Task::Quality(int)> func);
	void load(Item& item);
	void accept(CustomerOrder&& order);
	void pass(int i);
	//	void pass(int i, std::string& str);
	void advance();
	bool empty() const;
	bool readyToShip() const;
	bool readyToPass() const;
	void ship(OrderManager& finished);
	void display(std::ostream& os) const;
};


