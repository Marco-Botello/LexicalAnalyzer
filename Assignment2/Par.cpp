#include "Par.h"
#include "lexical.h"
Par::Par()
{
	flag = false; 
}

void Par::ParserOnOff(const bool number)
{
	flag = number;
}

void Par::print(ofstream& output)
{
	if (!flag)
	{
		Lexical::print();
		output << "Token: " << left << setw(20) << this->token
			<< "Lexeme: " << setw(20) << this->lexeme << endl;
	}
}

void Par::RAT19F(ifstream& infile, ofstream& output)
{
	
	Lexer(infile);
	print(output);
	if (!flag)
	{
		cout << "\t<RAT19F> -> <Opt Function Definitions>"
			<< " %% <Opt Declaration List> <Statement List>\n";
		output << "\t<RAT19F> -> <Opt Function Definitions>"
			<< " %% <Opt Declaration List> <Statement List>\n";
	}
	OptFunctionDefinition(infile, output);
	if (lexeme == "%%")
	{
		Lexer(infile);
		print(output);
		OptDeclarationList(infile, output);
		StatementList(infile, output);
		if (!(lexeme == "EOF"))
		{
			output << "This is not EOF marker.\n"
				<< "Error at line " << line << endl
				<< "Only <Opt Declaration List> <StatementList> is allowed after %%.\n";
			cerr << "This is not EOF marker.\n"
				<< "Error at line " << line << endl
				<< "Only <Opt Declaration List> <StatementList> is allowed after %%.\n";
			system("Pause");
			exit(1);
		}

		line = 1;
	}
	else
	{
		printError(output);
		output << "Invalid separator, '%%' is expected "
			<< " after function definitions and before declaration list.\n";
		cerr << "Invalid separator, '%%' is expected "
			<<" after function definitions and before declaration list.\n";
		system("Pause");
		exit(1);
	}
}

void Par::OptFunctionDefinition(ifstream& input, ofstream& output)
{
	if (lexeme == "@")
	{
		if (!flag)
		{
			output << "\t<Opt Function Definition> -> "
				<< "<Function Definition>\n";
			cout << "\t<Opt Function Definition> -> "
				<< "<Function Definition>\n";
		}
		FunctionDefinition(input, output);
	}
	else
	{
		if (!flag)
		{
			output << "\t<Opt Function Definition> -> " << "Epsilon" << endl;
			cout << "\t<Opt Function Definition> -> " << "Epsilon" << endl;
		}
		Empty(input, output);
	}
}

void Par::FunctionDefinition(ifstream& infile, ofstream& outfile)
{
	if (!flag)
	{
		outfile << "\t<Function Definition> ->"
			<< " <Function> \n";
		cout << "\t<Function Definition> ->"
			<< " <Function> \n";
	}
	Function(infile, outfile);
}

void Par::Function(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "@")
	{
		if (!flag)
		{
			cout << "\t<Function> ->"
				<< " @ <Identifier> (<Opt Parameter List>)"
				<< " <Opt Declaration List> <Body>\n";
			outfile << "\t<Function> ->"
				<< " @ <Identifier> (<Opt Parameter List>)"
				<< " <Opt Declaration List> <Body>\n";
		}
		Lexer(infile);
		print(outfile);
		if (token == "identifier")
		{
			Lexer(infile);
			print(outfile);
			if (lexeme == "(")
			{
				Lexer(infile);
				print(outfile);
				OptParameterList(infile, outfile);
				if (lexeme == ")")
				{
					Lexer(infile);
					print(outfile);
					OptDeclarationList(infile, outfile);
					Body(infile, outfile);
				}
				else
				{
					printError(outfile);
					outfile << "Function syntax error\n";
					outfile << "Invalid separator, ')' is expected"
						<< " after parameter list.\n";
					cerr << "Function syntax error\n";
					cerr << "Invalid separator, ')' is expected"
						<< " after parameter list.\n";
					system("Pause");
					exit(1);
				}
			}
			else
			{
				printError(outfile);
				outfile << "Function syntax error\n";
				outfile << "Invalid separator, '(' is expected"
					<< " after <identifier> and before parameter list.\n";
				cerr << "Function syntax error\n";
				cerr << "Invalid separator, '(' is expected"
					<< " after <identifier> and before parameter list.\n";
				system("Pause");
				exit(1);
			}
		}
		else
		{
			printError(outfile);
			outfile << "Function syntax error\n";
			outfile << "Invalid token, <identifier> is expected after '@'.\n";
			cerr << "Function syntax error\n";
			cerr << "Invalid token, <identifier> is expected after '@'.\n";
			system("Pause");
			exit(1);
		}
	}
	else
	{
		printError(outfile);
		outfile << "Function syntax error\n";
		outfile << "Invalid separator, '@' is expected"
			<< " at the beginning of a function.\n";
		cerr << "Function syntax error\n";
		cerr << "Invalid separator, '@' is expected"
			<< " at the beginning of a function.\n";
		system("Pause");
		exit(1);
	}

}

