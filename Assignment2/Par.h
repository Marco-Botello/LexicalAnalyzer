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

	//<Rat19F> -> <Opt Function Definitions> %%  <Opt Declaration List> <Statement List>
	void RAT19F(ifstream& infile, ofstream& outfile);

	//<Opt Function Definitions> -> <Function Definitions> | <Empty>
	void OptFunctionDefinition(ifstream& infile, ofstream& outfile);

	//<Function Definitions> -> <Function>
	void FunctionDefinition(ifstream& infile, ofstream& outfile);

	/*<Function> ->  @  <Identifier>  (<Opt Parameter List> )   
	<Opt Declaration List>  <Body>*/
	void Function(ifstream& infile, ofstream& outfile);

	//<Opt Parameter List> ->  <Parameter List>   |  <Empty>
	void OptParameterList(ifstream& infile, ofstream& outfile);

	//<Parameter List>  ->  <Parameter>
	void ParameterList(ifstream& infile, ofstream& outfile);

	//<Parameter> ->  <IDs > : <Qualifier> 
	void Parameter(ifstream& infile, ofstream& outfile);

	//<Qualifier> -> integer   |  boolean  |  floating
	void Qualifier(ifstream& infile, ofstream& outfile);

	//<Body>  ->  {  < Statement List>  }
	void Body(ifstream& infile, ofstream& outfile);

	//<Opt Declaration List> -> <Declaration List>   | <Empty>
	void OptDeclarationList(ifstream& infile, ofstream& outfile);

	//<Declaration List>  -> <Declaration> ;
	void DeclarationList(ifstream& infile, ofstream& outfile);

	//<Declaration> ->  <Qualifier > <IDs>
	void Declaration(ifstream& infile, ofstream& outfile);

	//<IDs> ->  <Identifier>
	void IDs(ifstream& infile, ofstream& outfile);

	//<Statement List> ->  <Statement>
	void StatementList(ifstream& infile, ofstream& outfile);

	/*<Statement> ->  <Compound> | <Assign> | <If> |  <Return> | 
	<Write> | <Read> | <While>*/
	void Statement(ifstream& infile, ofstream& outfile);

	//<Compound> -> {  <Statement List>  }
	void Compound(ifstream& infile, ofstream& outfile);

	//<Assign> -> <Identifier> : = <Expression>;
	void Assign(ifstream& infile, ofstream& outfile);

	//<If> -> if  ( <Condition>  ) <Statement>
	void If(ifstream& infile, ofstream& outfile);
	
	//<Return> ->  return
	void Return(ifstream& infile, ofstream& outfile);

	//<While> -> while ( <Condition>  )  <Statement> 
	void While(ifstream& infile, ofstream& outfile);

	//<Condition> -> <Expression>  <Relop>   <Expression>
	void Condition(ifstream& infile, ofstream& outfile);

	//<Relop> ->   = |  /=  |   >   | <   |  =>   | <=
	void Relop(ifstream& infile, ofstream& outfile);

	//<Expression>  -> <Term>
	void Expression(ifstream& infile, ofstream& outfile);

	//<Term>    ->  <Factor>
	void Term(ifstream& infile, ofstream& outfile);

	//<Factor> -> - <Primary>   | <Primary>
	void Factor(ifstream& infile, ofstream& outfile);

	/*<Primary> -> <Identifier> | <Integer> | ( <Expression> ) |
	<Real>  | true | false*/
	void Primary(ifstream& infile, ofstream& outfile);

	//<Empty> -> epsilon
	void Empty(ifstream& infile, ofstream& outfile);

	//Helper functions
	void printError(ofstream& outfile);
	void ParserOnOff(const bool number);
	void print(ofstream& outfile);

	//Destructor
//	~Par();

private:
	bool _switch;
};

#endif
