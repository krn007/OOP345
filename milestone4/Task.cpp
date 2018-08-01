#include "Task.h"
#include "Utilities.h"
#include <iomanip>

size_t Task::field_width = 1;

Task::Task()
{
	slots = "1";
	pNextTask[0] = pNextTask[1] = nullptr;
}

Task::Task(const std::string& strRecord)
{
	slots = "1";
	pNextTask[0] = pNextTask[1] = nullptr;

	Utilities util;
	util.setFieldWidth(field_width);

	size_t pos = 0;
	bool more = true;
	name = util.nextToken(strRecord, pos, more);
	if (!name.empty()) {
		if (more) {
			slots = util.nextToken(strRecord, pos, more);
			if (more) {
				nextTask[passed] = util.nextToken(strRecord, pos, more);
				if (more) {
					nextTask[redirect] = util.nextToken(strRecord, pos, more);
				}
			}
		}
	}
	else {
		std::string errmsg = "Error in Record";
		throw errmsg;
	}

	field_width = util.getFieldWidth();
}




const std::string& Task::getName() const
{
	return name;
}

unsigned int Task::getSlots() const
{
	return (unsigned int)atoi(slots.data());
}

const Task* Task::getNextTask(Quality quantity) const
{
	if (!pNextTask[quantity]) {
		std::string errmsg = "*** Validate  [" + nextTask[quantity] + "] @ [" + name + "] ***";
		//	throw errmsg;
	}
	return pNextTask[quantity];

}

bool Task::validate(const Task& task)
{
	for (unsigned int i = passed; i <= redirect; i++) {
		if (!nextTask[i].empty()) {
			if (nextTask[static_cast<Quality>(i)] == task) {
				pNextTask[i] = &task;
			}
		}
	}

	// validation //
	bool valid = true;
	for (unsigned int i = passed; i <= redirect; i++) {
		if (!nextTask[i].empty() && (pNextTask[i] == nullptr)) {
			valid = false;
		}
	}
	return valid;
}

void Task::display(std::ostream& os) const
{
	size_t width = field_width + 3;
	std::string tmpname = "[" + name + "]";
	std::string tmpslot = "[" + slots + "]";

	os << "Task Name    : " << std::left;
	os << std::setw(width) << tmpname << tmpslot << std::endl;

	std::string strTitle[2];
	strTitle[passed] = " Continue to : ";
	strTitle[redirect] = " Redirect to : ";
	for (unsigned int i = passed; i <= redirect; i++) {
		if (!nextTask[i].empty()) {
			tmpname = "[" + nextTask[i] + "]";
			if (pNextTask[i]) {
				os << strTitle[i] << std::setw(width) << tmpname << std::endl;
			}
			else {
				os << strTitle[i] << std::setw(width) << tmpname << "*** to be validated ***" << std::endl;
			}
		}
	}
}

bool operator==(const Task& t1, const Task& t2) {
	return !t1.getName().compare(t2.getName());
}
