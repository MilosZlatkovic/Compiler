#include <iostream>
#include "function.hpp"
#include "command.hpp"
#include "expression.hpp"
#include <vector>
#include <map>
#include <stack>

extern stack<map<string, int> > local_vars; 
extern int return_value;

int Function::Value(vector<Expression *> *param) const
{
  vector<Expression *>::iterator i;
  vector<Argument *>::iterator j;
 
  map<string, int> locals;
  
  for(i = param -> begin(), j = _args -> begin(); i != param -> end(), j != _args -> end(); i++, j++)
    locals[(*j) -> _s] = (*i) -> Value();
  
  local_vars.push(locals);
  _c -> Run();  
  
  return return_value;
}
