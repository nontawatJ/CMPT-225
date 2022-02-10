#ifndef TTTBOARD_H
#define TTTBOARD_H

#include <iostream>
#include <vector>

using namespace std;

class tttboard
{
private:
 	vector<int> b_;
	int n_;	
	
public:
	//step 1
	tttboard(int n=3);
	tttboard(int n, vector<int> b);
	friend ostream& operator << (ostream& output,const tttboard &b);
	bool operator == (const tttboard &b);
	vector<int> getb_() const;
	int getn_() const;

	//step 2
	vector<tttboard> possibleNextBoards(int turn) const;
};

#endif 