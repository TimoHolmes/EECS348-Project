#include "headers/historyLog.h"

void HistoryLog::add(Expression expr) { this->expressionHistory.push_back(expr); }

Expression HistoryLog::findExpression(int i) {
  return this->expressionHistory[i - 1];
};

void HistoryLog::print() {
  if (this->expressionHistory.size() != 0) {
    cout << "Current History: " << endl;
    for (int i = 0; i < this->expressionHistory.size(); i++) {
      cout << i + 1 << ": " << this->expressionHistory[i].getExpression() << endl;
    }
  } else {
    cout << "No expressions have been logged in your history yet." << endl;
  }
}