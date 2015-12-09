#ifndef SICT_ITEM_H_
#define SICT_ITEM_H_
#include <iostream>
#include <iomanip>

#include "PosIO.h"
#include "POS.h"


namespace sict {
	class Item :public PosIO {
		//private members
		char _sku[MAX_SKU_LEN + 1];
		char* _name;
		double _price;
		bool _taxed;
		int _quantity;

	public:
		//constructer/destructors
		Item();
		Item(const char* s, const char* n, const double p, bool t=true);
		Item(const Item&);
		virtual ~Item();
		//setters
		void setEmpty();
		void sku(const char* s);
		void name(const char* n);
		void price(const double p);
		void taxed(const bool t);
		void quantity(const int q);
		//getters
		const char* sku() const;
		const char* name() const;
		double price() const;
		bool taxed() const;
		int quantity()const;
		double cost() const;
		virtual bool isEmpty()const;

		//member overloads
		Item& operator=(const Item& a);
		bool operator==(const char* a);
		int operator+=(int a);
		int operator-=(int a);

	
		virtual std::fstream& save(std::fstream& file)const = 0;
		virtual std::fstream& load(std::fstream& file) = 0;
		virtual std::ostream& write(std::ostream& os, bool linear)const = 0;
		virtual std::istream& read(std::istream& is) = 0;
	};

	//non member overloads
	double operator+=(double& d, const Item& b);
	std::ostream& operator<<(std::ostream& os, const Item& b);
	std::istream& operator>>(std::istream& is,  Item& b);
}

#endif