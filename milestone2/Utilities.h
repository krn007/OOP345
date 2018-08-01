#include <string>
#include <fstream>

class Utilities {
	size_t field_width;           // maximum field width needed 
	static char delimiter;        // field delimiter character
	static std::ofstream logFile; // log file
public:
	Utilities();
	void setFieldWidth(size_t fw) { field_width = fw; }
	size_t getFieldWidth() const { return field_width; }
	const std::string nextToken(const std::string& str, size_t& next_pos, bool& more);
	static void setDelimiter(const char c);
	static void setLogFile(const char* filename);
	static std::ofstream& getLogFile();

	// add trim functions //
	std::string& ltrim(std::string& s, const char* t = " \t\n\r");
	std::string& rtrim(std::string& s, const char* t = " \t\n\r");
};


