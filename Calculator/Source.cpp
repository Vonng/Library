#include<vector>
using namespace std;

typedef int token;

class Expression
{
};

class NumberExpression : Expression
{
	token value;
};

class BinaryExpression : Expression
{
	enum BinaryOperator
	{
		Add,
		Sub,
		Mul,
		Div,
	};

	Expression firstOperand;
	Expression secondOperand;
	BinaryOperator binaryOperator;
};

class FunctionExpression : Expression
{
	token functionName;
	vector<Expression> arguments;
};
