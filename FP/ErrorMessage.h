#ifndef __244_ERRORMESSAGE_H__
#define __244_ERRORMESSAGE_H__
#include <iostream>

class ErrorMessage{
  char _message[81];
public:
  ErrorMessage();
  virtual ~ErrorMessage();
  void clear();
  bool isClear()const;
  void message(const char* value);
  const char* message()const;
};
std::ostream& operator<<(std::ostream& os,const ErrorMessage& M);
#endif