void Par::OptParameterList(ifstream& infile, ofstream& outfile)
{
	if (token == "identifier")
	{
		if (!flag)
		{
			cout << "\t<Opt Parameter List> -> "
				<< "<Parameter List>\n";
			outfile << "\t<Opt Parameter List> -> "
				<< "<Parameter List>\n";
		}
		ParameterList(infile, outfile);
	}
	else
	{
		if (!flag)
		{
			cout << "\t<Opt Parameter List> -> " << "Epsilon" << endl;
			outfile << "\t<Opt Parameter List> -> " << "Epsilon" << endl;
		}
		Empty(infile, outfile);
	}
}

void Par::ParameterList(ifstream& infile, ofstream& outfile)
{
	if (!flag)
	{
		cout << "\t<Parameter List> -> "
			<< "<Parameter>\n";
		outfile << "\t<Parameter List> -> "
			<< "<Parameter>\n";
	}
	Parameter(infile, outfile);
}

void Par::Parameter(ifstream& infile, ofstream& outfile)
{
	if (token == "identifier")
	{
		if (!flag)
		{
			cout << "\t<Parameter> -> <IDs> : <Qualifier>\n";
			outfile << "\t<Parameter> -> <IDs> : <Qualifier>\n";
		}
		IDs(infile, outfile);
		if (lexeme == ":")
		{
			Lexer(infile);
			print(outfile);
			Qualifier(infile, outfile);
		}
		else
		{
			printError(outfile);
			outfile << "Parameter syntax error\n";
			outfile << "Invalid operator, ':' is expected"
				<< " before qualifier.\n";
			cerr << "Parameter syntax error\n";
			cerr << "Invalid operator, ':' is expected"
				<< " before qualifier.\n";
		}
	}
	else
	{
		printError(outfile);
		outfile << "Parameter syntax error\n";
		outfile << "Invalid token, <identifier> is expected"
			<< " after '(' and before ':'.\n";
		cerr << "Parameter syntax error\n";
		cerr << "Invalid token, <identifier> is expected"
			<< " after '(' and before ':'.\n";
		system("Pause");
		exit(1);
	}
}

