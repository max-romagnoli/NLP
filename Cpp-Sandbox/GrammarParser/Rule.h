#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

class Rule {

private:

public:
  string mother;
  vector<string> daughters;
  Rule();
  Rule(string input);
  string rule_as_string;
  void show();

};
