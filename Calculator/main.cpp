//Calculator That read expression return value
//Yi Ge Di Gui Xia Jiang Parser
#include<iostream>
#include<sstream>
#include<string>
#include<map>
#include<cctype>
#include<cmath>
#include<exception>


using namespace std;

enum TokenValue{
	Name,
	Number,
	End,
	Plus = '+',
	Minus = '-',
	Mul = '*',
	Div = '/',
	Print = ';',
	Assign = '=',
	LP = '(',
	RP = ')'
};


//Global Storage
TokenValue	current = Print;		//Current Token
double		numberValue;			//number value storage
string		stringValue;			//String valuse storage

map < string, double > table;		//Symbol Table
istream* input;						//Input Stream

//Parser
double expr(bool get);				//Get expression
double term(bool get);				//Get term
double prim(bool get);				//Get primary

//Scanner
TokenValue getToken();				//Scan a token


//expression:
//		expression + term
//		expression - term
//		term
double expr(bool get)
{
	double left = term(get);	//Whether need to fetch a new token
								//The term eat all till a token that term can't handle ,just like + and -.
	for (;;)					//Whatever it goes, The token is in current
	{
		switch (current){		//so switch by current
		case Plus:				//if it is Plus,
		{
			left += term(true); //Retrive a right operand and do plus operation
			break;				//Back to the loop, Trying to eat more
		}
		case Minus:				//the same way as plus
		{
			left -= term(true); //Retrive a right operand for minus expression
			break;				///Back to the loop , Trying to eat more
		}
		default:				//If expr can't handle this token, return it to his papa
		{						//Give the value of this expresiion.
			return left;	//Other Token means end of this expression
		}
		}
	}
	return left;			//Return the final expression
}

//term:
//		term / primary
//		term * primary
//		primary
double term(bool get)
{
	double left = prim(get); //Get imply whether to fetch a new token
	for (;;)				//what ever, prim will eat all he can till one token he could't handle
	{
		switch (current) //if Mul and Div, the Term could handle that.
		{
		case Mul:
		{
			left *= prim(true);
			break;
		}
		case Div:
		{
			double divisor = prim(true);
			if (divisor == 0)		//Divisor zero check
			{
				//throw exception("Divide by zero!");
				cerr << "Divide by zero!";
			}
			left /= divisor;
			break;
		}
		default:		//return the value of the term as a whole
		{
			return left;
		}
		}
	}
	return left;
}

//Prim:
//		Number
//		Name
//		Name = expression
//		- primary
//		(expression)
double prim(bool get)
{
	if (get)		//get option
	{
		getToken();
	}
	switch (current)
	{
	case Number:		//I could handle Number
	{
		double v = numberValue; //If currentToken = Number,Then a number must be store in the variable numberValue
		getToken();				//Primary means the atomic type, So it won't try to eat more, Scan next token ,Whatever, I can't handle it
		return v;				//Return the primary element 's value as a whole. while leaving the new token to it's boss
	}
	case Name:
	{							//if a name is acquired
		if (stringValue == string("exit")) //Add specific command here;
		{
			exit(0);
		}							
		double& v = table[stringValue];   //Fetch the symbol table
		if (getToken() == Assign)		  //Oh , I could handle the lower level operation: Assign
		{
			v = expr(true);					//eat another expression as long as I can
		}
		return v;							//return the value assigned
	}
	case Minus:		//Unary
	{
		return -prim(true);					//After scanning a Unary Minus, eat a primary
	}
	case LP:			//Left Parenthese
	{
		double e = expr(true);	//Fetch a expression as long as I can
		if (current != RP)		//While expression cant't eat a right parenthese.So it will stop at it
		{
			//throw exception("Parenthese not match!");
			cerr << "Parenthese not match!";
		}
		getToken();	//Eat the right parenthese
		return e;	//return (expr) 's value as a primary element
	}
	default:
	{
		// throw exception("A primary element Excepted");
		cerr << "A primary element Excepted"; //except above all;
	}
	}
	return 0; //Deprecated
}

TokenValue getToken()
{
	char ch = 0;

	do// Blank Space Trim
	{
		if (!input->get(ch))
		{
			return current = End;
		}
	} while (ch != '\n' && isspace(ch)); //While ch is a space char(and not '\n')

	switch (ch)
	{
	case 0:
		return current = End;
	case ';':
	case '\n':
		return current = Print;
	case '*':
	case '/':
	case '+':
	case '-':
	case '(':
	case ')':
	case '=':
		return current = TokenValue(ch); //Index token value from enum
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '.':
		input->putback(ch);//If read one number by accident,putback
		*input>>numberValue;//Fetch the entire number
		return current = Number;
	default:
	{
		if (isalpha(ch))
		{
			stringValue = ch;
			while (input->get(ch) && isalnum(ch)) stringValue.push_back(ch);
			input->putback(ch);		//putback the extra char that taken from while loop
			return current = Name;
		}
		//throw exception("Bad Token");
		cerr << "bad Token";
		return Print;
	}
	}
}


int main(int argc,char** argv)
{
	switch (argc)
	{
	case 1:
	{
		input = &cin;
		break;
	}
	case 2:
	{
		input = new istringstream(argv[1]);
		break;
	}
	case 3:
	{
		cerr << "Too many arguments!";
		exit(1);
	}
	}


	table["pi"] = acos(-1);		//Set Symbol Table
	table["e"] = exp(1);

	input = &cin;

	while (*input)				//While instream exists
	{
		getToken();				//Get next(first) token
		if (current == End)		//exit when retivre 0
		{
			break;
		}
		if (current == Print)	//; then Cout << expr
		{
			continue;
		}
		cout << expr(false) << '\n';//Otherwise Fetch a expr;But Already take a token. So get is false
	}
	if (input != &cin)
	{
		delete input;			//Wipe hip
	}
	return 0;

}