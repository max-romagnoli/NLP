#include "Grammar.h"
#include <iostream>
#include <fstream>

Grammar::Grammar(){}

Grammar::Grammar(string fname) {

  ifstream file;
  file.open(fname);

  string line;
  while(getline(file,line)) {
    Rule r(line);
    rules.push_back(r);
    nrules++;
  }    

}

void Grammar::show() {
  cout << "number of rules was " << nrules << endl;
  for(Rule r : rules) {
    r.show();
  }
}

void Grammar::show_with_ndtrs(int ndtrs) {
  int relevant_rules = 0;
  cout << "the total number of rules was " << nrules << endl;
  for(Rule r : rules) {
    if(r.daughters.size() == ndtrs) {
      r.show();
      relevant_rules++;
    }
  }
  cout << "there were " << relevant_rules << " rules with " << ndtrs << " dtrs\n";
}
      
