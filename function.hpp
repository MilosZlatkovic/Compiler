#ifndef __FUNCTION_HPP__
#define __FUNCTION_HPP__

#include <iostream>
#include <vector>
#include "command.hpp"
#include "expression.hpp"

using namespace std;

class Function
{
public:
  Function(vector<Argument *> *a, Command *c)
    :_args(a), _c(c)
  {}
  int Value(vector<Expression *> *param) const;
protected:
  vector<Argument *> *_args;
  Command *_c;
};

#endif
