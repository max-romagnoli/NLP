#include "Rule.h"
#include <vector>

using namespace std;

class Grammar {

 private:
  int nrules = 0;

 public:
  Grammar();
  Grammar(string filename);
  vector<Rule> rules;
  void show();
  void show_with_ndtrs(int ndtrs);

};
