#ifndef W7_PRODUCT_H
#define W7_PRODUCT_H
#include "iProduct.h"

namespace w7 {
	class Product : public iProduct {
		int product_number_;
		double cost_;
	public:
		Product(int product_number, double cost);
		virtual double getCharge() const;
		virtual void display(std::ostream& os) const;

	};


}


#endif