/* OOP345 Workshop 4
Name - Karan Shah
Student_Id: 129965166
Date - 28th Decemeber 2017*/

#pragma once
#include <iostream>
template <typename K, typename V, int N>
class KVList {
	K k[N];
	V v[N];
	//std::pair<K, V> table[N];
	size_t count;

public:
	KVList() : count(0)
	{
	}

	size_t size() const
	{
		return count;
	}

	const K& key(int i) const
	{
		if (i >= 0 && i < count)
			return k[i];
		//return table[i].first;
	}

	const V& value(int i) const
	{
		if (i >= 0 && i < count)
			return v[i];
		//return table[i].second;
	}
	KVList& add(const K& kk, const V& vv)
	{
		if (count < N) {
			k[count] = kk;
			v[count] = vv;
			//table[count] = std:make_pair(kk, vv);
			count++;
		}

		return *this;
	}

	int find(const K& kk) const
	{
		for (size_t i = 0; i < count; i++) {
			if (k[i] == kk) return i;
			//if (table[i].first == kk) return i;
		}
		return 0;
	}

	KVList& replace(int i, const K& kk, const V& vv)
	{
		if (i >= 0 && i < count) {
			k[i] = kk;
			v[i] = vv;
		}

		return *this;
	}

};
