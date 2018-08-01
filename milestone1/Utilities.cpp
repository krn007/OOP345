#include "Utilities.h"

char Utilities::delimiter = '|';
std::ofstream Utilities::logFile;
Utilities::Utilities()
{
	field_width = 1;
}

std::string& Utilities::ltrim(std::string& s, const char* t)
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}
std::string& Utilities::rtrim(std::string& s, const char* t)
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

const std::string Utilities::nextToken(const std::string& str, size_t& next_pos, bool& more)
{
	// For malformed records by "/" //
	std::string record = str;
	size_t pos;
	while ((pos = record.find("/")) != std::string::npos) {
		record.replace(pos, 1, "|");
	}
	//==============================//


	std::string token;
	for (; (record.size() > next_pos) && (record[next_pos] != delimiter); next_pos++) {
		token += record[next_pos];
	}
	// trim left & right //
	token = ltrim(rtrim(token));

	if (record.size() > next_pos) {
		more = true;
		next_pos++;
	}
	else {
		more = false;
	}

	if (field_width < token.size()) {
		field_width = token.size();
	}
	return token;
}

void Utilities::setDelimiter(const char c) {
	delimiter = c;
}

void Utilities::setLogFile(const char* filename)
{
	logFile.open(filename, std::ofstream::out | std::ofstream::app);
}
std::ofstream& Utilities::getLogFile()
{
	return logFile;
}