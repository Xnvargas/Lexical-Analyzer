#include "lex.h"
#include "fstream"
#include <string>
#include <iostream>
using std::string;
using std::istream;
using std::ostream;
using namespace std;


Lex getNextToken(istream& in, int& linenum)
{
	enum LexState{ BEGIN, INID, ININT, OPRT, CMT, STRNG, END, };
	LexState lexstate = BEGIN;
	string lexeme;
	char ch;
	while (in.get(ch))
	{
		Token tok;
		char pk = in.peek();
		switch (lexstate)
		{
		case BEGIN:
			if (ch == '\n')
			{
				linenum++;
			}
			else if (isspace(ch))
			{
				break;
			}
			else if (ch == '+' || ch == '-' || ch == ')' || ch == '(' || ch == '*' || ch == '!' || ch == '/' || ch == ';')
			{
				if (pk == '/')
				{
					lexstate = CMT;
					break;
				}
				lexstate = OPRT;
				lexeme += ch;
			}
			else if (isalpha(ch))
			{
				lexstate = INID;
				lexeme += ch;
			}
			else  if (isdigit(ch))
			{
				lexstate = ININT;
				lexeme += ch;
			}
			else  if (ch == '$')
			{
				tok = DONE;
				lexstate = END;
				lexeme += ch;
			}
			else if (ch == '"')
			{
				lexstate = STRNG;
				break;
			}
			else
			{
				tok = ERR;
				lexstate = END;
				lexeme += ch;
				break;
			}
			break;
		case OPRT:
				in.putback(ch);
				if (ch == '+')
				{
					tok = PLUS;
					lexstate = END;
				}
				if (ch == '-')
				{
					tok = MINUS;
					lexstate = END;
				}
				if (ch == ';')
				{
					tok = SC;
					lexstate = END;
				}
				if (ch == '(')
				{
					tok = LPAREN;
					lexstate = END;
				}
				if (ch == ')')
				{
					tok = RPAREN;
					lexstate = END;
				}
				if (ch == '*')
				{
					tok = STAR;
					lexstate = END;
				}
				if (ch == '!')
				{
					tok = BANG;
					lexstate = END;
				}
				if (ch == '/')
				{
					tok = SLASH;
					lexstate = END;
				}
			break;
		case INID:
			if (isalnum(ch))
			{
				if (isalpha(ch))
				{
					lexeme += ch;
					if (lexeme == "print")
					{
						tok = PRINT;
						lexstate = END;
					}
					if (lexeme == "let")
					{
						tok = LET;
						lexstate = END;
					}
					if (lexeme == "if")
					{
						tok = IF;
						lexstate = END;
					}
					if (lexeme == "loop")
					{
						tok = LOOP;
						lexstate = END;
					}
					if (lexeme == "begin")
					{
						tok = Lex::BEGIN;
						lexstate = END;
					}
					if (lexeme == "end")
					{
						tok = Lex::END;
						lexstate = END;
					}
					break;
				}
				lexeme += ch;
				break;
			}
			if (!isalnum(ch))
			{
				in.putback(ch);
				tok = ID;
				lexstate = END;
			}
			break;
		case STRNG:
			// cout<<"STRRR"<<ch<<endl;
			if (ch != '"')
			{
				if (ch == '\\')
				{
					if (pk == 'n')
					{
						linenum++;
						lexstate = END;
						tok = STR;
					}
					if (pk == '\\')
					{
						break;

					}
					break;
				}
				lexeme += ch;
			}
			else
			{
				
				tok = STR;
				lexstate = END;
				break;
			}
			break;
		case ININT:
			//cout << lexeme<<"  "<<ch << endl;
			if (isdigit(ch))
			{
				lexeme += ch;
				break;
			}
			else
			{
				in.putback(ch);
				tok = INT;
				lexstate = END;
			}
			break;
		case CMT:
			if (ch == '\n')
			{
				linenum++;
				lexstate = BEGIN;
			}
			else
			{
				break;
			}
			break;
		case END:
			//cout<<"ENDLER"<<ch<<"   "<<lexeme<<endl;
			if (tok == DONE)
			{
				lexstate = BEGIN;
				Lex ret(tok, lexeme, linenum);
				return ret;
			}
			else
			{
				//cout << "HERE" << endl;
				Lex ret(tok, lexeme, linenum);
				in.putback(ch);
				lexstate = BEGIN;
				return ret;
			}
			break;
		}
	}
	if (in.get(ch).eof() == true)
	{
		return Lex(DONE, lexeme, linenum);
	}
	return Lex();
}
