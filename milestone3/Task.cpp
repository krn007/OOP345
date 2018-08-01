#include <iomanip>
#include "Task.h"
#include "Utilities.h"

//char Task::delimiter = '|';
size_t Task::field_width = 0;

Task::Task(const std::string& record) {
	slots = "1";
	pNextTask[passed] = nullptr;
	pNextTask[redirect] = nullptr;

	size_t next_pos = 0;
	bool more = true;
	Utilities u(field_width);

	name = u.nextToken(record, next_pos, more);
	if (more) slots = u.nextToken(record, next_pos, more);
	if (more) nextTask[passed] = u.nextToken(record, next_pos, more);
	if (more) nextTask[redirect] = u.nextToken(record, next_pos, more);

	field_width = u.getFieldWidth();
}

const std::string& Task::getName() const {
	return name;
}

unsigned int Task::getSlots() const {
	return std::stoi(slots);
}

bool Task::validate(const Task& task) {
	if (task.name == nextTask[passed]) pNextTask[passed] = &task;
	else if (task.name == nextTask[redirect]) pNextTask[redirect] = &task;

	return (nextTask[passed].empty() || pNextTask[passed]) &&
		(nextTask[redirect].empty() || pNextTask[redirect]);
}

const Task* Task::getNextTask(Quality quality) const {
	if (pNextTask[quality] == nullptr) {
		throw "*** Validate [" + nextTask[quality] + "] @ [" + name + "] ***";
	}
	return pNextTask[quality];
}

void Task::display(std::ostream& os) const {
	os << "Task Name    : " << std::left << std::setw(field_width + 3) <<
		"[" + name + "]" <<
		"[" << slots << "]" << std::endl;

	if (!nextTask[passed].empty()) {
		os << " Continue to : " << std::left << std::setw(field_width + 2) <<
			"[" + nextTask[passed] + "]";
		if (pNextTask[passed] == nullptr) os << " *** to be validated ***";
		os << std::endl;
	}

	if (!nextTask[redirect].empty()) {
		os << " Redirect to : " << std::left << std::setw(field_width + 2) <<
			"[" + nextTask[redirect] + "]";
		if (pNextTask[redirect] == nullptr) os << " *** to be validated ***";
		os << std::endl;
	}
}

//void Task::setDelimiter(const char c) {
//  delimiter = c;  
//}

size_t Task::getFieldWidth() {
	return Task::field_width;
}

bool operator==(const Task& task1, const Task& task2) {
	return task1.getName() == task2.getName();
}
