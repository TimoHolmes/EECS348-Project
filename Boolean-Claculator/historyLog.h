#pragma once
#include "expression.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class HistoryLog {
public:
  vector<Expression> expressionHistory;
  void add(Expression);
  Expression findExpression(int);
  void print();
};