#ifndef SICT_NONPERISHABLE_H_
#define SICT_NONPERISHABLE_H

#include "Item.h"
#include "ErrorMessage.h"


namespace sict {

	class NonPerishable :public Item {
		ErrorMessage _err;

		public:
			std::fstream& save(std::fstream& file)const;
			std::fstream& load(std::fstream& file);
			std::ostream& write(std::ostream& os, bool linear)const;
			std::istream& read(std::istream& is);
			bool isEmpty()const;

	};


}


#endif