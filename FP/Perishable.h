#ifndef SICT_NONPERISHABLE_H_
#define SICT_NONPERISHABLE_H

#include "Item.h"
#include "ErrorMessage.h"
#include "Date.h"


namespace sict {

	class Perishable :public Item {
		ErrorMessage _err;
		Date _expiry;

	public:
		Perishable();
		const Date& expiry()const;
		void expiry(const Date &value);
		bool isEmpty()const;
		

		std::fstream& save(std::fstream& file)const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear)const;
		std::istream& read(std::istream& is);
	};


}


#endif