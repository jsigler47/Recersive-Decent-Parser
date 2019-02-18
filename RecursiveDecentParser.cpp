//-----------------------------------------------------------------------------------------------------------------------------------------------
// HEADERS/NAMESPACE
//-----------------------------------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
//-----------------------------------------------------------------------------------------------------------------------------------------------
// GLOBAL VARIABLES
//-----------------------------------------------------------------------------------------------------------------------------------------------
int cur = 0, numAssign = 0, numVars = 0;
string tmp = "";
string input = "";
//-----------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-----------------------------------------------------------------------------------------------------------------------------------------------
string noSpace(string);
int search(string);
int isvar(char);
void program();
void block();
void stmtlist();
void stmt();
void morestmts();
void assign();
void ifstmt();
void whilestmt();
void testexpr();
void expr();
void variable();
void digit();
//-----------------------------------------------------------------------------------------------------------------------------------------------
// MAIN FUNCTION
//-----------------------------------------------------------------------------------------------------------------------------------------------
int main()
{//Read in the input.
	while(getline(cin, tmp))
	{
		input = input + tmp;
	}

	input = noSpace(input);
	//cout << "Input: " << input << endl;

	program();

	return 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
// UTILITY FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------------------------------------
string noSpace(string str)
{
//Get rid of all whitespace from the input string.
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	str.erase(remove(str.begin(), str.end(), '\t'), str.end());
	str.erase(remove(str.begin(), str.end(), '\v'), str.end());
	str.erase(remove(str.begin(), str.end(), '\f'), str.end());
	str.erase(remove(str.begin(), str.end(), '\r'), str.end());

	return str;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
int search(string str)
{
	return input.find(str, cur);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
int isvar(char c)
{
	switch(c)
	{
		case 'a':
			return 1;
		case 'b':
			return 1;
		case 'c':
			return 1;
		default:
			return 0;
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
// GRAMMAR FUNCTIONS
//-----------------------------------------------------------------------------------------------------------------------------------------------
void program() //<program> := program <block> .
{
	 // cout << "start program(). " << endl;

	int pos = search("program");

	if(pos == cur) //Check if it starts with "program"
	{
		cur = cur + 7; //Account for the whole word.
		block();
	}
	else if(pos != cur)
	{
		cout << "Error program() -- bad input. 'program' misplaced at " << pos << " expected at " << cur << endl;
		exit(1);
	}

	if(input[cur] == '.')
		cur = cur + 1;
	else
	{
		cout << "Error program() -- bad input. Expected a '.' and got '" << input[cur] << "'";
		exit(1);
	}

	if(cur == input.length())
	{
		cout << "Parse successful!" << endl;
		cout << numAssign << " assignments"<< endl;
		cout << numVars << " variable references" << endl;
	}

	else
	{
		cout << "Error program() -- bad input. Unexpeted '.' at " << cur << endl;
		exit(1);
	}

	exit(0);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
void block() // <block> := begin <stmtlist> end
{
	  //cout << "start block(). " << endl;

	int pos = search("begin"); //Search for "begin" at or after the current position in the input so it doesn't back track.

	if(pos == cur)
	{
		cur = cur + 5;
		stmtlist();

		pos = search("end");
		if(pos == cur)
		{
			cur = cur + 3;
		}

		else if(pos != cur)
		{
			cout << "Error block() -- bad input. 'end' misplaced at " << pos << " expected at " << cur << endl;
			exit(1);
		}
	}
	else if(pos != cur)
	{
		cout << "Error block() -- bad input. 'block' misplaced at " << pos << " expected at " << cur << endl;
		exit(1);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
void stmtlist() // <stmtlist> := <stmt> <morestmts>
{
	 // cout << "start stmtlist(). " << endl;
	stmt();
	morestmts();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
void morestmts() // <morestmts> := ; <stmtlist> | empty
{
	 // cout << "start morestmts(). " << endl;

	 if(input[cur] == ';')
	 {
	 	cur++;
	 	stmtlist();
	 }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
void stmt() // <stmt> := <assign> | <ifstmt> | <whilestmt> | <block>
{
	 // cout << "start stmt(). " << endl;

	int pos = search("if");
	if(pos == cur)
		ifstmt();

	else if(pos != cur)
	{
		pos = search("while");

		if(pos == cur)
		{
			whilestmt();
		}

		else if(pos != cur)
		{
			pos = search("begin");

			if(pos == cur)
			{
				block();
			}

			else if(isvar(input[cur]) == 1)
			{
				assign();
			}
		}
	}

	else
	{
		cout << "Error stmt() -- bad input. Expected ifstmt, whilestmt or block at " << cur << endl;
		exit(1);
	}

}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
void assign() // <assign> := <variable> = <expr>
{
	 // cout << "start assign(). " << endl;

	variable();

	int pos = search("=");
	if(pos == cur)
	{
		cur++;
	}

	else if(pos != cur)
	{
		cout << "Error assign() -- bad input. '=' misplaced at " << pos << " expected at " << cur << endl;
		exit(1);	
	}

	expr();

	numAssign++;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ifstmt() // <ifstmt> := if <testexpr> then <stmt> else <stmt>
{
	 // cout << "start ifstmt(). " << endl;

	int pos = search("if");
	if(pos == cur)
	{
		cur = cur + 2;
		testexpr();

		pos = search("then");
		if(pos == cur)
		{
			cur = cur + 4;
			stmt();

			pos = search("else");
			if(pos == cur)
			{
				cur = cur + 4;
				stmt();
			}

			else if(pos != cur)
			{
				cout << "Error ifstmt() -- bad input. 'else' misplaced at " << pos << " expected at " << cur << endl;
				exit(1);	
			}
		}

		else if(pos != cur)
		{
			cout << "Error ifstmt() -- bad input. 'then' misplaced at " << pos << " expected at " << cur << endl;	
			exit(1);
		}

	}

	else if(pos != cur)
	{
		cout << "Error ifstmt() -- bad input. 'if' misplaced at " << pos << " expected at " << cur << endl;	
		exit(1);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
void whilestmt() // <whilestmt> := while <testexpr> do <stmt>
{
	 // cout << "start whilestmt(). " << endl;

	int pos = search("while");

	if(pos == cur)
	{
		cur = cur + 5;

		testexpr();

		pos = search("do");

		if(pos == cur)
		{
			cur = cur + 2;
			stmt();
		}

		else if(pos != cur)
		{
			cout << "Error whilestmt() -- bad input. 'do' misplaced at " << pos << " expected at " << cur << endl;
			exit(1);
		}
	}

	else if(pos != cur)
	{
		cout << "Error whilestmt() -- bad input. 'while' misplaced at " << pos << " expected at " << cur << endl;
		exit(1);
	}

}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
void testexpr() // <testexpr> := <variable> <= <expr>
{
	 // cout << "start testexpr(). " << endl;
	variable();

	int pos = search("<");
	if(input[cur] == '<')
		cur++;
	else if(input[cur] != '<')
	{
		cout << "Error testexpr() -- bad input. '<' misplaced at " << pos << " expected at " << cur << endl;
		exit(1);
	}

	pos = search("=");
	if(input[cur] == '=')
		cur++;
	else if(input[cur] != '=')
	{
		cout << "Error testexpr() -- bad input. '=' misplaced at " << pos << " expected at " << cur << endl;
		exit(1);
	}

	expr();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
void expr() // <expr> := + <expr> <expr> | * <expr> <expr> | <variable> | <digit>
{
	 // cout << "start expr(). " << endl;

	if(input[cur] == '+')
	{
		cur++;
		expr();
		expr();
	}

	else if(input[cur] == '*')
	{
		cur++;
		expr();
		expr();
	}

	else if(isalpha(input[cur]))
	{
		variable();
	}

	else if(isdigit(input[cur]))
	{
		digit();
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
void variable() // <variable> := a | b | c
{
	 // cout << "start variable(). " << endl;

	switch(input[cur])
	{
		case 'a':
			numVars++;
			cur++;
			break;
		case 'b':
			cur++;
			numVars++;
			break;
		case 'c':
			cur++;
			numVars++;
			break;
		default:
			cout << "Error variable() -- bad input. Expected a | b | c and got " << input[cur] << endl;
			exit(1);
			break;
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
void digit() // <digit> := 0 | 1 | 2
{
	 // cout << "start digit(). " << endl;

	switch(input[cur])
	{
		case '0':
			cur++;
			break;
		case '1':
			cur++;
			break;
		case '2':
			cur++;
			break;
		default:
			cout << "Error digit() -- bad input. Expected 0 | 1 | 2 and got " << input[cur] << endl;
			exit(1);
			break;
	}
}