#include "./historyLog.h"
#include <string>
#include <vector>
using namespace std;

class UI {
private:
  string state = "menu";

public:
  void runUI();
  string getState();
  void setState(string);
  vector<char> defineVariables();
  void printOperationInfo();
  string getExpression(vector<char>);
  vector<bool> getTruthVals(vector<char>);
  void runMenu();
  void runNewExpression(HistoryLog);
  void printHistory(HistoryLog);
};