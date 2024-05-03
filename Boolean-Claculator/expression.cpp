#include "./headers/expression.h"

/**Expression Class Constructor takes an expression, the variables used in the
 * expression, and the truth values of those variables. The vars and truthVals
 * vectors are parallel.**/
Expression::Expression(string expression, vector<char> vars,
                       vector<bool> truthVals) {
  this->expression = expression;
  this->vars = vars;
  this->truthVals = truthVals;
  allocateSubExpressions();
};

// Returns the expression
string Expression::getExpression() { return this->expression; }

// Returns the Variables
vector<char> Expression::getVars() { return this->vars; }

// Returns the Truth Values used for each variable, respectively
vector<bool> Expression::getTruthVals() { return this->truthVals; }

// Returns current sub expressions held in the subExpressions vector
vector<string> Expression::getSubExpressions() { return this->subExpressions; }

vector<string> Expression::extractSubExpressions(const string &expression) {
  vector<string> result;
  stack<int> parenthesesStack;

  for (int i = 0; i < expression.length(); ++i) {
    if (expression[i] == '(') {
      parenthesesStack.push(i);
    } else if (expression[i] == ')') {
      if (!parenthesesStack.empty()) {
        int start = parenthesesStack.top();
        parenthesesStack.pop();
        int length = i - start - 1;
        if (length > 0) {
          result.push_back(expression.substr(start + 1, length));
        }
      } else {
        // Unmatched closing parenthesis, handle error or ignore
        cerr << "Unmatched ')' at position " << i << endl;
      }
    }
  }

  // Handle unmatched opening parentheses
  while (!parenthesesStack.empty()) {
    int start = parenthesesStack.top();
    parenthesesStack.pop();
    cerr << "Unmatched '(' at position " << start << endl;
  }

  return result;
}

// Adds a new Sub Expression string to the subExpressions vector
void Expression::allocateSubExpressions() {
  vector<string> content = extractSubExpressions(this->expression);
  for (int i = 0; i < content.size(); i++) {
    this->subExpressions.push_back(content[i]);
  }
}

bool Expression::evaluateSubExpression(const string &subExpr) {
  // Replace variables in subexpression with their truth values
  string evaluatedExpr = subExpr;
  for (size_t i = 0; i < this->vars.size(); ++i) {
    size_t pos = evaluatedExpr.find(this->vars[i]);
    while (pos != string::npos) {
      // Check if there is a '!' before the variable
      if (pos > 0 && evaluatedExpr[pos - 1] == '!') {
        // Replace with the opposite of the truth value
        evaluatedExpr.replace(pos - 1, 2, this->truthVals[i] ? "0" : "1");
      } else {
        // Replace with the truth value
        evaluatedExpr.replace(pos, 1, this->truthVals[i] ? "1" : "0");
      }
      // Find the next occurrence of the variable
      pos = evaluatedExpr.find(this->vars[i], pos + 1);
    }
  }
  // Evaluate the expression
  return evaluateInfix(evaluatedExpr);
}

bool Expression::evaluateInfix(const string &expr) {
  stack<char> operators;
  stack<bool> operands;
  for (char c : expr) {
    if (c == '0' || c == '1') {
      operands.push(c == '1');
    } else if (c == '$' || c == '@' || c == '&' || c == '|') {
      operators.push(c);
    } else if (c == ')') {
      while (!operators.empty() && operators.top() != '(') {
        char op = operators.top();
        operators.pop();
        bool operand2 = operands.top();
        operands.pop();
        bool operand1 = operands.top();
        operands.pop();
        operands.push(applyOperator(operand1, operand2, op));
      }
      if (!operators.empty() && operators.top() == '(') {
        operators.pop(); // Remove '(' from stack
      }
    } else if (c != '(') { // Ignore '('
      operands.push(c - '0');
    }
  }
  while (!operators.empty()) {
    char op = operators.top();
    operators.pop();
    bool operand2 = operands.top();
    operands.pop();
    bool operand1 = operands.top();
    operands.pop();
    operands.push(applyOperator(operand1, operand2, op));
  }
  if (operands.size() != 1) {
    throw std::runtime_error(
        "Invalid expression: could not resolve to a single truth value");
  }
  return operands.top();
}

bool Expression::applyOperator(bool operand1, bool operand2, char op) {
  if (op == '&') {
    return operand1 & operand2;
  } else if (op == '|') {
    return operand1 | operand2;
  } else if (op == '$') {
    return operand1 ^ operand2;
  } else if (op == '@') {
    bool temp = operand1 & operand2;
    return !temp;
  }
  throw runtime_error("Invalid operator");
}

void Expression::printTruthTable() {
  // Print evaluation
  printf("The expression %s evaluates to %s", this->expression.c_str(),
         evaluateSubExpression(this->expression) ? "True!" : "False!");
  cout << endl << endl;

  // Print table
  //  headers
  //  variable headers
  int var_size = vars.size();
  int sub_size = subExpressions.size();
  int exp_size = this->expression.size();

  int x = (var_size * 7);
  int y = (sub_size * 11);
  int z = (exp_size + 4);
  int a = x + y + z;

  printf("%*s %*c", (x / 2), "VARIABLES", (x / 2), ' ');
  printf("%*s %*c", (y / 2), "SUB-EXPRESSIONS", (y / 2), ' ');
  printf("MAIN EXPRESSION\n");

  cout << string(a, '=') << endl;
  cout << " ||";
  for (size_t i = 0; i < this->vars.size(); i++) {
    cout << " " << this->vars[i] << " ||";
  }
  // subexpression headers
  for (const string &subExpr : this->subExpressions) {
    printf("%*s %s", 5, subExpr.c_str(), " ");
    cout << "||";
  }
  // full expression header
  printf("%*s %s", (exp_size + 3), expression.c_str(), " ");
  cout << "|| " << endl;

  cout << string(a, '-') << endl;

  // values
  cout << " ||";
  for (size_t i = 0; i < this->vars.size(); ++i) {
    cout << " " << (this->truthVals[i] ? "T" : "F") << " ||";
  }
  // subexpression values
  for (const string &subExpr : this->subExpressions) {
    printf("%*s %s", 4, (evaluateSubExpression(subExpr) ? "T" : "F"), "  ");
    cout << "||";
  }
  // expression values
  printf("%*s %*c", ((exp_size / 2) + 3),
         (evaluateSubExpression(this->expression) ? "T" : "F"),
         ((exp_size / 2) + 2), ' ');
  cout << "|| " << endl;

  cout << string(a, '=') << endl;

  cout << endl << endl;
};