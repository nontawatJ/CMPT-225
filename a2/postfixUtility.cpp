#include "postfixUtility.h"
#include "genericLinkedListStack.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stack>
using namespace std;

bool checkOperator(const char &o)
{
	if ( (o == '-') || (o == '+') || (o == '*') || (o == '/') )
		return true;
	return false;
}
bool checkOrder(const char &o1,const char &o2)
{
	int t1,t2;
	if ( (o1 == '+') || (o1 == '-') )
		t1 = 1;
	else 
		t1 = 2;
	if ( (o2 == '+') || (o2 == '-') )
		t2 = 1;
	else 
		t2 = 2;
	return t1 >= t2;
}
string getPostfix(string nexp)
{
	stack<char> oper;
	string postfix = "";
	for (int i=0;i<nexp.length();i++)
	{
		if (nexp[i] == '(')
		{
			oper.push(nexp[i]);
		}
		else if (nexp[i] == ')')
		{
				while ( (!oper.empty()) && (oper.top() != '(') )
			{
				postfix = postfix + " " + oper.top();
				oper.pop();
			}
			oper.pop();
		}
		else if (checkOperator(nexp[i]))
		{
			while ( (!oper.empty()) && (oper.top() != '(') && (checkOrder(oper.top(),nexp[i]) ) )
			{
				postfix = postfix + " " + oper.top();
				oper.pop();
			}
			oper.push(nexp[i]);
			postfix += " ";
		}
		else if (nexp[i] == ' ')
			continue;
		else
			postfix = postfix + nexp[i];
	}
	while (!oper.empty())
	{
		postfix = postfix  + " " + oper.top();
		oper.pop();
	}
	return postfix;

}
float cal(char oper,float n1,float n2)
{
	if (oper == '+')
		return n1+n2;
	else if (oper == '-')
		return n1-n2;
	else if (oper == '*')
		return n1*n2;
	else
		return n1/n2;
}
float evaluatePostfix(string pexp)
{
	string n = "";

	genericLinkedListStack<string> num;
	genericLinkedListStack<float> result;
	for (int i=0;i<pexp.size();i++)
	{
		if (pexp[i] == ' ')
			continue;
		else if (checkOperator(pexp[i]))
		{	
			if (num.empty())
			{
				float a = result.top();
				result.pop();
				float b = result.top();
				result.pop();
				float c = cal(pexp[i],b,a);
				result.push(c);
			}
			else
			{
				float a = atof (num.top().c_str());
				num.pop();
				if (num.empty())
				{
					float b = result.top();
					result.pop();
					float c = cal(pexp[i],b,a);
					result.push(c);
				}
				else
				{
					float b = atof (num.top().c_str());
					num.pop();
					float c = cal(pexp[i],b,a);
					result.push(c);
				}
			}
		}
		else
		{
			int j = i;
			while (pexp[j] != ' ')
			{
				n = n + pexp[j];
				j++;
			}
			num.push(n);
			n = "";
			i=j;
		}
	}
	return result.top();		
}