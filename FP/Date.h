// add your information in here, 
// use dateTester.h comments an a template

#ifndef SICT_DATE_H__
#define SICT_DATE_H__
#include <iostream>
namespace sict{


  class Date{
  private:
	  int _year, _mon, _hour, _day, _min, _readErrorCode;
	  bool _dateOnly;
     
	  
	  int value()const;
	  void errCode(int errorCode);
	  void set(int year, int month, int day, int hour, int min);
  public:
	  Date();
	  Date(int year, int month, int day);
	  Date(int year, int month, int day, int hour, int min=0);
    
	  void set();
      int mdays()const;
	  int errCode()const;
	  bool bad()const;
	  bool dateOnly()const;
	  void dateOnly(bool v);



	  bool operator==(const Date& D)const;
	  bool operator!=(const Date& D)const;
	  bool operator<(const Date& D)const;
	  bool operator>(const Date& D)const;
	  bool operator<=(const Date& D)const;
	  bool operator>=(const Date& D)const;

	  std::istream& read(std::istream& is);
	  std::ostream& write(std::ostream& ostr)const;

  };

  std::ostream& operator<<(std::ostream& os, const Date& d);
  std::istream& operator>>(std::istream& is, Date& d); 
  

}
#endif