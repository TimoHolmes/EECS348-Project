#include "headers/errorHandler.h"
#include <algorithm>
#include <iostream>
#include <vector>

bool ErrorHandler::checkParenthesis(string expression) {
  if (expression.find("(") == string::npos ||
      expression.find(")") == string::npos) {
    return false;
  } else {
    return true;
  }
}

bool ErrorHandler::checkVariables(string expression,
                                  vector<char> usedVarVector) {

  for (char c : expression) {
    if (isalpha(c)) {
      if (std::find(usedVarVector.begin(), usedVarVector.end(), c) ==
          usedVarVector.end()) {
        return false;
      }
    }
  }
  return true;
}

bool ErrorHandler::checkOperators(string expression) {
    vector<char> validOperators = {'&', '|', '$', '@', '!'};

    for (char c : expression) {
        if (!isalpha(c) && !isspace(c) && 
            find(validOperators.begin(), validOperators.end(), c) == validOperators.end() &&
            c != '(' && c != ')') {
            cout << "Invalid operator found: " << c << endl;
            return false; // If the character is not valid, return false
        }
    }
    return true; // All characters are valid operators or operands
}

bool ErrorHandler::checkIfValid(string expression, vector<char> usedVarVector) {
  if (!checkParenthesis(expression)) {
    cout << "ERROR! Parenthesis are not balances." << endl;
    return false;
  }

  if (!checkVariables(expression, usedVarVector)) {
    cout << "ERROR! Variables are not matching from the list provided." << endl;
    return false;
  }

  if (!checkOperators(expression)) {
    cout << "ERROR! Expression contains incorrect operators." << endl;
    return false;
  }

  return true;
}
