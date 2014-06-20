#include <iostream>
#include "expression.hpp"
#include "command.hpp"
#include "function.hpp"
#include <map>

using namespace std;

extern void yyerror(string s);
extern map<string, int> table;
extern map<string, Function*> functions;
extern stack<map<string, int> > local_vars;
extern int return_value;
extern int break_com;

BlockCommand::~BlockCommand()
{
  vector<Command * >::iterator i;

  for(i = _commands -> begin(); i != _commands -> end(); i++)
    delete (*i);
}

void BlockCommand::Run()
{
  vector<Command * >::iterator i;
  map<string, int>::iterator j;
  if(local_vars.empty())
    local_vars.push(locals);
  else
    {
      map<string, int> block_locals = map<string, int>(local_vars.top());
  
      for(j = block_locals.begin(); j != block_locals.end(); j++)	
	  locals[j -> first] = j -> second;
      
      local_vars.push(locals);
    }
  
  for(i = _commands -> begin(); i != _commands -> end(); i++)
    {
      (*i) -> Run();
      if(break_com == 1)
	{
	  break_com = 0;
	  break;
	}      
    }
  local_vars.pop();
}

void PrintStringCommand::Run()
{
  cout << _s << endl;
}

PrintExpressionCommand::~PrintExpressionCommand()
{
  delete _exp;
}

void PrintExpressionCommand::Run()
{
  cout << _exp -> Value() << endl;
}

void ReadCommand::Run()
{
  map<string, int> locals = map<string, int>(local_vars.top());
  local_vars.pop();
  cin >> locals[_s];
  cout << locals[_s] << endl;
  local_vars.push(locals);
}

void DeclarationCommand::Run()
{  
  map<string, int> locals = map<string, int>(local_vars.top());
  local_vars.pop();
  locals[_s] = _exp -> Value();
  local_vars.push(locals);
}

DeclarationCommand::~DeclarationCommand()
{
  delete _exp;
}

void AssignmentCommand::Run()
{
  map<string, int> locals = map<string, int>(local_vars.top());
 
  map<string, int>::iterator i = locals.find(_s);
  if(i == locals.end())
    yyerror("No such variable " + _s);
  int result = _exp -> Value();
  
  locals = map<string, int>(local_vars.top());
  local_vars.pop();
  locals[_s] = result; 
  local_vars.push(locals);
}

AssignmentCommand::~AssignmentCommand()
{
  delete _exp;
}

IfThenElseCommand::~IfThenElseCommand()
{
  delete _exp;
  delete _then;
  delete _else;
}

void IfThenElseCommand::Run()
{
  if(_exp -> Value())
    _then -> Run();
  else _else -> Run();
}

IfThenCommand::~IfThenCommand()
{
  delete _exp;
  delete _then;
}

void IfThenCommand::Run()
{
  if(_exp -> Value())
    _then -> Run();
}

WhileCommand::~WhileCommand()
{
  delete _exp;
  delete _c;
}

void WhileCommand::Run()
{
  while(_exp -> Value())
    _c -> Run();    
}

NewFunctionDeclaration::~NewFunctionDeclaration()
{
  delete _command;
  vector<Argument * >::iterator i;

  for(i = _arguments -> begin(); i != _arguments -> end(); i++)
    delete (*i);
}

void NewFunctionDeclaration::Run()
{
  functions[_fun_name] = new Function(_arguments, _command);
}

void ReturnCommand::Run()
{
    return_value =  _exp -> Value();
    break_com = 1;
    local_vars.pop();
}

void RepeatUntilCommand::Run()
{  
  map<string, int> local;
  local_vars.push(local);

  vector<Command * >::iterator i;
  map<string, int>::iterator j;

  map<string, int> locals = map<string, int>(local_vars.top());
  local_vars.pop();

  map<string, int> block_locals = map<string, int>(local_vars.top());
  
  for(j = block_locals.begin(); j != block_locals.end(); j++)	
    locals[j -> first] = j -> second;	
      
  local_vars.push(locals);
  while(_exp -> Value())
    { 
      for(i = _commands -> begin(); i != _commands -> end(); i++)
	(*i) -> Run();
    }

  locals = map<string, int>(local_vars.top());
  local_vars.pop();
  block_locals = map<string, int>(local_vars.top());
  local_vars.pop();
  for(j = locals.begin(); j != locals.end(); j++)
    {
      map<string, int>::iterator k = block_locals.find(j -> first);
      if(k != block_locals.end())
	{
	  block_locals[j -> first] = j -> second;
	}
    }
  local_vars.push(block_locals);
}

RepeatUntilCommand::~RepeatUntilCommand()
{
  delete _exp;

  vector<Command * >::iterator i;

  for(i = _commands -> begin(); i != _commands -> end(); i++)
    delete (*i);
}

ForCommand::~ForCommand()
{
  delete _c;
}

void ForCommand::Run()
{
  map<string, int> locals = map<string, int>(local_vars.top());
  local_vars.pop();
  map<string, int>::iterator i = locals.find(_var_name);
  if(i == locals.end())
    yyerror("No such variable " + _var_name);
   
  locals[_var_name] = _initial_value;

  int param = _initial_value;

  local_vars.push(locals);      
  
  while(param < _final_value)
    {
      _c -> Run();
      param++;
      locals = map<string, int>(local_vars.top());
      local_vars.pop();
      locals[_var_name] = param;
      local_vars.push(locals);
    }
}
