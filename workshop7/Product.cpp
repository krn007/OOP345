/* OOP345 Workshop 7
Name - Karan Shah
Student_Id: 129965166
Date - 28th Decemeber 2017*/

#include <iomanip>
#include "Product.h"
#include "TaxableProduct.h"
using namespace std;
namespace w7 {
	iProduct* readProduct(ifstream& in)
	{
		int pn;
		double cost;
		char ts;

		in >> pn;
		if (in.fail())
			return (iProduct*)0;
		in >> cost;
		if (in.fail())
			return (iProduct*)0;

		ts = in.get();
		if (ts != '\n') {
			in >> ts;
			return new TaxableProduct(pn, cost, ts);
		}
		else {
			return new Product(pn, cost);
		}
	}

	Product::Product(int product_number, double cost) {
		product_number_ = product_number;
		cost_ = cost;
	}

	double Product::getCharge() const {
		return cost_;
	}

	void Product::display(std::ostream& os) const
	{
		os << setw(10) << product_number_ << fixed << setprecision(2);
		os << setprecision(2) << setw(10) << cost_;
	}



	std::ostream& operator<<(std::ostream& os, const iProduct& P) {
		P.display(os);
		return os;
	}

}
