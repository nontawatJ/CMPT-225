#include <string>
using namespace std;

bool checkOperator(const char &o);
bool checkOrder(const char &o1,const char &o2);
string getPostfix(string nexp);
float cal(char oper,float n1,float n2);
float evaluatePostfix(string pexp);