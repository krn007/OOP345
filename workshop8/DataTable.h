#pragma once

#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <fstream>
#include <cmath>

namespace w8
{
	template<class T>
	class DataTable
	{
		int wid;
		int dec;
		std::vector<T> x, y;

	public:
		DataTable(std::ifstream& is, int width, int decimals) : wid(width), dec(decimals)
		{
			while (is.good())
			{
				std::string line;
				std::getline(is, line);

				std::stringstream ss;

				if (!line.empty())
				{
					ss.str(line);

					T fx, fy;
					ss >> fx >> fy;

					x.push_back(fx);
					y.push_back(fy);
				}
			}
		}

		T mean() const
		{
			T yTot = std::accumulate(y.begin(), y.end(), 0.0);
			return yTot / y.size();
		}

		T sigma()
		{
			T meanVal = mean(), sumDeviation = 0.0;

			for (int i = 0; i < y.size(); i++) {
				sumDeviation += (y[i] - meanVal) * (y[i] - meanVal);
			}

			return std::sqrt(sumDeviation / y.size());
		}

		T median() const
		{
			std::vector <T> copy = y;

			std::sort(copy.begin(), copy.end());
			T median = copy[copy.size() / 2];

			return median;
		}

		void regression(T& slope, T& y_intercept) const
		{
			T avgX = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
			T avgY = std::accumulate(y.begin(), y.end(), 0.0) / y.size();

			T numer = 0.0, denom = 0.0;

			for (int i = 0; i < x.size(); ++i)
			{
				numer += (x[i] - avgX) * (y[i] - avgY);
				denom += (x[i] - avgX) * (x[i] - avgX);
			}

			slope = numer / denom;
			y_intercept = avgY - (slope * avgX);
		}

		void display(std::ostream& os) const
		{
			os << std::setw(wid) << "x" << std::setw(wid) << "y" << std::endl;

			for (int i = 0; i < x.size(); i++) {
				os << std::setw(wid) << std::fixed << std::setprecision(dec) << x[i]
					<< std::setw(wid) << std::fixed << std::setprecision(dec) << y[i] << std::endl;
			}
		}
	};

	template<class T>
	std::ostream& operator<<(std::ostream& os, const DataTable<T>& dt)
	{
		dt.display(os);
		return os;
	}
}
