#include "TDPARSE.h"
#include "trees.h"
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

#if !defined BT_TREE_ITEM_h
#define BT_TREE_ITEM_h

class BT_TREE_ITEM {
 public:
  BT_TREE_ITEM(void);
  ~BT_TREE_ITEM(void);
  PDA pda; 
  unsigned int rulecount;
  unsigned int progress;
  unsigned int preorder_size;
};

#endif

#if (!defined TDPARSE_BT_TREE_H)
#define TDPARSE_BT_TREE_H

class TDPARSE_BT_TREE : public TDPARSE {
public: 
 TDPARSE_BT_TREE(string grammar);
 TDPARSE_BT_TREE(void);

 /* PARSING */
 int parse_all(vector<string> key, bool do_all); 
 bool parse_one(void); 

 bool move(int& type);
 // unsigned int rulecount; inheritted
 /* BACKTRACKING */
 vector<BT_TREE_ITEM> history; /* choice points */
 void extend_history(unsigned int rulecount);
 void initialize_bt(void);
 void display_config_bt(void);
 int backtrack_debug;

 /* RECORDING PARSE */
 vector<Rule> preorder; /* rules used */
 void initialize_preorder(void);
 void display_preorder(void);
 Tree *build_tree(void);
 int use_dot;

 /* INHERITTED STUFF */
 // Grammar g; 
 // PDA pda; 
 // int progress; inheritted
 // vector<string> input; 



};

#endif
