#include "AssemblyLine.h"
#include "Processor.h"
#include "ItemManager.h"
#include "Item.h"
#include "OrderManager.h"
#include "Utilities.h"
#include <algorithm>

void AssemblyLine::push_back(Processor&& processor)
{
	//	std::cout << "KSH-------AssemblyLine::push_back" << std::endl;
	vector::push_back(std::move(processor));
}

void AssemblyLine::validate(std::ostream& os)
{
	//	std::cout << "KSH-------AssemblyLine::validate1" << std::endl;
	std::vector<Processor>::iterator i = this->begin();
	bool valid = true;
	for (; i != this->end() && valid; i++) {
		bool invalid = true;

		std::vector<Processor>::iterator j = this->begin();
		for (; j != this->cend() && invalid; j++) {
			if (i->validate(*j)) {
				invalid = false;
			}
		}
		valid = !invalid;
	}
	if (!valid) {
		std::cerr << "*** Not all Tasks have been validated ***\n";
	}
}
void AssemblyLine::validate(ItemManager& itemManager, std::ostream& os)
{
	//	std::cout << "KSH-------AssemblyLine::validate2" << std::endl;
	std::vector<Item>::const_iterator iter = itemManager.cbegin();
	for (; iter != itemManager.cend(); iter++) {

		// lamda function ============================//
		std::string strTask;
		auto lamda_vaildate = [&](const Task& task) {
			return !task.getName().compare(strTask);
		};

		strTask = iter->getRemover();
		if (std::find_if(this->cbegin(), this->cend(), lamda_vaildate) == this->cend()) {
			os << strTask << " is not available\n";
		}

		strTask = iter->getFiller();
		if (std::find_if(this->cbegin(), this->cend(), lamda_vaildate) == this->cend()) {
			os << strTask << " is not available\n";
		}
	}
}
void AssemblyLine::loadItem(ItemManager& itemManager)
{
	//for (auto& i : *this)
	//	for (auto& n : itemManager)
	//		if (i.getName() == n.getFiller() || i.getName() == n.getRemover())
	//			i.load(n);

	size_t pnum = this->size();
	size_t inum = itemManager.size();

	for (size_t i = 0; i < pnum; i++) {
		for (size_t j = 0; j < inum; j++) {
			std::string name = this->at(i).getName();
			std::string filler = itemManager[j].getFiller();
			std::string remover = itemManager[j].getRemover();

			if (!name.compare(filler)) {
				this->at(i).load(itemManager[j]);
			}
		}
	}
}
// processing
void AssemblyLine::loadOrders(OrderManager& orderManager, const std::string& entryProcessor, std::ostream& os)
{
	//	std::cout << "KSH-------AssemblyLine::loadOrders" << std::endl;
	auto lamda_vaildate = [&](const Processor& p) {
		return !p.getName().compare(entryProcessor);
	};

	// Check entry processor and AssemblyLine's entryProcessor
	std::vector<Processor>::iterator iter = std::find_if(this->begin(), this->end(), lamda_vaildate);
	if (iter != this->end()) {  // if entryProcrssor is exist in AssemblyLine, 
		while (!orderManager.empty()) {
			// moves the customer orders to assembly line's entryProcessor.  
			iter->accept(orderManager.extract());  // waiting entry processor //
			orderManager.pop_back();
		}
	}
}
bool AssemblyLine::process(OrderManager& finishing, unsigned int n)
{
	for (size_t k = 0; k < n; k++) {
		size_t pnum = this->size();
		bool allempty = true;
		for (size_t i = 0; i < pnum; i++) {
			Processor&& p = std::move(this->at(i));


			if (!p.empty()) {
				p.advance();

				if (p.readyToPass()) {
					p.pass(rand() % 100);
				}

				if (p.readyToShip()) {
					p.ship(finishing);
					//	Utilities::getLogFile() << "Task Completed\n";
				}

				allempty = false;
			}
		}

		if (allempty == true) {
			return true;
		}
	}

	return false;
}
// reporting
void AssemblyLine::display(std::ostream& os) const
{
	for (auto& n : *this) {
		n.display(os);
	}
}
