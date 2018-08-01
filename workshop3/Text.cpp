/* OOP345 Workshop 3
Name - Karan Shah
Student_Id: 129965166
Date - 28th Decemeber 2017*/

#include "Text.h"
namespace w3 {
	Text::Text()
	{
		strs = nullptr;
		fCount = 0;
	}

	Text::Text(const string fileName) : fCount(0)
	{
		ifstream is(fileName);

		if (is.is_open())
		{
			int count = 0;
			string line;

			do
			{
				getline(is, line, '\n');
				count++;
			} while (!is.fail());

			is.clear();
			is.seekg(0, ios::beg);

			strs = new string[count];

			for (int i = 0; !is.fail(); i++)
				getline(is, strs[i], '\n');

			fCount = count;
			is.close();
		}
		else
			Text();
	}

	Text::Text(const Text& other)
	{
		fCount = 0;
		strs = '\0';
		*this = other;
	}

	Text& Text::operator=(const Text& other) {
		if (this != &other) {
			if (strs) {
				delete[] strs;
				strs = '\0';
				fCount = 0;
			}

			if (other.strs) {
				fCount = other.fCount;
				strs = new string[fCount];

				for (size_t i = 0; i < fCount; i++)
					strs[i] = other.strs[i];
			}
		}

		return *this;
	}

	Text::Text(Text&& other) {
		fCount = 0;
		strs = '\0';
		*this = move(other);
	}

	Text&& Text::operator=(Text&& other) {
		if (this != &other) {
			if (strs) {
				delete[] strs;
				strs = '\0';
				fCount = 0;
			}

			fCount = other.fCount;
			strs = other.strs;

			other.fCount = 0;
			other.strs = '\0';
		}

		return move(*this);
	}

	Text::~Text() {
		delete[] strs;
		strs = nullptr;
	}

	size_t Text::size() const {
		return fCount;
	}
}