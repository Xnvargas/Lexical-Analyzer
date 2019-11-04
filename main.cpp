#include "lex.h"
#include "fstream"
#include <string>
#include <iostream>
using std::string;
using std::istream;
using std::ostream;

using namespace std;


bool Validate(int argc, char*argv[])
{
	int counter = 0;
	for (int i = 1; i<argc; i++)
	{
		string argIndex = argv[i];
		if (argIndex != "-v" && argIndex != "-consts" && argIndex != "-ids" && argIndex[0] == '-')
		{
			cerr << "UNRECOGNIZED FLAG " << argv[i] << endl;
			return false;
		}
		if (argv[i][0] != '-')
		{
			counter++;
		}

	}
	if (counter >1)
	{
		cerr << "ONLY ONE FILE NAME ALLOWED" << endl;
		return false;
	}
	if (!isalpha(argv[argc - 1][0]))
	{
		cerr << "FILE NOT LAST INDEX" << endl;
		return false;
	}




	ifstream infile;
	infile.open(argv[argc - 1]);
	if (!infile.is_open())
	{
		cerr << "CANNOT OPEN " << argv[argc - 1] << endl;
		return false;
	}
	else
	{
		infile.close();
		return true;
	}
}


int main(int argc, char*argv[])
{
	char c;


	if (Validate(argc, argv))
	{
		string index = argv[1];
		if (index == "-v" && isalpha(argv[argc - 1][0]))
		{
			string vali[] = { "PRINT", "LET", "IF", "LOOP", "BEGIN", "END", "ID", "INT", "STR", "PLUS", "MINUS", "STAR", "SLASH", "BANG", "LPAREN", "RPAREN", "SC", "ERR", "DONE" };
			istream *in;
			ifstream infile;
			infile.open(argv[argc - 1]);
			in = &infile;
			int tokCount = 0, linenum = 0;
			Lex t;
			Token tok;

			while (tok != DONE && tok != ERR)
			{
				t = getNextToken(*in, linenum);
				tok = t.GetToken();
				if (tok == ERR)
				{
					cout << "Error on line " << t.GetLinenum() + 1 << " (" << t.GetLexeme() << ")" << endl;
					linenum++;
					return 0;
				}


				if (tok != DONE && tok != ERR)
				{
					if (tok == PLUS || tok == MINUS || tok == LPAREN || tok == RPAREN || tok == STAR || tok == BANG || tok == SLASH || tok == SC)
					{
						cout << vali[tok] << endl;
						tokCount++;
					}
					else{
						cout << vali[tok] << '(' << t.GetLexeme() << ')' << endl;
						tokCount++;
					}

				}
				cin >> c;
			}
			if ((t = getNextToken(*in, linenum)) == DONE)
			{
				t = getNextToken(*in, linenum);
				tok = t.GetToken();
				cout << "Lines: " << t.GetLinenum() << endl;
				cout << "Tokens: " << tokCount << endl;

				infile.close();
				return 0;
			}

		}
		else if (index == "-v" && !isalpha(argv[argc - 1][0]))
		{
			string vali[] = { "PRINT", "LET", "IF", "LOOP", "BEGIN", "END", "ID", "INT", "STR", "PLUS", "MINUS", "STAR", "SLASH", "BANG", "LPAREN", "RPAREN", "SC", "ERR", "DONE" };
			istream *in;

			in = &cin;
			int tokCount = 0, linenum = 0;
			Lex t;
			Token tok;

			while (tok != DONE && tok != ERR)
			{
				t = getNextToken(*in, linenum);
				tok = t.GetToken();
				if (tok == '+' || tok == '-' || tok == ')' || tok == '(' || tok == '*' || tok == '!' || tok == '/' || tok == ';')
				{
					cout << vali[tok] << endl;
				}
				if (tok != DONE && tok != ERR)
				{
					cout << vali[tok] << '(' << t.GetLexeme() << ')' << endl;
					tokCount++;
				}
			}
			if ((t = getNextToken(*in, linenum)) == DONE)
			{
				t = getNextToken(*in, linenum);
				tok = t.GetToken();
				cout << "Lines: " << t.GetLinenum() << endl;
				cout << "Tokens: " << tokCount << endl;

				return 0;
			}
			if ((t = getNextToken(*in, linenum)) == ERR)
			{
				cout << "Error on line " << (t = getNextToken(*in, linenum)).GetLinenum() << " (" << (t = getNextToken(*in, linenum)).GetLexeme() << ")" << endl;
				linenum++;
				return 0;
			}
		}

		else if ((argv[argc - 1]) == index)
		{
			ifstream infile;
			infile.open(index);
			while (infile.get())
			{
				if (infile.eof())
				{
					cout << "Lines: " << 0 << endl;
					return 0;
				}
			}
		}
		return 0;
	}
	else
		return -1;
}