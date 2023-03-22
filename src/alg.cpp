// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getPrior(char op) {
  std::pair <char, int> priority[6];
  switch (op) {
    case'(':
      priority[0].first = '(';
      priority[0].second = 0;
    case')':
      priority[1].first = ')';
      priority[1].second = 1;
    case'+':
      priority[2].first = '+';
      priority[2].second = 2;
    case'-':
      priority[3].first = '-';
      priority[3].second = 2;
    case'*':
      priority[4].first = '*';
      priority[4].second = 3;
    case'/':
      priority[5].first = '/';
      priority[5].second = 3;
  }
  int prior = -1;
  for (int j = 0; j < 6; ++j) {
    if (op == priority[j].first) {
      prior = priority[j].second;
      break;
    }
  }
  return prior;
}

std::string infx2pstfx(std::string inf) {
  std::string work;
  TStack<char, 100> stack1;
  for (auto& op : inf) {
    int prior = getPrior(op);
    if (prior == -1) {
      work += op;
    } else {
      if (stack1.get() < prior || prior == 0 || stack1.isEmpty()) {
        stack1.push(op);
      } else if (op == ')') {
        char sm = stack1.get();
        while (getPrior(sm) >= prior) {
          work += sm;
          stack1.pop();
          sm = stack1.get();
        }
        stack1.pop();
      } else {
        char sm = stack1.get();
        while (getPrior(sm) >= prior) {
          work += sm;
          stack1.pop();
          sm = stack1.get();
        }
        stack1.push(op);
      }
    }
  }
  while (!stack1.isEmpty()) {
    work += stack1.get();
    stack1.pop();
  }
  return work;
}

int count(const int& a, const int& b, const int& oper) {
  switch (oper) {
    default:
      break;
    case'+': return a + b;
    case'-': return a - b;
    case'*': return a * b;
    case'/': return a / b;
  }
  return 0;
}

int eval(std::string pref) {
  TStack<char, 100> stack1;
  for (auto& oper : pref) {
    if (getPrior(oper) == -1) {
      char ch[2] = {oper, '\0'};
      int r = std::stoi(ch);
      stack1.push(r);
    } else {
      int b = stack1.get();
      stack1.pop();
      int a = stack1.get();
      stack1.pop();
      stack1.push(count(a, b, oper));
    }
  }
  return stack1.get();
}
