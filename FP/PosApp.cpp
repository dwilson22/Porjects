#include <cstring>
#include <iomanip>
#include <fstream>
#include <ctime>
#include "PosApp.h"
#include "Item.h"
using namespace std;
namespace sict{

	//constructor
	PosApp::PosApp(const char* filename, const char* billfname) {
		strncpy(_filename, filename, 128);
		_filename[strlen(filename) + 1] = '\0';
		strncpy(_billfname, billfname, 128);
		_billfname[strlen(billfname) + 1] = '\0';
		_noOfItems = 0;
		_items[0] = '\0';
	}

	int PosApp::menu() {
		int quit=-1;

			cout << "The OOPs Store" << endl << "1- List items" << endl << "2- Add Perishable item"
				<< endl << "3- Add Non-Perishable item" << endl << "4- Update item quantity"
				<< endl << "5- Show Item" << endl << "6- POS" << endl << "0- exit program" << endl
				<< "> ";
			    
				cin >> quit;
				cin.ignore(2000, '\n');
				cout << endl;
				if (quit > 6 || quit < 0)
					quit = -1;
				return quit;
				
			
		
	}

	void PosApp::loadRecs() {
		_noOfItems = 0;
		fstream fin;
		fin.open(_filename,ios::in);
		if (fin.is_open()) {
			Item* readIndex[MAX_NO_ITEMS];
			char per;
			int i=0;
			readIndex[0] = nullptr;
			while (fin.good()) {
				fin >> per;
				if (fin.good()) {
					if (per == 'P') {
						readIndex[i] = new Perishable;
					}
					else if (per == 'N') {
						readIndex[i] = new NonPerishable;
					}
					fin.ignore(20, ',');
					readIndex[i]->load(fin);
					
					i++;
					_noOfItems = i;
				}
			}
			for (int n = 0; n < _noOfItems; n++)
				*_items[n] = *readIndex[n];
			
			fin.close();
			}
		else {
			fin.clear();
			fin.close();
			fin.open(_filename, ios::out);
			fin.close();
		}
	}

	void PosApp::saveRecs() {
		fstream fout;
		fout.open(_filename,ios::out);
		if (_noOfItems != 0) {
			for (int i = 0; i < _noOfItems; i++) {
				_items[i]->save(fout);
			}
		}
		fout.close();
		loadRecs();
	}
	int PosApp::searchItems(const char* sku)const {
		int found = -1;
		for (int i = 0; i < _noOfItems; i++){
	
			if (*_items[i] == sku)
				found = i;
		}

		return found;
	}
	void PosApp::updateQty() {
		char _sku[MAX_SKU_LEN + 1];
		int item;
		int qty;
		cout << "Please enter the sku: ";
		cin.getline(_sku, MAX_SKU_LEN);
		_sku[strlen(_sku) + 1] = '\0';
		item = searchItems(_sku);
		if (item != -1) {
			_items[item]->write(cout,false);
			cout << "Please enter the number of purchased items: ";
			cin >> qty;
			*_items[item]+=qty;
			saveRecs();
			cout << "Updated!";
		}
		else {
			cout << "Not found!";
		}

	}

	void PosApp::addItem(bool ip) {
		if (ip == true) {
			Item* temp = new Perishable;
			temp->read(cin);
			if (cin.fail()) {
				cin.clear();
				cin.ignore(2000, '\n');
				cout << *temp<<endl;
				delete temp;
			}
			else {
				_items[_noOfItems] = new Perishable;
				
				*_items[_noOfItems] = *temp;
			
				
				
				_noOfItems++;
				saveRecs();
				cout << "Item added."<<endl;
				temp=nullptr;
		
			}
		}
		else if (ip==false){
			Item* temp = new NonPerishable;
			temp->read(cin);
			if (cin.fail()) {
				cin.clear();
				cin.ignore(2000, '\n');
				cout << *temp<<endl;
				delete temp;
			}
			else {

				_items[_noOfItems] = new NonPerishable;
				*_items[_noOfItems] = *temp;
				_noOfItems++;
				saveRecs();
				cout << "Item added."<<endl;
				temp=nullptr;
			}
		}
	}

