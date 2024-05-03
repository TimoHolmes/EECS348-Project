#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

class Expression {

private:
  string expression;
  vector<char> vars;
  vector<bool> truthVals;
  vector<string> subExpressions;

public:
  Expression(string expression, vector<char> vars, vector<bool> truthVals);
  string getExpression();
  vector<char> getVars();
  vector<bool> getTruthVals();
  vector<string> getSubExpressions();
  vector<string>extractSubExpressions(const string&);
  void allocateSubExpressions();
  bool applyOperator(bool, bool, char);
  bool evaluateSubExpression(const string&);
  bool evaluateInfix(const string&);
  void printTruthTable();
};