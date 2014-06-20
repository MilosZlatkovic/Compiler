#ifndef __EXPRESSION_HPP__
#define __EXPRESSION_HPP__ 1

#include <iostream>
#include <vector>

using namespace std;

class Expression
{
public:
  virtual ~Expression()
  {}
  virtual int Value() const = 0;
};

class Var: public Expression
{
public:
  Var(string s)
    :_s(s)
  {}
  int Value() const;
private:
  string _s;
};

class Const: public Expression
{
public:
  Const(int num)
  :_num(num)
  {}
  int Value() const;
private:  
  int _num;
};

class FunctionCall: public Expression
{
public:
  FunctionCall(string fun_name, vector<Expression *> *a)
    :_fun_name(fun_name), _args(a)
  {}
  int Value() const;
private:
  string _fun_name;
  vector<Expression *> *_args;
};

class BinOperator: public Expression
{
public:
  BinOperator(Expression *left, Expression *right, char sign)
    :_left(left), _right(right), _sign(sign)
  {}
  ~BinOperator();
private:
  BinOperator(const BinOperator& b);
  BinOperator& operator = (const BinOperator& b);
protected:
Expression *_left, *_right;
char _sign;
};

class Add: public BinOperator
{
public:
  Add(Expression *left, Expression *right)
    :BinOperator(left, right, '+')
  {}
  int Value() const;
};

class Sub: public BinOperator
{
public:
  Sub(Expression *left, Expression *right)
    :BinOperator(left, right, '-')
  {}
  int Value() const;
};

class Div: public BinOperator
{
public:
  Div(Expression *left, Expression *right)
    :BinOperator(left, right, '/')
  {}
  int Value() const;
};

class Mul: public BinOperator
{
public:
  Mul(Expression *left, Expression *right)
    :BinOperator(left, right, '*')
  {}
  int Value() const; 
};

class GT: public BinOperator
{
public:
  GT(Expression *left, Expression *right)
    :BinOperator(left, right, '>')
  {}
  int Value() const;
};

class LT: public BinOperator
{
public:
  LT(Expression *left, Expression *right)
    :BinOperator(left, right, '<')
  {}
  int Value() const;
};

class Mod: public BinOperator
{
public:
  Mod(Expression *left, Expression *right)
    :BinOperator(left, right, '%')
  {}
  int Value() const;
};

class Eq: public BinOperator
{
public:
  Eq(Expression *left, Expression *right)
    :BinOperator(left, right, '=')
  {}
  int Value() const;
};

class NotEq: public BinOperator
{
public:
  NotEq(Expression *left, Expression *right)
    :BinOperator(left, right, '!')
  {}
  int Value() const;
};

class Opp: public Expression
{
public:
  Opp(Expression *e)
  :_e(e)
  {}
  int Value() const;
private:  
  Expression *_e;
};

#endif
