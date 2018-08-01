#include <iostream>
#include <fstream>
#include <string>
#include "SecureData.h"

using namespace std;

namespace w10 {

	void converter(char* t, char key, int n, const Cryptor& c)
	{
		for (int i = 0; i < n; i++)
		{
			t[i] = c(t[i], key);
		}
	}

	SecureData::SecureData(const char* file, char key)
	{
		fstream input(file, ios::in);
		if (input)
		{
			nbytes = 0;
			input >> noskipws;
			while (input.good())
			{
				char c;
				input >> c;
				nbytes++;
			}
			nbytes--;
			input.clear();
			input.seekg(0, ios::beg);
			text = new char[nbytes + 1];

			int i = 0;
			while (input.good())
				input >> text[i++];
			text[--i] = '\0';
			cout << endl;
			cout << nbytes;
			cout << " bytes copied from text ";
			cout << file;
			cout << " into memory (null byte added)";
			cout << endl;
			encoded = false;

			code(key);
			cout << "Data encrypted in memory";
			cout << endl;
		}
	}

	SecureData::~SecureData()
	{
		delete[] text;
	}

	void SecureData::display(ostream& os) const
	{
		if (text && !encoded)
			os << text << endl;
	}

	void SecureData::code(char key)
	{
		converter(text, key, nbytes, Cryptor());
		encoded = !encoded;
	}

	void SecureData::backup(const char* file) {
		if (text)
		{
			fstream os(file, ios::out);
			if (os)
			{
				for (int i = 0; i < nbytes; ++i)
				{
					os << text[i];
				}
			}

		}
	}

	void SecureData::restore(const char* file, char key)
	{
		fstream ifs(file, ios::in);
		if (ifs)
		{
			nbytes = 0;
			ifs >> noskipws;
			char tmpc;
			while (ifs.good())
			{
				ifs >> tmpc;
				nbytes++;
			}

			if (text)
			{
				delete[] text;
				text = nullptr;
			}
			text = new char[nbytes + 1];

			ifs.clear();
			ifs.seekg(0, ios::beg);
			nbytes = -1;
			while (ifs.good())
			{
				ifs >> text[++nbytes];
			}
			text[nbytes + 1] = '\0';

			cout << endl;
			cout << nbytes + 1;
			cout << " bytes copied from binary file ";
			cout << file;
			cout << " into memory (null byte included)";
			cout << endl;

			encoded = true;

			code(key);
			cout << "Data decrypted in memory";
			cout << endl;
		}
	}

	ostream& operator<<(ostream& os, const SecureData& data)
	{
		data.display(os);
		return os;
	}

}