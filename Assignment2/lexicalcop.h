#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>

using namespace std;

class Lexical
{
public:
	//constructor
	Lexical();

	//finite state machine for integer
	int intFSM(const string str);

	//finite state machine for floating
	int realFSM(const string str);

	//finite state machine for identifier
	int identifierFSM(const string str);

	//function returns the column number of the character in the table
	int column(const char input) const;

	//Helper functions checking separator, operator and keyword
	bool Separator(const char input) const;
	bool Operator(const char input) const;
	bool checkKeyword(string identifier) const;

	//function classify a string into a specific group
	int identifyLexeme(string);

	//function returns a token and a lexeme
	void Lexer(ifstream& file);

	//function prints token and lexeme
	void print() const;

	//mutators
	void setToken(const string newToken);
	void setLexeme(const string newLexeme);

	//accessors
	string getToken() const;
	string getLexeme() const;

	//destructor
//	~Lexical();
protected:
	char input;
	string lexeme;
	string token;
	static int line;
};

#endif
