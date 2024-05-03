#include "./src/headers/UI.h"

int main() {
  UI ui;
  ui.runUI();

  return 0;
}

/*----------------------------------------
TODO:
Extraneous Error Testing:
  Input values from user that are not valid
  Use examples given in error testing table created by Dustin
  
--Calculator does not do NOT functions before a parenthesized function. 
EX: !(T&F) just calcuates the parenthesized T&F without the NOT 

Fix History Log: Get
program to add history correctly Get program to print history correctly

ErrorHandler Class:
  Compartamentalize the error checking with multiple functions to check exactly
what is wrong with the expression
    TODO:
      checkForInvalidParentheses(string expression)

Truth Table:
  Create a better format for the Truth Table:
    EXAMPLE:
      +----------------------------------------------------------+
      |    VARIABLES    | SUBEXPRESSIONS |     MAIN EXPRESSION   |
      +-----+-----+-----+-------+--------+-----------------------+
      |  A  |  B  |  C  | A & B | A & C  | ( A & B ) | ( A & C ) |
      +-----+-----+-----+-------+--------+-----------------------+
      |  0  |  0  |  0  |   0   |   0    |           0           |
      +----------------------------------------------------------+

Comment out code blocks:
  DO NOT comment every line
  Only comment relevant information for each block of code
  Leave header files comment free

Non-Repl.it Compile:
  Download code base as a zip file and try to compile on Windows
  Download code base as a zip file and try to compile on Linux
  Download code base as a zip file and try to compile on MacOS


----------------------------------------*/