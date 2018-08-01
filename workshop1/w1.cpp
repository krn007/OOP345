/* OOP345 Workshop 1
Name - Karan Shah
Student_Id: 129965166
Date - 28th Decemeber 2017*/

#include <iostream>
#include <cstring>
#include "CString.h"
#include "process.h"
#define MAX 3using namespace std;
int main(int args, char* argv[]) {	cout << "Command Line :";
	for (int i = 0; i < args; i++) {
		cout << " " << argv[i];
	}
	cout << endl;	if (args == 1) {		cout << "Insufficient number of arguments(min 1)" << endl;		return 1;	}	cout << "Maximum number of characters stored : " << 3 << endl;
	for (int i = 1; i < args; i++) {		process(argv[i]);	}	return 0;
}