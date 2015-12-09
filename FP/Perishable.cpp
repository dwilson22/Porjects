#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>
#include "Item.h"
#include "ErrorMessage.h"
#include "Perishable.h"

using namespace sict;
using namespace std;
//constructor that sets date only to true
Perishable::Perishable() {
	_expiry.dateOnly(true);
}
//returns a const date reference
const Date& Perishable::expiry()const {
	const Date& a = _expiry;
	return  a;
}
//sets _expiry to value sent
void Perishable::expiry(const Date &value) {
	_expiry = value;
}

std::fstream& Perishable::save(std::fstream& file)const {
	file << "P," << sku() << "," << name() << "," << price() << "," << taxed() << ","
		<< quantity()<<"," << _expiry<< endl;
	return file;
}
//loads from a file in the form X,sku,name,price,taxed,quantity,date

std::fstream& Perishable::load(std::fstream& file) {
	double p=0.0;
	int q=0;
	bool t=false;
	char n[200];
	char s[MAX_SKU_LEN + 1];

	file.getline(s, MAX_SKU_LEN, ',');
	file.getline(n, 200, ',');
	file >> p;
	file.ignore(20,',');
	file >> t;
	file.ignore(20,',');
	file >> q;
	file.ignore(20, ',');
	_expiry.read(file);



	sku(s);
	name(n);
	price(p);
	taxed(t);
	quantity(q);

	return file;

}
//writes either linearly (one line) if true or in a "form", mulitple lines
std::ostream& Perishable::write(std::ostream& os, bool linear)const {
	if (_err.isClear()) {
		if (linear == true) {
			
			os.setf(ios::left);
			os.width(MAX_SKU_LEN);
			os << sku() << "|";
			os.width(20);
			char n[20];
			strncpy(n, name(), 20);
			n[strlen(name()) + 1] = '\0';
			os << n << "|";
			os.setf(ios::right);
			os.width(7);
			os.setf(ios::fixed);
			os.precision(2);
			os << price() << "|";
			if (taxed())
				os << " tp";
			else
				os << "  p";
			os << "|";
			os.width(4);
			os << quantity() << "|";
			os.width(9);
			os << cost()*quantity() << "|";

			os.precision(6);
			os.unsetf(ios::fixed);
			os.unsetf(ios::right);

		}
		else {
			os << "Name:" << endl;
			os << name() << endl;
			os << "Sku: " << sku() << endl;
			os.setf(ios::fixed);
			os.precision(2);
			os << "Price: " << price() << endl;
			if (taxed())
				os << "Price after tax: " << cost() << endl;
			else
				os << "Price after tax: N/A" << endl;
			os << "Quantity: " << quantity() << endl;
			os << "Total Cost: " << cost()*quantity() << endl;
			os.precision(6);
			os << "Expiry date: ";
			_expiry.write(os);
			os << endl;
			os.precision(6);
			os.unsetf(ios::fixed);
		}
	}
	else
		os<<_err;
	return os;
}
std::istream& Perishable::read(std::istream& is) {
	double p;
	int q;
	char t;
	char n[200];
	char s[MAX_SKU_LEN + 1];


	cout << "Perishable Item Entry: " << endl;
	cout << "Sku: ";
	is.getline(s, MAX_SKU_LEN, '\n');
	
	cout << "Name:"<<endl;
	is.getline(n, 200, '\n');
	//nested if to test each input valididty, if it fails passes error msg out
	cout << "Price: ";
	if (is >> p) {
		price(p);
		cout << "Taxed: ";
		if (is >> t && (t == 'y' || t == 'Y' || t == 'n' || t == 'N')) {
			(t == 'y' || t == 'Y') ? taxed(true) : taxed(false);
			cout << "Quantity: ";
			if (is >> q) {
				quantity(q);
				cout << "Expiry date (YYYY/MM/DD) : ";

				if (!_expiry.read(is)) {
					if (_expiry.errCode() == 1)
						_err.message("Invalid Date Entry");
					
				}
				if (_expiry.errCode() == 2) {
					_err.message("Invalid Year in Date Entry");
					is.setstate(ios::failbit);
				}
				if (_expiry.errCode() == 3) {
					_err.message("Invalid Month in Date Entry");
					is.setstate(ios::failbit);
				}
				if (_expiry.errCode() == 4) {
					_err.message("Invalid Day in Date Entry");
					is.setstate(ios::failbit);
				}

			}
			else
				_err.message("Invalid Quantity Entry");
		}
		else {
			_err.message("Invalid Taxed Entry, (y)es or (n)o");
			is.setstate(ios::failbit);
		}
	}
	else
		_err.message("Invalid Price Entry");

	
	if (quantity() != 0&&_expiry.errCode()==0) {
		sku(s);
		name(n);
		_err.clear();
	}
	else
		setEmpty();

	return is;

}

bool Perishable::isEmpty() const {

	return (sku() == '\0' && _err.message() == '\0');
}

