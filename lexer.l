%option noyywrap
%option nounput

%{

#include <iostream>
#include <cstdlib>
#include <string>
#include <math.h>
#include "expression.hpp"
#include "command.hpp"

using namespace std;

int convertToDecimal(string s);

#include "parser.tab.hpp"

%}

%%

for return for_token;
to return to_token;
repeat return repeat_token;
until return until_token;
"return" return return_token;
int return int_token;
read return read_token;
begin return begin_token;
end return end_token;
print return print_token;
mod return mod_token;
if return if_token;
then: return then_token;
else: return else_token;
while return while_token;
do: return do_token;
"==" return eq_token;
"!=" return notEq_token;
("-")?[0-9]+ yylval.d = atoi(yytext); return num;
"0x"[0-9A-F]+ yylval.d = convertToDecimal(string(yytext)); return num;
[a-zA-Z_][a-zA-Z_0-9]* yylval.s = new string(yytext); return id;
"\"".*"\"" yylval.s = new string(yytext); return text_token;
[ \t\n] {}
[+-/{}<>()*;.\":=] return *yytext;
. {
     cerr << "Lexical error, unrecognized character: " << *yytext << endl;
     exit(EXIT_FAILURE);
  }

%%

int convertToDecimal(string s)
{
  int sum = 0;
  for(unsigned i = 2; i < s.length(); i++)
     if(s[i] >= '0' && s[i] <= '9')
         sum += (s[i] - '0')*pow(16, s.length() - i - 1);
     else sum += (s[i] - 'A' + 10)*pow(16, s.length() - i - 1);

  return sum;
}