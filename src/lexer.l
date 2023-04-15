%option noyywrap

%{
   // Подключаем код на bison
  #include "sintax.h"
%}

IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*
LPARENT [(]
RPARENT [)]
COMMA [,]
ASSIGN [=]
ILIT [0][x][A-F0-9][A-F0-9]*
BOR [|]
BAND [&]
BXOR [\^]
BNOT [~]
TOO_BIG_ILIT [0][x][A-F0-9]{8}[A-F0-9]+
ERROR [^a-zA-Z_(),=|&\^~ \t\r\n]

%%
{IDENTIFIER} {return IDENTIFIER;}
{LPARENT} {return LPARENT;}
{RPARENT} {return RPARENT;}
{COMMA} {return COMMA;}
{ASSIGN} {return ASSIGN;}
{TOO_BIG_ILIT} {return 1;}
{ILIT} {return ILIT;}
{BOR} {return BOR;}
{BAND} {return BAND;}
{BXOR} {return BXOR;}
{BNOT} {return BNOT;}
[ \t\r] {};
\n { return EOL; }
{ERROR}+ {return 1;}
[0-9][a-zA-Z0-9_]* {return 1;}
<<EOF>> { return 0;}
%%

