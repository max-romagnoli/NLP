#include <string>
#include <vector>
#include "rules.h"

#if !defined CHART_SLASH_h
#define CHART_SLASH_h

class SlashCategory {
 public:
  SlashCategory(void);
  Category result;
  vector<Category> slash; // what is still required
  void set_slash(vector<Category> cats, int offset);
  void print(void);
};


SlashCategory cancel_one(SlashCategory sl);

bool are_equal(SlashCategory p1, SlashCategory p2);


class CHART_SLASH {
public: 
 CHART_SLASH(string grammar);
 CHART_SLASH(void);
 Grammar g; 
 vector<SlashCategory> edges[50][50];
 vector<string> input; 
 bool accept(vector<string> key); 
 void complete_table(void);
  void initialize(void);
 void do_line(int start);
 void do_cell(int start, int length);
 int is_there(int start, int length, Category c);
 void add_edge(int start, int length, SlashCategory p);
 void propose_slash(int start, int length, Category c);

 void display_row(int length);  
  int chart_debug;


};

#endif








