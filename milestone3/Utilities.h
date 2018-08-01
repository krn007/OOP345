#include <string>

class Utilities {
	size_t field_width;
	static char delimiter;
public:
	// receives the minimum value of the field width to be used in displaying any
	// token in a list of tokens.
	Utilities(size_t minimum_field_width = 1u);
	// resets the field width to fw
	void setFieldWidth(size_t fw);
	// returns the field width
	size_t getFieldWidth() const;
	// receives a reference to string str, a reference to the position (next_pos)
	// in this string at which to start extracting the next token, and a
	// reference to a boolean flag (more).  This function returns the next token
	// found and sets more to true if the function has found more tokens after
	// the extracted token; false otherwise.  This function update the
	// field_width data member if its current value is less than the size of the
	// token extracted
	const std::string nextToken(const std::string& str, size_t& next_pos, bool& more);
	// resets the delimiter for this class to the character received
	static void setDelimiter(const char c);
	// returns the delimiter for this class
	static const char getDelimiter();
};
