#include <iostream>
#include <vector>

class Task;
class ItemManager;

class TaskManager : public std::vector<Task> {
public:
	void validate(std::ostream& os);
	void validate(const ItemManager& itemMng, std::ostream& os);
	void display(std::ostream& os) const;
};

