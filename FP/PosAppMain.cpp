#include "PosApp.h"
int main(){
  sict::PosApp app("aidapp.txt", "bill.txt");
  app.run();
  return 0;
}