	void PosApp::listItems()const {
		double total=0.0;
		cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total |";
		cout << endl << "-----|--------|--------------------|-------|---|----|---------|"<<endl;
		//display date and time as YYYY/MM/DD, HH:MM
		for (int i = 0; i < _noOfItems; i++) {
			cout << endl;
			cout.setf(ios::right);
			cout.width(4);
			//displays the row and each item linearly adds the total to be displayed at the end
			cout << i+1;
			cout.unsetf(ios::right);
			cout<<" | "<<*_items[i];
			total += (_items[i]->cost()*_items[i]->quantity());
		}
		cout <<endl<< "-----^--------^--------------------^-------^---^----^---------^";
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << endl << "Total Asset: " << total << endl;
		cout.precision(6);
		cout.unsetf(ios::fixed);
	}
	void PosApp::showBill() {
		double total = 0.0;
		fstream fb;
		fb.open(_billfname, ios::in);
		if (fb.is_open()) {
			Item* readIndex[MAX_NO_ITEMS];
			char per;
			int i = 0;
			readIndex[0] = nullptr;
			while (fb.good()) {
				

				fb >> per;
				if (fb.good()) {
					if (per == 'P') {
						readIndex[i] = new Perishable;
					}
					else if (per == 'N') {
						readIndex[i] = new NonPerishable;
					}
					fb.ignore(20, ',');
					readIndex[i]->load(fb);
					i++;	
				}
			}
			cout << "v--------------------------------------------------------v" << endl;
			time_t t = time(0);   // get time now
			struct tm * now = localtime(&t);
			cout << "| "
				<< (now->tm_year + 1900) << "/"
				<< (now->tm_mon + 1) << "/"
				<< now->tm_mday << ", "
				<< now->tm_hour << ":" << now->tm_min << "                                        |";
			//iterate through each item to be displayed linearly
			for (int n = 0; n < i; n++) {
				cout << endl <<"| "<< *readIndex[n];
				total += readIndex[n]->cost();
			}
			cout <<endl<< "^--------^--------------------^-------^---^----^---------^";
			cout.setf(ios::fixed);
			cout.precision(2);
			cout << endl << "Total $"<<total<<endl;
			cout.precision(6);
			cout.unsetf(ios::fixed);
			fb.close();
			fb.open(_billfname, ios::out|ios::trunc);
			fb.close();
		}
		else {
			fb.clear();
			fb.close();
			fb.open(_billfname, ios::out);
			fb.close();
		}
	}

	void PosApp::addToBill(Item& I) {
		int qty = I.quantity();
		I.quantity(1);
		fstream fb;
		fb.open(_billfname, ios::out|ios::app);
		if (!fb.is_open()) {
			fb.clear();
			fb.close();
			fb.open(_billfname, ios::out);
		}

		I.save(fb);
		qty--;
		I.quantity(qty);
		saveRecs();
		fb.close();
	}

	void PosApp::POS() {
		char sku[MAX_SKU_LEN];

		while (sku[0] != '\0') {
			cout << "Sku: ";
			cin.getline(sku, MAX_SKU_LEN, '\n');
			sku[strlen(sku) + 1] = '\n';
			//if item is found display name and add to bill file
			if (searchItems(sku) != -1) {
				cout << "v------------------->" << endl;
				cout<< _items[searchItems(sku)]->name()<<endl;
				addToBill(*_items[searchItems(sku)]);
				cout << "^------------------->" << endl;
			}
			else {
				cout << "Not Found!" << endl;
			}
		}

		showBill();
	}

	void PosApp::run() {
		int quit=-1;

		while (quit != 0) {
			quit = menu();
			switch (quit) {
			case 0:
				cout << "Goodbye!";
				break;
			case 1:
				
				listItems();
				break;
			case 2:
				
				addItem(true);
				
				break;
			case 3:
				
				addItem(false);
				
				break;
			case 4:
				
				updateQty();
				
				break;
			case 5:
				
				char sku[MAX_SKU_LEN + 1];
				cout << "Please enter the SKU: ";
				cin.getline(sku, MAX_SKU_LEN);
				sku[strlen(sku) + 1] = '\0';
				if (searchItems(sku) != -1) {
					cout << "v-----------------------------------v";
					_items[searchItems(sku)]->write(cout, false);
					cout<<"^-----------------------------------^" << endl;
				}
				else
					cout << "Not Found!" << endl;
				
				break;
			case 6:
				
				POS();
				
				break;
			default:
				cout << "===Invalid Selection, try again===";
				cout << endl;
				quit = -1;
				break;
			}
		} 
	}
}
