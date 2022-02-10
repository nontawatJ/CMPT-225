#include <string>
using namespace std;

class loan_application
{
private:
	string applicant_full_name;
	int years_of_relevant_education;
	int years_of_relevant_experience;
	int loan_amount;
	int estimated_yearly_profits[30];
	int application_type;
	string date;
public:
	loan_application();
	loan_application(const string &FN,const int &YOREd,const int &YOREx,const int &LA,const int* EYP);
	loan_application(const string &FN,const int &YOREd,const int &YOREx,const int &LA,const int* EYP,const string &date);
	string getName() const;
	string getDate() const;
	void setDate(const string &date);
	int getYOREx() const;
	int getYOREd() const;
	int getLA() const;
	const int* getEYP() const;
	float priority()const;
	bool operator  < (const loan_application &rhs) const;
	bool operator <= (const loan_application &rhs) const;
	bool operator > (const loan_application &rhs) const;
	bool operator >= (const loan_application &rhs) const;
	bool operator == (const loan_application &rhs) const;
	bool operator != (const loan_application &rhs) const;
	friend ostream& operator << (ostream &ouput,const loan_application &rhs);
	

};