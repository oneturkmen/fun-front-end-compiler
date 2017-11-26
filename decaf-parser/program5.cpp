/**
  Program 5, program5.cpp
  Purpose: driver (main) file

  @author Batyr Nuryyev
  @date   11/26/2017
*/
#include <iostream>
#include <string>
#include <iomanip>
#include "program5.hpp"
#include "program5.tab.h"
#include "program5_typecheck.hpp"
#include <FlexLexer.h>
using namespace std;

/* -- -- -- -- -- -- -- -- */
yyFlexLexer scanner;
Node *tree;

/* -- Custom functions -- */
void errox()
{
  cout << endl;
  cout << "--  :( SRY Cannot print the tree        --" << endl;
  cout << "--    Possible reasons:                 --" << endl;
  cout << "-- 1) Errors in bison/flex              --" << endl;
  cout << "-- 2) Lex could not recognize character --" << endl;
  cout << "-- 3) Empty input                       --" << endl;
}

/* -- -- -- MAIN -- -- -- */
int main() {
  yyparse();

  // to be done ...
  if (tree == NULL)
  {
    errox();
  }
  else {
    //cout << endl << "-- PRINTING THE TREE --" << endl;
    //cout << "tree strucure: " << tree->getValProd();
    //tree->print(&cout);

    cout << "<<<<<<<< ! WELCOME TO TYPE CHECKING ROLLERCOASTER ! >>>>>>>>" << endl;

    vector <string> first_phase_errors;


    cout << " -- -- STARTING FIRST PHASE => Filling a la Symbol Table -- -- " << endl;

    buildTypeTree(tree, first_phase_errors);

    if (first_phase_errors.size() >= 1)
    {
      for (const auto &error : first_phase_errors)
      {
        cout << error << endl;
      }
    }
    else
    {
      cout << "CLEAR" << endl;
      cout << " -- -- STARTING SECOND PHASE => Type Checking -- -- ";
      cout << endl;
      vector <string> second_phase_errors;
      checkTypeTree(tree, second_phase_errors);

      if (second_phase_errors.size() >= 1)
      {
        for (const auto &error_2 : second_phase_errors)
        {
          cout << error_2 << endl;
        }
      }
      else
      {
        cout << "CLEAR" << endl;
        cout << " -- -- Dumping the symbol tables -- -- ";
        cout << endl;

        dumpTable(tree);
      }
    }
  }

  return 0;
}
