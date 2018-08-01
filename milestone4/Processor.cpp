#include "Processor.h"
#include <string>
#include "Item.h"
#include "Utilities.h"
#include "OrderManager.h"

Processor::Processor(const std::string& record, std::function<Task::Quality(int)> func) :
	item_(nullptr), is_a_filler(true), Task(record)
{
	num_end_slots = Task::getSlots();  // ???
	inspector = func;
	//	std::cout << "KSH-------Processor::Processor" << std::endl;
}


void Processor::load(Item& item)
{
	//	std::cout << "KSH-------Processor::load" << std::endl;
	item_ = &item;
	if (!getName().compare(item.getFiller())) {
		is_a_filler = true;
	}
	else {
		is_a_filler = false;
	}
}

bool Processor::empty() const
{
	//	std::cout << "KSH-------Processor::empty" << std::endl;
	if (waiting.empty() && process.empty() && complete.empty()) {
		return true;
	}
	return false;
}

void Processor::accept(CustomerOrder&& order)
{
	//	std::cout << "KSH-------Processor::accept" << std::endl;
	waiting.push_back(std::move(order));
}

void Processor::pass(int i)
{
	//If there is more than one possible next processor, this function calls inspector to decide the choice.
	auto checkQuality = getNextTask(passed) && getNextTask(redirect) ? inspector(i) : passed;

	if (!complete.empty()) {
		//moves the order at the front of the complete queue to the next processor.
		CustomerOrder&& order = std::move(complete.front());
		Processor* nextP = (Processor*)getNextTask(checkQuality);
		nextP->accept(std::move(order));
		complete.pop_front();
	}

	if (checkQuality == passed)
		Utilities::getLogFile() << "Passed to ";
	else
		Utilities::getLogFile() << "Redirect to ";
	Utilities::getLogFile() << "[" << getName() << "]\n";

}

void Processor::advance()
{
	//For every customer order in the process queue this function either fills one customer 
	//item request with the item requested if the processor is a filler task or retreive the item 
	//if the process is remover task (not a filler).
	if (!process.empty() && num_end_slots) {
		num_end_slots--;
		if (item_) {
			//is_a_filler ? process.back().fill(*item_) : process.back().remove(*item_);
			if (is_a_filler) {
				for (auto& n : process)
					n.fill(*item_);
			}
			else {
				for (auto& n : process)
					n.remove(*item_);
			}
		}

		//If there are no empty end slots, 
		//this function moves the order in the last slot from the front of the process queue 
		//to the complete queue
		complete.push_back(std::move(process.front()));
		process.pop_front();


		//adjusts the number of end slots to either 1 or the number of slots in the processor if the process queue is empty
		if (process.empty()) {
			num_end_slots = 1;
		}
	}

	//the front of the waiting queue to the back of the process queue
	if (!waiting.empty()) {
		process.push_back(std::move(waiting.front()));
		waiting.pop_front();
	}

}

bool Processor::readyToShip() const
{
	//std::cout << "KSH-------Processor::readyToShip" << std::endl;
	if (!complete.empty() && !getNextTask(passed)) {
		return true;
	}
	return false;
}
bool Processor::readyToPass() const
{
	//std::cout << "KSH-------Processor::readyToPass" << std::endl;
	if (!complete.empty() && getNextTask(passed)) {
		return true;
	}
	return false;
}
void Processor::ship(OrderManager& finished)
{
	//	std::cout << "KSH-------Processor::ship" << std::endl;
	if (!complete.empty()) {
		finished.push_back(std::move(complete.front()));
		complete.pop_front();

		//Logs the event and moves the order to the finished manager
		Utilities::getLogFile() << "Task Completed\n";
	}
}
void Processor::display(std::ostream& os) const
{
	//	std::cout << "KSH-------Processor::display" << std::endl;
	Task::display(os);

	if (item_) {
		os << " Item to add : ";		item_->display(os);
	}
	else {
		os << " Item to add :" << " ---" << std::endl;
	}
}