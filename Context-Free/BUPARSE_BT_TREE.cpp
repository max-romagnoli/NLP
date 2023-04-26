#include "BUPARSE_BT_TREE.h"
#include <iostream>
#include <fstream>

BU_BT_TREE_ITEM::BU_BT_TREE_ITEM() {
  rulecount = 0;
  progress = 0;
  postorder_size = 0;  
}

BU_BT_TREE_ITEM::~BU_BT_TREE_ITEM() {

}


BUPARSE_BT_TREE::BUPARSE_BT_TREE(string grammar): BUPARSE(grammar) {
  backtrack_debug = 0;
  use_dot = 0;
  tree_ptr = 0;
}

BUPARSE_BT_TREE::BUPARSE_BT_TREE(){
  backtrack_debug = 0;
  use_dot = 0;
  tree_ptr = 0;
}

void BUPARSE_BT_TREE::initialize_bt(){
  history.clear();
}

void BUPARSE_BT_TREE::initialize_postorder(){
  postorder.clear();
}

void BUPARSE_BT_TREE::display_config_bt(){
  int i;
  if (backtrack_debug == 1){
    i = history.size()-1;
    cout << "BACKTRACKING to use of rule: ";
    g.rules[history[i].rulecount].print();
    cout << i << " STACK: "; 
    history[i].pda.print();

    cout << " WORDS: ";
    for(unsigned int j = history[i].progress; j < input.size(); j++) {
      cout << input[j] << ' ';
    }
    cout << endl;

  }
}

void BUPARSE_BT_TREE::extend_history(unsigned int i) {
  BU_BT_TREE_ITEM b;
  b.pda = pda;
  b.progress = progress;
  /* record rule number about to be used */
  b.rulecount = i;
  b.postorder_size = postorder.size();
  history.push_back(b);

}

void BUPARSE_BT_TREE::reset_from_history(void) {
  BU_BT_TREE_ITEM b;
  display_config_bt();
  b = history.back();
  rulecount = b.rulecount + 1;
  pda = b.pda;
  progress = b.progress;
  postorder.resize(b.postorder_size);
  history.pop_back();
}


void BUPARSE_BT_TREE::display_postorder() {
  for (unsigned int m = 0; m < postorder.size(); m++) {
   postorder[m].print();
  }

//   for(unsigned int i = 0; i < postorder.size(); i++) {
//     postorder[i].mother.print();
//     cout << ' ' << postorder[i].dtrs.size();
//   }
//   cout << endl;

}

/* each member of postorder corresponds to push onto the stack    */
/* for non-terminals this is preceded bu pops of dtrs             */
/* so interpreting the postorder    this way, pop and push from a  */
/* stack of trees starting with an empty stack                    */
/* you could do this in the parse method itself and work all      */
/* the time with a stack of trees, but under backtracking         */
/* would have to ensure that trees allocated down a blind alley   */
/* doing the tree allocation once the parse is completed is       */
/* to program                                                     */

Tree * BUPARSE_BT_TREE::build_tree() {
  // this clears most recently built tree, if any
  if(tree_ptr != 0) {
    delete tree_ptr;
  }

  vector<Tree *> tree_stack;
  Tree *t_ptr, *dtr_ptr;

  Rule r; // use to track thry postorder
          // note for parts of postorder corresponding to words
          // the 'Rule' will be somewhat fake: [w] --> []

  for(unsigned int i = 0; i < postorder.size(); i++) {
    r = postorder[i];

    t_ptr = new Tree(r.mother);
    unsigned arity;
    arity = r.dtrs.size();
    // fetches first dtr, then second etc, which are buried successively
    // less deeply in the tree_stack
    for(unsigned int j = tree_stack.size()-arity; j < tree_stack.size() ; j++) {
      dtr_ptr = tree_stack[j];
      t_ptr->dtrs.push_back(dtr_ptr);
    }

    // now pop dtr nodes
    for(unsigned int k = 0; k < arity ; k++) {
      tree_stack.pop_back();
    }
    tree_stack.push_back(t_ptr);

  }


  t_ptr = tree_stack.back();
  tree_stack.pop_back();
  return t_ptr;

}

/* if do_all == 1 does all analyses */
/* otherwise does one analysis                  */
int BUPARSE_BT_TREE::parse_all(vector<string> key, bool do_all) {

  input = key;
  initialize();
  initialize_bt();
  initialize_postorder();
  int how_many = 0;
  bool more_solutions = false;

  do {
    if(parse_one() == true) {
      how_many++;
      tree_ptr = build_tree(); 
      tree_ptr->drawtree();
      if(use_dot == 1) {
	tree_ptr->dot_tree();
      }
      // delete tree_ptr; now done in build_tree

      if (do_all == false) {
	break;
      }
  
      if(history.size() > 0) {
	more_solutions = true;
        reset_from_history();
      }
      else {
	more_solutions = false;
      }
    }
    else {
      break;
    }
  
  } while(more_solutions);

  return how_many;
}

bool BUPARSE_BT_TREE::parse_one() {

  bool accept;
  int type = 0;
  int backtracking = 0;
  Rule r;
  Rule ppart;  
  Category c;

  do {
    while(move(type)) { 
      if (type == 1) { // REDUCE 
	r = g.rules[rulecount];

	// record choice point
	extend_history(rulecount);

	// record parse step
	ppart = r;
	postorder.push_back(ppart);

	// update stack
	for (int j = r.dtrs.size(); j > 0; j--) {
	  pda.pop();
	}  /* pop dtrs */
	pda.push(r.mother); /* push mother */
	rulecount = 0;

	display_config();
      }
      else if(type == 2) { // SHIFT
          
	c.cat = input[progress];
	c.terminal = true;

	// record parse step
	ppart.mother = c;
	ppart.dtrs.clear();
	postorder.push_back(ppart);

	// update stack
	pda.push(c);
	progress++;
        rulecount=0;
	display_config();
      }
    } // end of moves loop

    // accept, backtrack or fail
    if (final_config() == true) {
      accept = true;
      break;
    }      
    else if (history.size() > 0) {
      reset_from_history();
      backtracking = 1;
    }
    else {
      backtracking = 0;
      accept = false;
    }
  }   while(backtracking == 1);


  return accept;
}

bool BUPARSE_BT_TREE::move(int& type) {
  Rule r;

  // check for reduction
  for(unsigned int j = rulecount; j < g.nrules; j++) {
	r = g.rules[j];
    
	if (pda.top_match(r.dtrs)) {
        rulecount = j;
        type = 1;
        return true;
	}
  }

  // check for shift
  if(progress < input.size()){
    type = 2;
    return true;
  }

  return false;
}


