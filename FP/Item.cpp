#include <iostream>
#include <cstring>
#include <string.h>
#include "Item.h"
#include "POS.h"
#include "PosIO.h"

namespace sict {
	
	Item::Item() {
		setEmpty();
	}
	Item::Item(const char* s, const char* n,const double p, bool t) {
		sku(s);
		name(n);
		price(p);
		taxed(t);
		quantity(0);
	}
	Item::Item(const Item& a) {
		*this = a;
	}
	Item::~Item() {
		delete[] _name;
	}
	
	const char* Item::sku() const{
		return _sku;
	}
	const char* Item::name()const {
		return _name;
	}
	double Item::price()const {
		return _price;
	}
	bool Item::taxed()const {
		return _taxed;
	}
	int Item::quantity()const {
		return _quantity;
	}
	double Item::cost() const {
		return (taxed()) ? _price*(1+TAX) : _price;
			}
	bool Item::isEmpty() const {
	
		return (_sku[0] == '\0'|| name() == nullptr);
	}
	
	void  Item::setEmpty() {
		_sku[0]='\0';
		name(nullptr);
		price(0);
		taxed(false);
		quantity(0);
	}
	void Item::sku(const char* s) {
		if (s != '\0') {
			strncpy(_sku, s, MAX_SKU_LEN);
			_sku[strlen(_sku) + 1] = '\0';
		}
	}
	void Item::name(const char* n) {
		_name = nullptr;
		if (n != nullptr) {
			_name = new char[strlen(n) + 1];
			strcpy(_name, n);
		}
	}
	void Item::price(const double p) {
		_price = p;
	}
	void Item::taxed(const bool t) {
		_taxed = t;
	}
	void Item::quantity(const int q) {
		_quantity = q;
	}

	
	Item& Item::operator=(const Item& a) {
		if (this != &a) {
			if (!a.isEmpty()) {
				strncpy(_sku, a._sku, MAX_SKU_LEN);
				_sku[strlen(_sku) + 1] = '\0';
				_name = new char[strlen(a._name) + 1];
				strcpy(_name, a._name);
				_price = a._price;
				_taxed = a._taxed;
				_quantity = a._quantity;

			}
			else {
				setEmpty();
			}
		}
		return *this; 
	}
	bool Item::operator==(const char* a) {
		
		return (!strcmp(_sku, a));
	}
	int Item::operator+=(int a) {
		return _quantity += a;
	}
	int Item::operator-=(int a) {
		return _quantity -= a;
	}


	double operator+=(double& d, const Item& b) {
		d += (b.cost()*b.quantity());
		return d;
	}
	std::ostream& operator<<(std::ostream& os, const Item& b) {
		if(!b.isEmpty())
		 b.write(os, true);
		 return os;
	}
	std::istream& operator>>(std::istream& is, Item& b) {

		 b.read(is);
		 return is;
	}
}