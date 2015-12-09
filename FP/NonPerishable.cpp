#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>
#include "Item.h"
#include "ErrorMessage.h"
#include "NonPerishable.h"

using namespace sict;
using namespace std;

std::fstream& NonPerishable::save(std::fstream& file)const {
	file << "N," << sku() << "," << name() << "," << price() << "," << taxed() << ","
		<< quantity() << endl; 
	return file;
}
//loads from a file in the form X,sku,name,price,taxed,quantity
std::fstream& NonPerishable::load(std::fstream& file) {
	double p=0.00;
	int q=0;
	bool t=true;
	char n[200];
	char s[MAX_SKU_LEN + 1];

	file.getline(s, MAX_SKU_LEN, ',');
	file.getline(n, 200, ',');
    file >> p;
	file.ignore(20,',');
	file >> t;
	file.ignore(20,',');
	file >> q;

	

	sku(s);
	name(n);
	price(p);
	taxed(t);
	quantity(q);

	return file;

}
//writes either linearly (one line) if true or in a "form", mulitple lines

std::ostream& NonPerishable::write(std::ostream& os, bool linear)const {
	
	if (_err.isClear()) {
		if (linear == true) {
			
			os.setf(ios::left);
			os.width(MAX_SKU_LEN);
			os << sku() << "|";
			os.width(20);
			char n[20];
			strncpy(n, name(), 20);
			n[strlen(name())+1] = '\0';
			os.setf(ios::left);
			os << n << "|";
			os.setf(ios::right);
			os.width(7);
			os.setf(ios::fixed);
			os.precision(2);
			os << price() << "|";
			if (taxed())
				os << " t ";
			else
				os << "   ";
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
			os.unsetf(ios::fixed);
		}
	}
	else {
		os << _err.message();
	}

	return os;
}
std::istream& NonPerishable::read(std::istream& is) {
	double p;
	int q;
	char t;
	char n[200];
	char s[MAX_SKU_LEN + 1];
	

	cout << "NonPerishable Item Entry:" << endl;
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
			if (is >> q) 
				quantity(q);
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


	
	
	if (quantity() != 0) {
		sku(s);
		name(n);
		_err.clear();
	}
	else
		setEmpty();

	return is;

}
bool NonPerishable::isEmpty() const {

	return (sku() == '\0' && _err.message()== 0);
}