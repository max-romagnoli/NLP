/*! \file
 * class for a PDA 
 *  principally a stack of categories 
 */

#include <vector>
#include "rules.h"

using namespace std;

#if !defined PDA_H
#define PDA_H

//! to represent a stack of categories to be used by a parser 
class PDA {
public:
  PDA();
  ~PDA();
  void push(Category c);
  Category pop();
  Category top();
  bool is_empty(); 
  void print();
  bool top_match(vector<Category> cats); 
  int size();
  bool print_top_at_left; //!< controls whether printed with top at left (default) or top at right
 private:
  vector<Category> pda;
};

#endif











