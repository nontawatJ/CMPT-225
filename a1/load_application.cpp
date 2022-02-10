#include "loan_application.h"
#include <iostream>
using namespace std;

loan_application::loan_application()
{
	applicant_full_name = "";
	years_of_relevant_education = 0;
	years_of_relevant_experience = 0;
	loan_amount = 0;
	application_type =0;
	date = "";
}
loan_application::loan_application(const string &FN,const int &YOREd,const int &YOREx,const int &LA,const int* EYP)
{
	applicant_full_name = FN;
	years_of_relevant_education = YOREd;
	years_of_relevant_experience = YOREx;
	loan_amount = LA;
	for (int i=0;i<30;i++)
	{
		estimated_yearly_profits[i] = EYP[i];
	}

}
loan_application::loan_application(const string &FN,const int &YOREd,const int &YOREx,const int &LA,const int* EYP,const string &date)
{
	applicant_full_name = FN;
	years_of_relevant_education = YOREd;
	years_of_relevant_experience = YOREx;
	loan_amount = LA;
	for (int i=0;i<30;i++)
	{
		estimated_yearly_profits[i] = EYP[i];
	}
	this->date = date;
}
string loan_application::getDate() const
{
	return date;
}
void loan_application::setDate(const string &date)
{
	this->date = date;
}
string loan_application::getName() const
{
	return applicant_full_name;
}
int loan_application::getYOREd () const
{
	return years_of_relevant_education;
}
int loan_application::getYOREx () const
{
	return years_of_relevant_experience;
}
int loan_application::getLA() const
{
	return loan_amount;
}
const int* loan_application::getEYP() const
{
	return estimated_yearly_profits;
}
float loan_application::priority() const
{
	float prio = 0;
	for (int i=0;i<30;i++)
	{
		prio = prio + ((1.0/(i+1)) * estimated_yearly_profits[i]);
	}
	return prio;
}
bool loan_application::operator < (const loan_application &rhs) const
{
	return priority() > rhs.priority();
}
bool loan_application::operator <= (const loan_application &rhs) const
{
	return priority() >= rhs.priority();
}
bool loan_application::operator > (const loan_application &rhs) const
{
	return priority() < rhs.priority();
}
bool loan_application::operator >= (const loan_application &rhs) const
{
	return priority() <= rhs.priority();
}
bool loan_application::operator == (const loan_application &rhs) const
{
	return priority() == rhs.priority();
}
bool loan_application::operator != (const loan_application &rhs) const
{
	return priority() != rhs.priority();
}
ostream& operator << (ostream &output,const loan_application &rhs )
{
	if (rhs.date == "")
		output << "(" << rhs.applicant_full_name << "," << rhs.loan_amount << ")";
	else
		output << "(" << rhs.applicant_full_name << "," << rhs.loan_amount << "," << rhs.date << ")";
	return output;
	
}