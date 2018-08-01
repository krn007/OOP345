/* OOP345 Workshop 6
Name - Karan Shah
Student_Id: 129965166
Date - 28th Decemeber 2017*/

#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <functional>

class Grades
{
	size_t count;
	struct studentEntry
	{
		std::string studentNumber;
		double studentMark;
	} *studentTable;

public:
	Grades() : count(0)
	{
	}
	Grades(const char* filename) : count(0)
	{
		std::fstream is(filename);
		if (is.is_open())
		{
			std::string line;
			while (getline(is, line))
			{
				count++;
			}


			is.clear();
			is.seekg(0);

			studentTable = new studentEntry[count];

			for (size_t i = 0; i < count; i++)
			{
				is >> studentTable[i].studentNumber;
				is >> studentTable[i].studentMark;
			}

			is.close();
		}
		else
		{
			throw std::string("Grade(\"") + filename + "\") - cannot open file \n ";
		}
	}
	void displayGrades(std::ostream& os, std::function<std::string(double mark)> letter)const
	{
		for (size_t i = 0; i < count; i++)
		{
			os << studentTable[i].studentNumber << " "
				<< studentTable[i].studentMark << " "
				<< letter(studentTable[i].studentMark)
				<< "\n";
		}
	}

};
