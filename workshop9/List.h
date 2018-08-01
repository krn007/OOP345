// Workshop 9 - Smart Pointers
// List.h

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iomanip>

using namespace std;

namespace w9 {
	template <typename Type>

	class List
	{
		vector<Type> list;

	public:

		List()
		{
		}

		List(const char* file)
		{
			ifstream f(file);
			if (!f) {
				throw string("* Failed to open f ") +
					string(file) + string(" *");
			}
			while (f)
			{
				Type t;
				if (t.load(f))
				{
					list.push_back(*new Type(t));
				}
			}
		}
		size_t size() const
		{
			return list.size();
		}
		const Type& operator[](size_t i) const
		{
			return list[i];
		}
		void operator+= (unique_ptr<Type>& Un)
		{
			list.push_back(*Un);
		}
		void display(ostream& os) const
		{
			os << fixed << setprecision(2);
			for (auto& n : list)
				n.display(os);
		}
	};

	template<typename Type>
	ostream& operator<<(ostream& os, const List<Type>& T)
	{
		T.display(os);
		return os;
	}
}