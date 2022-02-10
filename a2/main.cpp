#include <iostream>
#include "genericLinkedListStack.h"
#include "postfixUtility.h"
#include <string>
using namespace std;

int main(int argc,char* argv[])
{
	string postfix = getPostfix(argv[1]);
	float ans = evaluatePostfix(postfix);
	cout << ans << endl;

	return 0;
}