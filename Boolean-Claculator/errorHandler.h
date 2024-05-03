#pragma once
#include <string>
#include <vector>
using namespace std;

class ErrorHandler {
public:
  bool checkIfValid(string expression, vector<char> usedVarVector);

  bool checkParenthesis(string expression);

  bool checkVariables(string expression, vector<char> usedVarVector);

  bool checkOperators(string expression); 
};