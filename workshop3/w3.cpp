/* OOP345 Workshop 3
Name - Karan Shah
Student_Id: 129965166
Date - 28th Decemeber 2017*/

#include <iostream>
#include <iomanip>
#include <utility>
#include <ctime>
#include "Text.h"
#define TIME(start, end) double((end) - (start)) / CLOCKS_PER_SEC
using namespace std;
using namespace w3;
int main(int args, char* argv[]) {
	if (args == 1) {
		cerr << argv[0] << ": missing file operand" << endl;
		return 1;
	}
	else if (args != 2) {
		cerr << argv[0] << ": too many arguments" << endl;
		return 2;
	}
	clock_t cs, ce;
	{
		cout << fixed << setprecision(3);
		cs = clock();
		Text a;
		ce = clock();
		cout << "Constructor      " << TIME(cs, ce) << " seconds";
		cout << " - a.size = " << a.size() << endl;

		cs = clock();
		Text b(argv[1]);
		ce = clock();
		cout << "Constructor      " << TIME(cs, ce) << " seconds";
		cout << " - b.size = " << b.size() << endl;

		cs = clock();
		a = b;
		ce = clock();
		cout << "Copy Assignment  " << TIME(cs, ce) << " seconds";
		cout << " - a.size = " << a.size() << endl;

		cs = clock();
		a = move(b);
		ce = clock();
		cout << "Move Assignment  " << TIME(cs, ce) << " seconds";
		cout << " - a.size = " << a.size() << endl;

		cs = clock();
		Text c = a;
		ce = clock();
		cout << "Copy Constructor " << TIME(cs, ce) << " seconds";
		cout << " - c.size = " << c.size() << endl;

		cs = clock();
		Text d = move(a);
		ce = clock();
		cout << "Move Constructor " << TIME(cs, ce) << " seconds";
		cout << " - d.size = " << d.size() << endl;

		cs = clock();
	}
	ce = clock();
	cout << "Destructor       " << TIME(cs, ce) << " seconds" << endl;
}