#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"
#include "POS.h"
namespace sict{

  void Date::set(){
    time_t t = time(NULL);
    tm lt = *localtime(&t);
    _day = lt.tm_mday;
    _mon = lt.tm_mon + 1;
    _year = lt.tm_year + 1900;
    if (dateOnly()){
      _hour = _min = 0;
    }
    else{
      _hour = lt.tm_hour;
      _min = lt.tm_min;
    }
  }

  int Date::value()const{
    return _year * 535680 + _mon * 44640 + _day * 1440 + _hour * 60 + _min;
  }


  int Date::mdays()const{
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = _mon >= 1 && _mon <= 12 ? _mon : 13;
    mon--;
    return days[mon] + int((mon == 1)*((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0));
  }

  int Date::errCode()const {
	  return _readErrorCode;
  }
  void Date::errCode(int errorCode) {
	  _readErrorCode = errorCode;
  }
  bool Date::bad()const {
	  if (errCode() == 0)
		  return false;
	  else
		  return true;

  }
  bool Date::dateOnly()const {
	  return _dateOnly;

  }
  void Date::dateOnly(bool v) {
	  _dateOnly = v;
  }
  void Date::set(int year, int month, int day, int hour=0, int min=0) {
	  _readErrorCode = 0;
	  //test valiity for years
	  if (year >= MIN_YEAR && year <= MAX_YEAR) 
		  _year = year;
	  else
		  errCode(2);
	  
	  //for months
	  if (month > 0 && month < 13)
		  _mon = month;
	  else
		  errCode(3);
	  //for days
	  if (day>0&&day<=mdays()) 
			  _day = day;
		  else
			  errCode(4);
	  
	  //for hours
	  if (hour >= 0 && hour < 24)
		  _hour = hour;
	  else
		  errCode(5);
	  //for min
	  if (min >= 0 && min < 60)
		  _min = min;
	  else
		  errCode(6);

	  //return no problems

	  _year = year;
	  _mon = month;
	  _day = day;
	  _hour = hour;
	  _min = min;
	  if (_readErrorCode==0)
	  errCode(0);

  }

  Date::Date() {
	  _dateOnly = 0;
	  set();
  }
  Date::Date(int year, int month, int day) {
	  _dateOnly = 1;
	  set(year, month, day, 0, 0);

  }

  Date::Date(int year, int month, int day, int hour, int min ) {
	  _dateOnly = 0;

	  set(year, month, day, hour, min);

  }


  bool Date::operator==(const Date& D)const {
	  if (value() == D.value())
		  return true;
	  else
		  return false;
  }
  bool Date::operator!=(const Date& D)const {
	  if (value() == D.value())
		  return false;
	  else
		  return true;
  }

  bool Date::operator<(const Date& D)const {
	  if (value() < D.value())
		  return true;
	  else
		  return  false;
  }

  bool Date::operator>(const Date& D)const {
	  if (*this < D)
		  return false;
	  else
		  return true;
  }

  bool Date::operator<=(const Date& D)const {
	  if (value() <= D.value())
		  return true;
	  else
		  return  false;
  }

  bool Date::operator>=(const Date& D)const {
	  if (*this < D)
		  return false;
	  else
		  return true;
  }

  //reads in date as either YYYY/MM/DD, HH:MM or just YYYY/MM/DD
  std::istream& Date::read(std::istream& is = std::cin) {
	  int year ;
	  int month = 0;
	  int hour = 0;
	  int day = 0;
	  int min = 0;
	  if (_dateOnly == true) {
		  is >> year;
		  is.ignore(2000, '/');
		  is >> month;
		  is.ignore(2000, '/');
		  is >> day;
	  }
	  else {
		  is >> year;
		  is.ignore(2000, '/');
		  is >> month;
		  is.ignore(2000, '/');
		  is >> day;
		  is.ignore(2000, ',');
		  is >> hour;
		  is.ignore(2000, ':');
		  is >> min;
	  }
	  if (cin.fail())
		  errCode(1);
	  else {
		  set(year, month, day, hour, min);
	  }

	  return is;
  }
  //writes date as either YYYY/MM/DD, HH:MM or just YYYY/MM/DD
  std::ostream& Date::write(std::ostream& ostr = std::cout)const {
	  if (_dateOnly == true){
		  cout.setf(ios::right);
		  ostr << _year << "/";
		  cout.fill('0');
		  cout.width(2);
		  ostr << _mon << "/";
		  cout.width(2);
		  ostr << _day ;
		  cout.fill(' ');
		  cout.setf(ios::left);
	  }
	  else {
		  cout.setf(ios::right);
		  ostr << _year << "/";
		  cout.fill('0');
		  cout.width(2);
		  ostr << _mon << "/";
		  cout.width(2);
		  ostr << _day << ", ";
		  cout.width(2);
		  ostr << _hour << ":";
		  cout.width(2);
		  ostr << _min;
		  cout.fill(' ');
		  cout.setf(ios::left);
	  }

	  return ostr;
  }

  std::ostream& operator<<(std::ostream& os, const Date& d) {
	  d.write(os);
	  return os;
  }

  std::istream& operator>>(std::istream& is, Date& d) {
	  d.read(is);
	  return is;
  }
}