void Par::Qualifier(ifstream& infile, ofstream& outfile)
{
	if (token == "keyword" && lexeme == "integer")
	{
		if (!flag)
		{
			cout << "\t<Qualifier> -> integer\n";
			outfile << "\t<Qualifier> -> integer\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else if (token == "keyword" && lexeme == "boolean")
	{
		if (!flag)
		{
			cout << "\t<Qualifier> -> boolean\n";
			outfile << "\t<Qualifier> -> boolean\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else if (token == "keyword" && lexeme == "floating")
	{
		if (!flag)
		{
			cout << "\t<Qualifier> -> floating\n";
			outfile << "\t<Qualifier> -> floating\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else
	{
		printError(outfile);
		outfile << "Qualifier syntax error\n"
			<< "Invalid keyword\n";
		outfile << "'integer', 'boolean' or 'floating' keyword is expected"
			<< " after ':'.\n";
		cerr << "Qualifier syntax error\n"
			<< "Invalid keyword\n";
		cerr << "'integer', 'boolean' or 'floating' keyword is expected"
			<< " after ':'.\n";
		system("Pause");
		exit(1);
	}
}

void Par::Body(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "{")
	{
		if (!flag)
		{
			cout << "\t<Body> -> { <Statement List> }\n";
			outfile << "\t<Body> -> { <Statement List> }\n";
		}
		Lexer(infile);
		print(outfile);
		StatementList(infile, outfile);
		if (lexeme == "}")
		{
			Lexer(infile);
			print(outfile);
		}
		else
		{
			printError(outfile);
			outfile << "Function Body syntax error\n";
			outfile << "Invalid separator, '}' is expected"
				<< " after statements. Specifically, after ';'.\n";
			cerr << "Function Body syntax error\n";
			cerr << "Invalid separator, '}' is expected"
				<< " after statements. Specifically, after ';'.\n";
			system("Pause");
			exit(1);
		}
	}
	else
	{
		printError(outfile);
		outfile << "Function Body syntax error";
		outfile << "Invalid separator, '{' is expected"
			<< " before any statements.\n";
		cerr << "Function Body syntax error";
		cerr << "Invalid separator, '{' is expected"
			<< " before any statements.\n";
		system("Pause");
		exit(1);
	}
}

void Par::OptDeclarationList(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "integer" || lexeme == "boolean" || lexeme == "floating")
	{
		if (!flag)
		{
			cout << "\t<Opt Declaration List> -> <Declaration List>\n";
			outfile << "\t<Opt Declaration List> -> <Declaration List>\n";
		}
		DeclarationList(infile, outfile);
	}
	else
	{
		if (!flag)
		{
			cout << "\t<Opt Declaration List> -> " << "Epsilon" << endl;
			outfile << "\t<Opt Declaration List> -> " << "Epsilon" << endl;
		}
		Empty(infile, outfile);
	}
}

void Par::DeclarationList(ifstream& infile, ofstream& outfile)
{
	if (!flag)
	{
		cout << "\t<Declaration List> -> "
			<< "<Declaration>\n";
		outfile << "\t<Declaration List> -> "
			<< "<Declaration>\n";
	}
	Declaration(infile, outfile);
	if (lexeme == ";")
	{
		Lexer(infile);
		print(outfile);
	}
	else
	{
		printError(outfile);
		outfile << "Declaration List syntax error\n";
		outfile << "Invalid separator, ';' is expected"
			<< " at the end of declaration.\n";
		cerr << "Declaration List syntax error\n";
		cerr << "Invalid separator, ';' is expected"
			<< " at the end of declaration.\n";
		system("Pause");
		exit(1);
	}
}

void Par::Declaration(ifstream& infile, ofstream& outfile)
{
	if (!flag)
	{
		cout << "\t<Declaration> -> "
			<< "<Qualifier> <IDs>\n";
		outfile << "\t<Declaration> -> "
			<< "<Qualifier> <IDs>\n";
	}
	Qualifier(infile, outfile);
	IDs(infile, outfile);
}

void Par::IDs(ifstream& infile, ofstream& outfile)
{
	if (token == "identifier")
	{
		if (!flag)
		{
			cout << "\t<IDs> -> "
				<< "<identifier>\n";
			outfile << "\t<IDs> -> "
				<< "<identifier>\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else
	{
		printError(outfile);
		outfile << "IDs syntax error\n";
		outfile << "Invalid token, <identifier> is expected"
			" after '(' or ','.\n";
		cerr << "IDs syntax error\n";
		cerr << "Invalid token, <identifier> is expected"
			" after '(' or ','.\n";
		system("Pause");
		exit(1);
	}
}

void Par::StatementList(ifstream& infile, ofstream& outfile)
{
	if (!flag)
	{
		cout << "\t<Statement List> -> "
			<< "<Statement>\n";
		outfile << "\t<Statement List> -> "
			<< "<Statement>\n";
	}
	Statement(infile, outfile);
}

void Par::Statement(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "{")
	{
		if (!flag)
		{
			cout << "\t<Statement> -> "
				<< "<Compound>\n";
			outfile << "\t<Statement> -> "
				<< "<Compound>\n";
		}
		Compound(infile, outfile);
	}
	else if (token == "identifier")
	{
		if (!flag)
		{
			cout << "\t<Statement> -> "
				<< "<Assign>\n";
			outfile << "\t<Statement> -> "
				<< "<Assign>\n";
		}
		Assign(infile, outfile);
	}
	else if (lexeme == "if")
	{
		if (!flag)
		{
			cout << "\t<Statement> -> "
				<< "<If>\n";
			outfile << "\t<Statement> -> "
				<< "<If>\n";
		}
		If(infile, outfile);
	}
	else if (lexeme == "return")
	{
		if (!flag)
		{
			cout << "\t<Statement> -> "
				<< "<Return>\n";
			outfile << "\t<Statement> -> "
				<< "<Return>\n";
		}
		Return(infile, outfile);
	}
	else if (lexeme == "scan")
	{
		if (!flag)
		{
			cout << "\t<Statement> -> "
				<< "<Scan>\n";
			outfile << "\t<Statement> -> "
				<< "<Scan>\n";
		}
		scan(infile, outfile);
	}
	else if (lexeme == "while")
	{
		if (!flag)
		{
			cout << "\t<Statement> -> "
				<< "<While>\n";
			outfile << "\t<Statement> -> "
				<< "<While>\n";
		}
		While(infile, outfile);
	}
	else
	{
		printError(outfile);
		outfile << "Statement syntax error\n";
		outfile << "Invalid token or keyword or separator\n";
		outfile << "<identifier>,'if', 'return', 'scan', 'while' " 
			<< "keyword or '{'is expected at the beginning of a statement.\n";
		cerr << "Statement syntax error\n";
		cerr << "Invalid token or keyword or separator\n";
		cerr << "<identifier>,'if', 'return', 'scan', 'while' "
			<< "keyword or '{'is expected at the beginning of a statement.\n";
		system("Pause");
		exit(1);
	}
}

void Par::Compound(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "{")
	{
		if (!flag)
		{
			cout << "\t<Compound> -> "
				<< "{ <StatementList> }\n";
			outfile << "\t<Compound> -> "
				<< "{ <StatementList> }\n";
		}
		Lexer(infile);
		print(outfile);
		StatementList(infile, outfile);
		if (lexeme == "}")
		{
			Lexer(infile);
			print(outfile);
		}
		else
		{
			printError(outfile);
			outfile << "Compound syntax error\n";
			outfile << "Invalid separator, '}' is expected"
				<< " at the end of statement list(code block).\n";
			cerr << "Compound syntax error\n";
			cerr << "Invalid separator, '}' is expected"
				<< " at the end of statement list(code block).\n";
			system("Pause");
			exit(1);
		}
	}
	else
	{
		printError(outfile);
		outfile << "Compound syntax error\n";
		outfile << "Invalid separator, '{' is expected"
			<< " at the beginning of statement list(code block).\n";
		cerr << "Compound syntax error\n";
		cerr << "Invalid separator, '{' is expected"
			<< " at the beginning of statement list(code block).\n";
		system("Pause");
		exit(1);
	}
}

void Par::Assign(ifstream& infile, ofstream& outfile)
{
	if (token == "identifier")
	{
		if (!flag)
		{
			cout << "\t<Assign> -> "
				<< "<Identifier> := <Expression>;\n";
			outfile << "\t<Assign> -> "
				<< "<Identifier> := <Expression>;\n";
		}
		Lexer(infile);
		print(outfile);
		if (lexeme == ":=")
		{
			Lexer(infile);
			print(outfile);
			Expression(infile, outfile);
			if (lexeme == ";")
			{
				Lexer(infile);
				print(outfile);
			}
			else
			{
				printError(outfile);
				outfile << "Assign syntax error\n";
				outfile << "Invalid separator, ';' is expected"
					" at the end of assign statement.\n";
				cerr << "Assign syntax error\n";
				cerr << "Invalid separator, ';' is expected"
					" at the end of assign statement.\n";
				system("Pause");
				exit(1);
			}
		}
		else
		{
			printError(outfile);
			outfile << "Assign syntax error\n";
			outfile << "Invalid operator, ':=' is expected"
				<< " after <identifier> and before <expression>.\n";
			cerr << "Assign syntax error\n";
			cerr << "Invalid operator, ':=' is expected"
				<< " after <identifier> and before <expression>.\n";
			system("Pause");
			exit(1);
		}
	}
	else
	{
		printError(outfile);
		outfile << "Assign syntax error\n";
		outfile << "Invalid token, <identifier> is expected"
			" at the beginning of assign statement.\n";
		cerr << "Assign syntax error\n";
		cerr << "Invalid token, <identifier> is expected"
			" at the beginning of assign statement.\n";
		system("Pause");
		exit(1);
	}
}

void Par::If(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "if")
	{
		if (!flag)
		{
			cout << "\t<If> -> "
				<< "if (<Condition>) <Statement>\n";
			outfile << "\t<If> -> "
				<< "if (<Condition>) <Statement>\n";
		}
		Lexer(infile);
		print(outfile);
		if (lexeme == "(")
		{
			Lexer(infile);
			print(outfile);
			Condition(infile, outfile);
			if (lexeme == ")")
			{
				Lexer(infile);
				print(outfile);
				Statement(infile, outfile);
			}
			else
			{
				printError(outfile);
				outfile << "If statement syntax error\n";
				outfile << "Invalid separator, ')' is expected"
					<< " after condition.\n";
				cerr << "If statement syntax error\n";
				cerr << "Invalid separator, ')' is expected"
					<< " after condition.\n";
				system("Pause");
				exit(1);
			}
		}
		else
		{
			printError(outfile);
			outfile << "If statement syntax error\n";
			outfile << "Invalid separator, '(' is expected"
				<< " before condition.\n";
			cerr << "If statement syntax error\n";
			cerr << "Invalid separator, '(' is expected"
				<< " before condition.\n";
			
			system("Pause");
			exit(1);
		}
	}
	else
	{
		printError(outfile);
		outfile << "If statement syntax error\n";
		outfile << "Invalid keyword, 'if' keyword is expected"
			<< " at the beginning of If statement.\n";
		cerr << "If statement syntax error\n";
		cerr << "Invalid keyword, 'if' keyword is expected"
			<< " at the beginning of If statement.\n";
		system("Pause");
		exit(1);
	}
}

void Par::Return(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "return")
	{
		if (!flag)
		{
			cout << "\t<Return> -> "
				<< "return\n";
			outfile << "\t<Return> -> "
				<< "return\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else
	{
		printError(outfile);
		outfile << "Return statement syntax error\n";
		outfile << "Invalid keyword, 'return' is expected"
			<< " at the beginning of Return statement.\n";
		cerr << "Return statement syntax error\n";
		cerr << "Invalid keyword, 'return' is expected"
			<< " at the beginning of Return statement.\n";
		system("Pause");
		exit(1);
	}
}

void Par::While(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "while")
	{
		if (!flag)
		{
			cout << "\t<While> -> "
				<< "<while (<Condition>) <Statement>\n";
			outfile << "\t<While> -> "
				<< "<while (<Condition>) <Statement>\n";
		}
		Lexer(infile);
		print(outfile);
		if (lexeme == "(")
		{
			Lexer(infile);
			print(outfile);
			Condition(infile, outfile);
			if (lexeme == ")")
			{
				Lexer(infile);
				print(outfile);
				Statement(infile, outfile);
			}
			else
			{
				printError(outfile);
				outfile << "While statement syntax error\n";
				outfile << "Invalid separator, ')' is expected"
					<< " after condition and before any statements.\n";
				cerr << "While statement syntax error\n";
				cerr << "Invalid separator, ')' is expected"
					<< " after condition and before any statements.\n";
				system("Pause");
				exit(1);
			}
		}
		else
		{
			printError(outfile);
			outfile << "While statement syntax error\n";
			outfile << "Invalid separator, '(' is expected"
				<< " before condition and after 'while' keyword.\n";
			cerr << "While statement syntax error\n";
			cerr << "Invalid separator, '(' is expected"
				<< " before condition and after 'while' keyword.\n";
			system("Pause");
			exit(1);
		}
	}
	else
	{
		printError(outfile);
		outfile << "While-loop syntax error\n";
		outfile << "Invalid keyword, 'while' is expected"
			<< " at the beginning of While-loop.\n";
		cerr << "While-loop syntax error\n";
		cerr << "Invalid keyword, 'while' is expected"
			<< " at the beginning of While-loop.\n";
		system("Pause");
		exit(1);
	}
}

void Par::Condition(ifstream& infile, ofstream& outfile)
{
	if (!flag)
	{
		cout << "\t<Condition> -> "
			<< "<Expression> <Relop> <Expression>\n";
		outfile << "\t<Condition> -> "
			<< "<Expression> <Relop> <Expression>\n";
	}
	Expression(infile, outfile);
	Relop(infile, outfile);
	Expression(infile, outfile);
}

void Par::Relop(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "=")
	{
		if (!flag)
		{
			cout << "\t<Relop> -> =\n";
			outfile << "\t<Relop> -> =\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else if (lexeme == "/=")
	{
		if (!flag)
		{
			cout << "\t<Relop> -> /=\n";
			outfile << "\t<Relop> -> /=\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else if (lexeme == ">")
	{
		if (!flag)
		{
			cout << "\t<Relop> -> >\n";
			outfile << "\t<Relop> -> >\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else if (lexeme == "<")
	{
		if (!flag)
		{
			cout << "\t<Relop> -> <\n";
			outfile << "\t<Relop> -> <\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else if (lexeme == "=>")
	{
		if (!flag)
		{
			cout << "\t<Relop> -> =>\n";
			outfile << "\t<Relop> -> =>\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else if (lexeme == "<=")
	{
		if (!flag)
		{
			cout << "\t<Relop> -> <=\n";
			outfile << "\t<Relop> -> <=\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else
	{
		printError(outfile);
		outfile << "Relop syntax error\n";
		outfile << "Invalid operator\n"
			<< "'=', '/=', '>', '<', '=>' or '<=' is expected"
			<< " between 2 <Expression>.\n";
		cerr << "Relop syntax error\n";
		cerr << "Invalid operator\n"
			<< "'=', '/=', '>', '<', '=>' or '<=' is expected"
			<< " between 2 <Expression>.\n";
		system("Pause");
		exit(1);
	}
}

void Par::Expression(ifstream& infile, ofstream& outfile)
{
	if (!flag)
	{
		cout << "\t<Expression> -> <Term>\n";
		outfile << "\t<Expression> -> <Term>\n";
	}
	Term(infile, outfile);
}

void Par::Term(ifstream& infile, ofstream& outfile)
{
	if (!flag)
	{
		cout << "\t<Term> -> <Factor>\n";
		outfile << "\t<Term> -> <Factor>\n";
	}
	Factor(infile, outfile);
}

void Par::Factor(ifstream& infile, ofstream& outfile)
{
	if (lexeme == "-")
	{
		if (!flag)
		{
			cout << "\t<Factor> -> - <Primary>\n";
			outfile << "\t<Factor> -> - <Primary>\n";
		}
		Lexer(infile);
		print(outfile);
		Primary(infile, outfile);
	}
	else
	{
		if (!flag)
		{
			cout << "\t<Factor> -> <Primary>\n";
			outfile << "\t<Factor> -> <Primary>\n";
		}
		Primary(infile, outfile);
	}
}

void Par::Primary(ifstream& infile, ofstream& outfile)
{
	if (token == "identifier")
	{
		if (!flag)
		{
			cout << "\t<Primary> -> <identifier>\n";
			outfile << "\t<Primary> -> <identifier>\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else if (token == "integer")
	{
		if (!flag)
		{
			cout << "\t<Primary> -> <integer>\n";
			outfile << "\t<Primary> -> <integer>\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else if (token == "floating")
	{
		if (!flag)
		{
			cout << "\t<Primary> -> <floating>\n";
			outfile << "\t<Primary> -> <floating>\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else if (lexeme == "(")
	{
		if (!flag)
		{
			cout << "\t<Primary> -> (<Expression>)\n";
			outfile << "\t<Primary> -> (<Expression>)\n";
		}
		Lexer(infile);
		print(outfile);
		Expression(infile, outfile);
		if (lexeme == ")")
		{
			Lexer(infile);
			print(outfile);
		}
		else
		{
			printError(outfile);
			outfile << "Invalid separator, ')' is expected.\n";
			cerr << "Invalid separator, ')' is expected.\n";
			system("Pause");
			exit(1);
		}
	}
	else if (lexeme == "true")
	{
		if (!flag)
		{
			cout << "\t<Prime> -> true\n"; //not sure what to do here?
			outfile << "\t<Prime> -> true\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else if (lexeme == "false")
	{
		if (!flag)
		{
			cout << "\t<Prime> -> false\n";
			outfile << "\t<Prime> -> false\n";
		}
		Lexer(infile);
		print(outfile);
	}
	else
	{
		printError(outfile);
		outfile << "Primary syntax error\n";
		outfile << "Invalid token, separator, or boolean value\n";
		outfile << "<identifier>, <integer>, <floating>, "
			<< "'(', 'true' or 'false' is expected"
			<< " after '-', '*' or '/'.\n";
		cerr << "Primary syntax error\n";
		cerr << "Invalid token, separator, or boolean value\n";
		cerr << "<identifier>, <integer>, <floating>, "
			<< "'(', 'true' or 'false' is expected"
			<< " after '-', '*' or '/'.\n";
		system("Pause");
		exit(1);
	}
}

void Par::Empty(ifstream& infile, ofstream& outfile)
{

}

void Par::printError(ofstream& outfile)
{
	outfile << "Error at line " << line << endl;
	cerr << "Error at line " << line<< endl;

	line = 1;
}


