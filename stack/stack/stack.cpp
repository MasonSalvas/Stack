// stack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Header.h"
//#include "swag.h" #baller

using namespace std;

int precedence(char bling)		//gets to see which operators take prioity over others 
{
	switch (bling)
	{
	case '*':
	case '/':
	case '%':
		return 3;

	case '+':
	case '-':
		return 2;

	case ')':
	case '(':
		return 1;

	default:
		return 0;
	}
}
template <class T>
void getTwoOffStack (stack<T>& theStack, T& first, T& second)
{
	//this function gets the top two numbers off the stack

	second = theStack.top ();

	theStack.pop ();

	first = theStack.top ();

	theStack.pop ();
}

float postfixCalculate (string& Express)
{
	//This function will do the calcualtions from a post fix expression

	stack<float> hadouken;            //float stack

	float first, second;

	for (int n = 0; n < Express.length(); n++)
	{
		char c = Express[n];
		if(isspace (c))
		{
			continue;
		}

		else if(isdigit (c))
		{
			int value = 0;
			while(isdigit(Express[n]))
			{
				value = 10 * value + (Express[n] - '0');
				n++;
			}
			hadouken.push(value);
		}

		//For each item in the postfix expression from the left:

		else
		{
			switch (c)
			{
				//if the item is an operator (+,-,*,%, or /) then
				//      pop two numbers off the stack
				//      make a calculation:  the second number 
				//      popped-operator-first number
				//      push the result on the stack

			case '*':
				getTwoOffStack (hadouken, first, second);
				hadouken.push (first * second);
				break;

			case '/':
				getTwoOffStack (hadouken, first, second);
				hadouken.push (first / second);
				break;

			case '%':
				getTwoOffStack (hadouken, first, second);
				hadouken.push ((int)first % (int)second);
				break;

			case '+':
				getTwoOffStack (hadouken, first, second);
				hadouken.push (first + second);
				break;

			case '-':
				getTwoOffStack (hadouken, first, second);
				hadouken.push (first - second);
				break;

				//if the item is a number push it on the stack

			default:
				break;
			}
		}

	}
	//When the loop is done, the answer is the only value left on the stack.

	float returnVal = hadouken.top ();

	hadouken.pop ();

	return returnVal;
}
int main()
{
	string expr;					//used for the input for the getting the expression from the input file 
	stack<char> stk;				//the stack used to rearrange the operators for postfix
	float answer = 0;				//gets the answer of the expression
	ifstream in("expr.dat");		//the instream for getting the original expression
	ifstream in_calc("postexpr.dat");//the instream file getting the 
	ofstream out("postexpr.dat");	//will output the file to postexpr.dat file
	ofstream answerout("answer.dat");//will output the answer to a final file

	while(!in.eof())
	{

		getline(in, expr);

		for (int i = 0; i < expr.length(); i++)
		{
			char c = expr[i];
			if(isspace (c))
			{
				continue;
			}

			else if(isdigit (c))
			{
				int value = 0;
				while(isdigit(expr[i]))
				{
					value = 10 * value + (expr[i] - '0');
					i++;
				}
				i--;
				cout<<value<<" ";
				out<<value<<" ";
				answerout<<value<<" ";
			}

			else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
			{
				int muney = precedence(c);
				while(!stk.isEmpty() &&  muney <= precedence(stk.top()))
				{
					cout<<stk.top()<<" ";
					out<<stk.top()<<" ";
					answerout<<stk.top()<<" ";
					stk.pop();
				}

				stk.push(c);
			}

			else if(c == '(')
			{
				stk.push(c);
			}

			else if(c == ')')
			{

				while(stk.top() != '(')
				{
					cout<<stk.top()<<" ";
					out<<stk.top()<<" ";
					answerout<<stk.top()<<" ";
					stk.pop();
				}
				stk.pop();
			}

		}

		while(!stk.isEmpty())
		{
			if(stk.top() == '(')
			{
				cout<<"";
				out<<"";
				answerout<<"";
			}
			else
			{
				cout<<stk.top()<<" ";
				out<<stk.top()<<" ";
				answerout<<stk.top()<<" ";
			}
			stk.pop();
		}
		cout<<endl;
		out<<endl;
		answerout<<endl;
	}

	while(!in_calc.eof())
	{
		getline(in_calc, expr);
		if(!expr.empty())
		{
			answer = postfixCalculate(expr);
			cout<<"The answer is: "<<answer<<endl;
			answerout<<"The answer is: "<<answer<<endl;
		}
	}

	return 0;
}






