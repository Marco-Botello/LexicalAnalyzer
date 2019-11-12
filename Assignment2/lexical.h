#ifndef LEXER_H
#define LEXER_H

#include<string>
#include<iostream>
#include<ctype.h>
#include<iomanip>
#include<fstream>
using namespace std;
class Lexical{
public:

            Lexical();
            string getToken() const;
            string getLexeme() const;
            void setToken(const string newToken);
            void setLexeme(const string newLexeme);
            int column(const char input) const;
            int identifyLexeme(string);
            void Lexer(ifstream& file);
            void print() const;
            int intFSM(const string str);
            int realFSM(const string str);
            int identifierFSM(const string str);
          bool Separator(const char input) const;
          bool Operator(const char input) const;
          bool checkKeyword(string identifier) const;

    protected:
    char input;
    static int line;
    string lexeme;
    string token;
    
};
#endif
