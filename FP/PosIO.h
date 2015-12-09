#pragma once
#ifndef SICT_POSIO_H_
#define  SICT_POSIO_H_
#include <iostream>
#include <fstream>
namespace sict {

	class PosIO {
	public:
		virtual std::fstream& save(std::fstream& file)const = 0;
		virtual std::fstream& load(std::fstream& file) = 0;
		virtual std::ostream& write(std::ostream& os, bool linear)const = 0;
		virtual std::istream& read(std::istream& is) = 0;
	};
}



#endif