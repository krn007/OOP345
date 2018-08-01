#ifndef W7_TAXABLEPRODUCT_H
#define W7_TAXABLEPRODUCT_H
#include "Product.h"
#include "iProduct.h"
using namespace std;
namespace w7 {
	class TaxableProduct : public Product {
		char taxable_status_;
	public:
		TaxableProduct(int product_number, double cost, char taxable_status);
		virtual double getCharge() const;
		virtual void display(std::ostream& os) const;
	};
}


#endif