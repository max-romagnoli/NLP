#include "Rule.h"
#include <iostream>

Rule::Rule() {}

Rule::Rule(string input) {

  rule_as_string = input;

  size_t i,start,len;
  string daughter;
  i = rule_as_string.find(" --> ");
  start = i+5;
  len = i;
  mother = rule_as_string.substr(0,len);  // set mother

  while((i = rule_as_string.find(",", start)) != string::npos) {  // set daughters
    len = i-start;
    daughter = rule_as_string.substr(start,len);
    daughters.push_back(daughter);
    start = i+1;
  }
  daughter = rule_as_string.substr(start);
  daughters.push_back(daughter);
  
}

void Rule::show() {
  cout << mother << " --> " << endl;
  for (string daught : daughters) {
    cout << "     " << daught << endl;
  }
}
