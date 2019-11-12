#ifndef PAR_H
#define PAR_H

#include "lexical.h"

class Par : public Lexical
{
	//RAT19F is the main function for this top-down parser
	//The functions following it are called recursively using (RDP)
public:
	//constructor
	Par();

	//syntax rule functions after removing left recursive and backtracking

	//<Rat19F> := <Opt Function Definitions> %%  <Opt Declaration List> <Statement List>
	void RAT19F(ifstream& infile, ofstream& outfile);

	//<Opt Function Definitions> := <Function Definitions> | <Empty>
	void OptFunctionDefinition(ifstream& infile, ofstream& outfile);

	//<Function Definitions>  :: = <Function> | <Function> <Function Definitions>
	void FunctionDefinition(ifstream& infile, ofstream& outfile);

	//<Function> ::= function  <Identifier>   ( <Opt Parameter List> )  <Opt Declaration List>  <Body>
	void Function(ifstream& infile, ofstream& outfile);

	//<Opt Parameter List> :: = <Parameter List> | <Empty>
	void OptParameterList(ifstream& infile, ofstream& outfile);

	//<Parameter List>  ::=  <Parameter>    |     <Parameter> , <Parameter List>
	void ParameterList(ifstream& infile, ofstream& outfile);

	//<Parameter> ::=  <IDs >  <Qualifier>  
	void Parameter(ifstream& infile, ofstream& outfile);

	//<Qualifier> ::= int     |    boolean    |  real 
	void Qualifier(ifstream& infile, ofstream& outfile);

	//<Body>  ::=  {  < Statement List>  }
	void Body(ifstream& infile, ofstream& outfile);

	//<Opt Declaration List> ::= <Declaration List>   |    <Empty>
	void OptDeclarationList(ifstream& infile, ofstream& outfile);

	//<Declaration List>  := <Declaration> ;     |      <Declaration> ; <Declaration List>
	void DeclarationList(ifstream& infile, ofstream& outfile);

	// <Declaration> ::=   <Qualifier > <IDs>                   
	void Declaration(ifstream& infile, ofstream& outfile);

	//<IDs> ::=     <Identifier>    | <Identifier>, <IDs>
	void IDs(ifstream& infile, ofstream& outfile);

	//<Statement List> ::=   <Statement>   | <Statement> <Statement List>
	void StatementList(ifstream& infile, ofstream& outfile);

	//<Statement> ::=   <Compound>  |  <Assign>  |   <If>  |  <Return>   | <Print>   |   <Scan>   |  <While> 
	void Statement(ifstream& infile, ofstream& outfile);

	//<Scan> ::=    get ( <IDs> );
	void Scan(ifstream& infile, ofstream& outfile);

	//<Compound> ::=   {  <Statement List>  } 
	void Compound(ifstream& infile, ofstream& outfile);

	//<Assign> ::=     <Identifier> = <Expression> ;
	void Assign(ifstream& infile, ofstream& outfile);

	/*<If> ::=     if  ( <Condition>  ) <Statement>   fi   |   
	if (<Condition>) <Statement>   otherwise  <Statement>  fi
	*/
	void If(ifstream& infile, ofstream& outfile);

	//<Return> ::=  return ; |  return <Expression> ;
	void Return(ifstream& infile, ofstream& outfile);

	//<While> ::=  while ( <Condition>  )  <Statement>   
	void While(ifstream& infile, ofstream& outfile);

	//<Condition> ::=     <Expression>  <Relop>   <Expression>
	void Condition(ifstream& infile, ofstream& outfile);

	// <Relop> :: = ==   | /= | > | < | = >    |   <=
	void Relop(ifstream& infile, ofstream& outfile);

	//<Expression>  ::=    <Expression> + <Term>    | <Expression>  - <Term>    |    <Term>
	void Expression(ifstream& infile, ofstream& outfile);

	//<Term>    ::=      <Term>  *  <Factor>     |   <Term>  /  <Factor>     |     <Factor>
	void Term(ifstream& infile, ofstream& outfile);

	//<Factor> ::=      -  <Primary>    |    <Primary>
	void Factor(ifstream& infile, ofstream& outfile);

	/*<Primary> ::=     <Identifier>  |  <Integer>  |   <Identifier>  ( <IDs> )   |   ( <Expression> )   |  
                                     <Real>  |   true   |  false                       */
	void Primary(ifstream& infile, ofstream& outfile);

	//<Empty>   ::= epsilon
	void Empty(ifstream& infile, ofstream& outfile);

	//Helper functions
	void printError(ofstream& outfile);
	void ParserOnOff(const bool number);
	void print(ofstream& outfile);



private:
	bool _switch;
};

#endif