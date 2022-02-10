#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "SortedArrayList.h"
#include "loan_application.h"
#include <algorithm>
using namespace std;


void Tokenize(string line, vector<string> & tokens, string delimiters = "\t ")
{
string token = "";
        string OneCharString = " ";
        for (int i=0; i<line.size(); i++)
                if (find(delimiters.begin(), delimiters.end(), line[i])!=delimiters.end()) // line[i] is one of the delimiter characters
                {
			if (token.size()>0)
                        	tokens.push_back(token);
                        token = "";
                }
                else
                {
                        OneCharString[0] = line[i];
                        token +=OneCharString;
                }

        if (token != "")
                tokens.push_back(token);
}

void make_decisions (string decision_date,int &budget,SortedArrayList<loan_application> &AT,SortedArrayList<loan_application> &AP,SortedArrayList<loan_application> &DN)
{
	int count = AT.count();
	for (int i=0;i<count;i++)
	{
		if (AT[i].getYOREd() + AT[i].getYOREx() < 10 )
		{
			AT[i].setDate(decision_date);
			DN.add(loan_application(AT[i].getName(),AT[i].getYOREd(),AT[i].getYOREx(),AT[i].getLA(),AT[i].getEYP(),decision_date));
			AT.removeFirst(AT[i]);
			i--;
			count--;
		}
		else if (AT[i].getLA() <= budget)
		{
			AT[i].setDate(decision_date);
			AP.add(loan_application(AT[i].getName(),AT[i].getYOREd(),AT[i].getYOREx(),AT[i].getLA(),AT[i].getEYP(),decision_date));
			budget = budget - AT[i].getLA();
			AT.removeFirst(AT[i]);
			i--;
			count--;
		}
		
	}
}






int main(int argc,char* argv[])
{

	vector<std::string> SA;
	ifstream inf;
	inf.open(argv[1]);
	string line ;
	while (getline(inf,line).good())
	{
		Tokenize(line,SA,"\t");
	}
	inf.close();


	//count how many application,print and make decision
	int count =0;
	int deci = 0;
	int prin = 0;
	for (int i=0;i<SA.size();i++)
	{
		if (SA[i] == "save_application")
		{
			count++;
		}
		else if (SA[i] == "make_decisions")
		{
			deci++;
		}
		else if (SA[i] == "print")
		{
			prin++;
		}
		
	}
	

	
	//all the declaration needed
	string name[5000];
	int EYP[5000][30];
	int YOREd[5000];
	int YOREx[5000];
	int LA[5000];
	int E[30];
	int c = 0;
	int t,t2,t3 = 0;
	int a = 0;
	int number_of_loan_application = 0;
	string* date = new string[deci];
	int* budget = new int[deci];
	SortedArrayList<loan_application> active_applications(5000);
	SortedArrayList<loan_application> denied_applications(5000);
	SortedArrayList<loan_application> approved_applications(5000);

	
	//convert string to int 
	while (a < SA.size())
	{
		c = 0;
		t3 = 0;
		if (SA[a] == "save_application")
		{
			if (number_of_loan_application == 5000)
			{
				cout << "The bank only takes a maximum of 5000 loan applications" << endl;
				return 0;
			}
			name[t] = SA[a+1];
			for (int j=a+5;;j++)//year profits
			{
				if ( (SA[j] == "save_application") || (SA[j] == "make_decisions") || (SA[j] == "print") )
					break;
				EYP[t][c] = atoi (SA[j].c_str());
				t3++;//count how many array
				c++;
			} 
			YOREd[t] = atoi (SA[a+2].c_str());//years of edu
			YOREx[t] = atoi (SA[a+3].c_str());//years of exp
			LA[t] = atoi (SA[a+4].c_str());//loan amount
			//change estimate_year_profit from 2 dimension to 1 
			for (int j=0;j<t3;j++)
			{
				E[j] = EYP[t][j];
			}
			//check the limit for loan applications
			
			active_applications.add(loan_application(name[t],YOREd[t],YOREx[t],LA[t],E));
			number_of_loan_application++;
			

		}
		else if (SA[a] == "make_decisions")
		{
			for (int j=a+2;;j++)
			{
				if ( (SA[j] == "save_application") || (SA[j] == "make_decisions") || (SA[j] == "print") )
					break;
				budget[t2] = atoi (SA[a+2].c_str());//budget
				date[t2] = SA[a+1];//change from 2 dimension to 1 for date
			}
			make_decisions(date[t2],budget[t2],active_applications,approved_applications,denied_applications);
			t2++;
		}
		else if (SA[a] == "print")
		{
			cout << "active_applications\t";
			active_applications.print();
			cout << "approved_applications\t";
			approved_applications.print();
			cout << "denied_applications\t";
			denied_applications.print();
		}
		a++;
	}
	


	return 0;
}

