#include "BUPARSE.h"
#include "trees.h"
#include <string>
#include <vector>

using namespace std;


#if !defined BU_BT_TREE_ITEM_h
#define BU_BT_TREE_ITEM_h

class BU_BT_TREE_ITEM {
 public:
  BU_BT_TREE_ITEM(void); // done this
  ~BU_BT_TREE_ITEM(void); // done this
  PDA pda; 
  unsigned int rulecount;
  unsigned int progress;
  unsigned int postorder_size;
};

#endif

#if !(defined BUPARSE_BT_TREE_H)
#define BUPARSE_BT_TREE_H

class BUPARSE_BT_TREE : public BUPARSE {
 public: 
  BUPARSE_BT_TREE(string grammar); // done this
  BUPARSE_BT_TREE(void); // done this

  /* PARSING */
  int parse_all(vector<string> key, bool do_all);  // done this
  bool parse_one(void); // done this

  bool move(int& type);
  // unsigned int rulecount; inheritted

  /* BACKTRACKING */
  vector<BU_BT_TREE_ITEM> history;
  void extend_history(unsigned int); // done this
  void initialize_bt(void); // done this
  void reset_from_history(void); 
  void display_config_bt(void); // done this
  int backtrack_debug;
 

  /* RECORDING PARSE */
  vector<Rule> postorder; /* postorder of the parse */
  void initialize_postorder(void);  // done this
  void display_postorder(void); // done this
  Tree *tree_ptr;
  Tree *build_tree(void); // done this
  int use_dot;

  /* INHERITTED STUFF */
  // Grammar g; inheritted
  // PDA pda; inheritted
  // int progress; inheritted
  // vector<string> input; inheritted


};

#endif


