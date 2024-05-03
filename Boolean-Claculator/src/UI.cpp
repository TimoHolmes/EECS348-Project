#include "./headers/UI.h"
#include "headers/errorHandler.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
ErrorHandler errorHandler;

void UI::runUI() {
  // Instantiate a History Log
  HistoryLog history;

  // Main UI loop dependent on the state of the UI
  while (state != "exit") {
    if (state == "menu") {
      runMenu();
    } else if (state == "history") {
      printHistory(history);
    } else if (state == "new expression") {
      runNewExpression(history);
    }
  }
};

vector<char> UI::defineVariables() {
  /*function that asks the user for how many variables are in their boolean
   * expression and saves that number of variables taken from the varArr in a
   * char vector and returns that vector*/
  char varArr[24] = {'A', 'B', 'C', 'D', 'E', 'G', 'H', 'I',
                     'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                     'R', 'S', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  char *p = &varArr[23];
  int numVariables = 0;

  cout << "Welcome to the Code Commanders Boolean logic calculator!" << endl;
  do {
    cout << "How many variables will be in your expression?: ";
    cin >> numVariables;
  } while (numVariables < 1 || numVariables > 24);

  vector<char> usedVarVector;
  for (int i = numVariables; i > 0; i--) {
    usedVarVector.push_back(p[(i * -1) + 1]);
  }
  cout << "Your variables are: ";
  for (int i = 0; i < usedVarVector.size(); i++) {
    cout << usedVarVector[i] << " ";
  }
  cout << endl;
  return usedVarVector;
};

void UI::printOperationInfo() {
  /*void return function that prints information on how to use the UI*/
  // pick any of these operations for your function!
  cout << "When defining your expression below, please use the following"
       << endl;
  cout << "symbols to represent the following operations: " << endl;
  cout << "AND = &" << endl;
  cout << "OR = |" << endl;
  cout << "NOT = !" << endl;
  cout << "XOR = $" << endl;
  cout << "NAND = @" << endl;
  cout << "Use parentheses to seperate 2-bit blocks in your expression" << endl;
};

string UI::getExpression(vector<char> usedVarVector) {
  /*function that gets expression from user that uses the predefined variables
   * set by the UI*/
  cout << "Write your expression using variables ";
  for (int i = 0; i < usedVarVector.size(); i++) {
    if (i == usedVarVector.size() - 1) {
      cout << usedVarVector[i] << " ";
    } else {
      cout << usedVarVector[i] << ", ";
    }
  }

  cout << "below." << endl;
  cout << "Expression: ";
  string expression;
  cin >> expression;

  // Check if the expression contains valid characters
  bool isValid = errorHandler.checkIfValid(expression, usedVarVector);

  while (!isValid) {
    cout << "Please enter a valid expression: ";
    cin >> expression;
    isValid = errorHandler.checkIfValid(expression, usedVarVector);
  }
  return expression;
};

vector<bool> UI::getTruthVals(vector<char> usedVarVector) {
  /*function that asks the user for truth values for each variable and returns
   * them as a char vector that is parallel to the char vector that holds the
   * variables being used by the expression*/
  vector<bool> usedVarTruthVals;
  for (int i = 0; i < usedVarVector.size(); i++) {
    char truthVal;
    cout << "What is the truth value of " << usedVarVector[i] << "? "
         << "(Please enter T or F): ";
    bool passCheck = false;
    do {
      cin >> truthVal;
      if (truthVal == 'T' || truthVal == 'F') {
        if (truthVal == 'T') {
          bool boolTruthVal = true;
          usedVarTruthVals.push_back(boolTruthVal);
        } else {
          bool boolTruthVal = false;
          usedVarTruthVals.push_back(boolTruthVal);
        }
        passCheck = true;
      } else {
        cout << "ERROR! Please enter T or F for " << usedVarVector[i] << ": ";
      }
    } while (!passCheck);
  }
  cout << endl;
  return usedVarTruthVals;
};

string UI::getState() {
  /*function that returns the current state of the UI*/
  return state;
}

void UI::setState(string state) {
  /*function that sets the state of the UI*/
  this->state = state;
}

void UI::runMenu() {
  /*function that runs the menu of the UI*/
  string options[] = {"New Expression", "History", "Exit"};
  for (int i = 0; i < 3; i++) {
    cout << i + 1 << ". " << options[i] << endl;
  }
  cout << "Please enter the number of the option you would like to select: ";
  int choice;
  cin >> choice;

  switch (choice) {
  case 1:
    setState("new expression");
    break;
  case 2:
    setState("history");
    break;
  case 3:
    setState("exit");
    break;
  }
}

void UI::runNewExpression(HistoryLog hist) {
  // Asks user for number of variables and returns them in a char vector which
  // is stored in usedVarVector
  vector<char> usedVarVector = defineVariables();

  // Prints information on how to use the UI
  printOperationInfo();

  // Asks for the expression and returns it in a string stored in expression var
  string expression = getExpression(usedVarVector);

  /* Asks the user for the truth values of each variable and returns
  and stores them in a char vector parallel to usedVarVector */
  vector<bool> usedVarTruthVals = getTruthVals(usedVarVector);

  // Instaniates an Expression Class obj using the expression, variables, and
  // truth values
  Expression expr(expression, usedVarVector, usedVarTruthVals);

  // Adds the new expression object to the History Log
  hist.add(expr);

  /* Parser obj parses the expression and returns the parsed expression
  Example : ((W&Z)|(Y$X)@Z) ==> ((T&T)|(T^F)!&T)
  */
  expr.printTruthTable();
  /*^^^^THIS IS WHAT NEEDS TO BE EVALUATED IN INFIX^^^^^^*/

  setState("menu");
}

void UI::printHistory(HistoryLog hist) {
  hist.print();
  cout << "Please enter the number of the expression you would like to see a "
          "truth table for, or enter 0 to return to the menu: ";

  int userSelection;
  cin >> userSelection;
  if (userSelection == 0) {
    setState("menu");
  } else {
    Expression expr = hist.findExpression(userSelection);
    // function here prints the truthtable for that expression
    cout << "Would you like to print another expression? (Y/N): ";
    char userChoice;
    cin >> userChoice;
    if (userChoice == 'N' || userChoice == 'n') {
      setState("menu");
    } else {
      setState("history");
    }
  }
}
