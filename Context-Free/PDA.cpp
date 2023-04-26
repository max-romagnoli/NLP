/* implementation stack on top of vector class */
#include "PDA.h"
#include <iostream>

PDA::PDA() {
  pda.clear();
  print_top_at_left = true;
#if DEBUG 
  cout << "calling PDA constructor\n";
#endif

}

PDA::~PDA(){
#if DEBUG 
  cout << "calling PDA destructor\n";
#endif
}


/*! adds to the top of stack */
void PDA::push(Category x) { /* use push_back method of vector */
  pda.push_back(x);
}

/*! removes the top of the stack and returns it */
Category PDA::pop() { /* use back and pop_back method of vector */
  Category c;
  c = pda.back();
  pda.pop_back();
  return c;
}


/*! verifies that the stack is empty */
bool PDA::is_empty() {
  return pda.empty();
}

/*! returns the top of the stack without removing it */
Category PDA::top() { 
   return pda.back();

}

/*! displays the contents left to write or right to left 
 * according to print_top_at_left
 */ 
void PDA::print() {
  if(print_top_at_left) {
    for (int i = pda.size(); i > 0; i--) {
      pda[i-1].print();
      cout << ' ';
    }
    cout << endl;
  }
  else {
    for (unsigned int i = 0; i < pda.size(); i++) {
      pda[i].print();
      cout << ' ';
    }

  }
}

/*! used by shift/reduce parser, cats will be the dtrs of syntax rule
 * checks that top elements of stack corresponds to dtrs in reverse 
 * order
 *
 * so last dtr is top of stack etc
 */
bool PDA::top_match(vector<Category> cats) {
  int n = pda.size();
  bool match = true;   /* 1 if cats matches top of PDA */
  
  for(int i = cats.size(); i > 0; i--) {
    if (n == 0) {
      match = false;
      break;
    }
    else if(are_equal(pda[n-1],cats[i-1])) {
      n--;
      continue;
    }
    else {
      match = false;
      break;
    }
  }

  return match;
}


int PDA::size() {
return pda.size();
}






