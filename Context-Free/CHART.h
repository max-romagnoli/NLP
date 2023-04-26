#include <string>
#include <vector>
#include "rules.h"

using namespace std;

#if !defined CHART_h
#define CHART_h

typedef vector<Category> Cell;

class CHART {
public: 
 CHART(string grammar);
 CHART(void);
 Grammar g;
 vector<vector<Cell>> chart;
 /*!< used to represent a 2-dimensional table \n 
  * with entries refered to with chart[start][length] \n
  * needs to be resized for each input of length M \n
  * start = 0 to M-1 so chart is a vector of length M \n
  * length = 1 to M and this is easiest done by having \n
  * each chart[i] be a vector length M+1, with position 0 never used \n
  * its effective entries run from k=1 to k=M
  */


 bool accept(vector<string> in); //!< check whether in is acceptable
 vector<string> input; //!< stores whatever passed to accept 
 void do_table(void); 
 void initialize(void); //!< set the chart to right size then put in length 1 entries
 void do_line(int length); //!< should fill in all entries of this length
 void do_cell(int start, int length); //!< should fill in all entries at chart[start][length] 
 bool is_there(int start, int length, Category c); //!< check for c at chart[start][length]
 void add_edge(int start, int length, Category c); //!< add c to chart[start][length] if not there
 void clear_table(void); //!< empty all chart entries
 void display_row(int length); //!< display row of given length
 int chart_debug;

};

#endif
