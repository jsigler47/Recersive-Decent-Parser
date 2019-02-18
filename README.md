# Recersive-Decent-Parser
A recersive decent parser for a given grammer written in C++  
___
## The Grammar:

\<program\> ::=	program \<block\> .  
\<block\> ::=	begin \<stmtlist\> end  
\<stmtlist\> ::= \<stmt\> \<morestmts\>  
\<morestmts\> ::=	; \<stmtlist   
\<stmt\> ::=\<assign\> | \<ifstmt\> | \<whilestmt\> | \<block\>  
\<assign\> ::= \<variable\> = \<expr\>  
\<ifstmt\> ::= if \<testexpr\> then \<stmt\> else \<stmt\>  
\<whilestmt\> ::= while \<testexpr\> do \<stmt\>  
\<testexpr\> ::= \<variable\> \<= \<expr\>  
\<expr\> ::=	+ \<expr\> \<expr\> | ∗ \<expr\> \<expr\> | \<variable\> | \<digit\>  
\<variable\> :: = a | b | c  
\<digit\> :: =	0 | 1 | 2  
___
The recursive decent parser prints the number of assignment statements in the input program after it successfully parsed the program, and the number of variable references.   
For the program listed below, the parser prints ”4 assignments, 13 variable references”. Note that a statement such as “a = + a b” has three references, not just one.  
  
program  
begin  
if b <= 0 then  
while a <= 1 do  
begin  
a = + a b;  
c = + a 1  
end  
else  
begin  
a = * a b  
end;  
c = + a b  
end.  
___
