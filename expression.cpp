#include <iostream>
#include "expression.hpp"
#include "function.hpp"
#include <map>

using namespace std;

extern stack<map<string, int> > local_vars;
extern void yyerror(string s);
extern map<string, Function*> functions;

int Const::Value() const
{
  return _num;
}

int Var::Value() const
{
  map<string, int> locals = map<string, int>(local_vars.top());

  map<string, int>::iterator i = locals.find(_s);
  if(i == locals.end())
     yyerror("No such variable " + _s);
  return i -> second;
}

int FunctionCall::Value() const
{
  map<string, Function*>::iterator i = functions.find(_fun_name);
  if(i == functions.end())
     yyerror("No such function " + _fun_name);
  return i -> second -> Value(_args); 
}

BinOperator::~BinOperator()
{
  delete _left;
  delete _right;
}

int Add::Value() const
{
  int l = _left -> Value();
  int d = _right -> Value();

  return l + d;
}

int Mul::Value() const
{
  int l = _left -> Value();
  int d = _right -> Value();

  return l * d;
}

int Sub::Value() const
{
  int l = _left -> Value();
  int d = _right -> Value();

  return l - d;
}

int Div::Value() const
{
  int l = _left -> Value();
  int d = _right -> Value();

  if(d == 0)
    yyerror("You can not divide by zero!");
  return l / d;
}

int GT::Value() const
{
  int l = _left -> Value();
  int d = _right -> Value();
 
  return l > d;
}

int LT::Value() const
{
  int l = _left -> Value();
  int d = _right -> Value();

  return l < d;
}

int Mod::Value() const
{
  int l = _left -> Value();
  int d = _right -> Value();

  return l % d;
}

int Eq::Value() const
{
  int l = _left -> Value();
  int d = _right -> Value();

  return l == d;
}

int NotEq::Value() const
{
  int l = _left -> Value();
  int d = _right -> Value();

  return l != d;
}

int Opp::Value() const
{
  return - _e -> Value();
}
