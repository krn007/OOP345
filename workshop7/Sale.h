/* OOP345 Workshop 7
Name - Karan Shah
Student_Id: 129965166
Date - 28th Decemeber 2017*/
#ifndef W7_SALE_H
#define W7_SALE_H
#include <vector>
#include "Product.h"
#include"TaxableProduct.h"

namespace w7 {
	class Sale {
		std::vector<iProduct*> products;

	public:
		Sale(const char* file);
		virtual ~Sale();

		void display(std::ostream& os) const;
	};

}
#endif
