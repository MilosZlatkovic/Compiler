#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__ 1

#include <iostream>
#include "expression.hpp"
#include <vector>
#include <map>
#include <stack>

using namespace std;

class Command
{
public:
  virtual ~Command()
  {}
  virtual void Run() = 0;
};

class BlockCommand: public Command
{
public:
  BlockCommand(vector<Command *> *commands)
    :_commands(commands)
  {}
  ~BlockCommand();
  void Run();
private:
  BlockCommand(const BlockCommand& bc);
  BlockCommand& operator = (const BlockCommand& bc);
  vector<Command *> *_commands;
  map<string, int> locals;
};

class PrintStringCommand: public Command
{
public:
  PrintStringCommand(string s)
  :_s(s)
  {}
  void Run();
private: 
  string _s;
};

class PrintExpressionCommand: public Command
{
public:
  PrintExpressionCommand(Expression *exp)
    :_exp(exp)
  {}
  ~PrintExpressionCommand();
  void Run();
private:
  PrintExpressionCommand(const PrintExpressionCommand& pec);
  PrintExpressionCommand& operator = (const PrintExpressionCommand& pec);
protected:  
  Expression *_exp;
};

class ReadCommand: public Command
{
public:
  ReadCommand(string s)
    :_s(s)
  {}
  void Run();
protected:
  string _s;
};

class DeclarationCommand: public Command
{
public:
  DeclarationCommand(string s, Expression *exp)
    :_s(s), _exp(exp)
  {}
  ~DeclarationCommand();
  void Run();
private:
  DeclarationCommand(const DeclarationCommand& ac);
  DeclarationCommand& operator = (const DeclarationCommand& ac);
protected:
  string _s;
  Expression *_exp;
};

class AssignmentCommand: public Command
{
public:
  AssignmentCommand(string s, Expression *exp)
    :_s(s), _exp(exp)
  {}
  ~AssignmentCommand();
  void Run();
private:
  AssignmentCommand(const AssignmentCommand& ac);
  AssignmentCommand& operator = (const AssignmentCommand& ac);
protected:
  string _s;
  Expression *_exp;
};

class IfThenElseCommand: public Command
{
public:
  IfThenElseCommand(Expression *exp, Command *then, Command *else_command)
    :_exp(exp), _then(then), _else(else_command)
  {}
  ~IfThenElseCommand();
  void Run();
private:
  IfThenElseCommand(const IfThenElseCommand& itec);
  IfThenElseCommand& operator = (const IfThenElseCommand& itec);
protected:
  Expression *_exp;
  Command *_then;
  Command *_else;
};

class IfThenCommand: public Command
{
public:
  IfThenCommand(Expression *exp, Command *then)
    :_exp(exp), _then(then)
  {}
  ~IfThenCommand();
  void Run();
private:
  IfThenCommand(const IfThenCommand& itc);
  IfThenCommand& operator = (const IfThenCommand& itc);
protected:
  Expression *_exp;
  Command *_then;
};

class WhileCommand: public Command
{
public:
  WhileCommand(Expression *exp, Command *c)
    :_exp(exp), _c(c)
  {}
  ~WhileCommand();
  void Run();
private:
  WhileCommand(const WhileCommand& wc);
  WhileCommand& operator = (const WhileCommand& wc);  
protected:
  Expression *_exp;
  Command *_c;
};

class Argument
{
public:
  Argument(string s, int i)
    :_s(s), _i(i)
  {}

  string _s;
  int _i;
};

class NewFunctionDeclaration: public Command
{
public:
  NewFunctionDeclaration(string fun_name, vector<Argument *> *arguments, Command *command)
    :_fun_name(fun_name), _arguments(arguments), _command(command)
  {}
  ~NewFunctionDeclaration();
  void Run();
private:
  string _fun_name;
  vector<Argument *> *_arguments;
  Command *_command; 
};

class ReturnCommand: public Command
{
public:
  ReturnCommand(Expression *exp)
     :_exp(exp)
  {}
  void Run();
private:
    Expression *_exp;
};

class RepeatUntilCommand: public Command
{
public:
  RepeatUntilCommand(vector<Command *> *commands, Expression *exp)
    :_exp(exp), _commands(commands)
  {}
  ~RepeatUntilCommand();
  void Run();
private:
  RepeatUntilCommand(const RepeatUntilCommand& ruc);
  RepeatUntilCommand& operator = (const RepeatUntilCommand& ruc);  
protected:
  Expression *_exp;
  vector<Command *> *_commands;
};

class ForCommand: public Command
{
public:
  ForCommand(string var_name, int initial_value, int final_value, Command *c)
    :_var_name(var_name), _initial_value(initial_value), _final_value(final_value), _c(c)
  {}
  ~ForCommand();
  void Run();
private:
  ForCommand(const ForCommand& fc);
  ForCommand& operator = (const ForCommand& fc);
protected:
  string _var_name;
  int _initial_value;
  int _final_value;
  Command *_c;
};

#endif
