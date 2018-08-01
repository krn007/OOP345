#include <iomanip>
#include "TaxableProduct.h"
using namespace std;
namespace w7 {
	TaxableProduct::TaxableProduct(int product_number, double cost, char taxable_status) :Product(product_number, cost)
	{
		taxable_status_ = taxable_status;
	}

	double TaxableProduct::getCharge() const {
		double charge = Product::getCharge();
		(taxable_status_ == 'H') ? charge *= 1.13 : charge *= 1.08;
		return charge;
	}

	void TaxableProduct::display(std::ostream& os) const {
		Product::display(os);
		os << ' ';
		(taxable_status_ == 'H') ? os << "HST" : os << "PST";
	}

}