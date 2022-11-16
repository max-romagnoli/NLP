/******** TranslationDictionary.h ************************/
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

struct Transpair {
  string french;
  string english;
};

class Trans_Dict {

private:
  vector<Transpair> thewords;

public:
  Trans_Dict();      /* constructor */
  Trans_Dict(string file_name);      /* constructor */
  bool opened_ok; 
  bool lookup_french(string word, string& trans);
  bool lookup_english(string word, string& trans);
  bool update(string french, string english);
  void export_to_file(string filename);

};
