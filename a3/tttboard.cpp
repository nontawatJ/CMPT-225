#include "tttboard.h"
#include <vector>
#include <iostream>

using namespace std;

//step 1
tttboard::tttboard(int n){
	n_ = n;
	for (int i=0; i<n*n; i++)
		b_.push_back(0);
}
tttboard::tttboard(int n,vector<int> b)
{
	n_ = n;
	for (int i=0;i <n*n;i++)
		b_.push_back(b[i]);
}
ostream& operator << (ostream& output,const tttboard &b)
{
	output << "{";
	for(int i=0;i<b.b_.size();i++)
	{
		output << b.b_[i] << ",";
	}
	output << "\b}";
	return output;
}
bool tttboard::operator==(const tttboard &b)
{
	if (n_ != b.n_)
		return false;
	for (int i=0;i<n_*n_;i++)
	{
		if (b_[i] != b.b_[i])
			return false;
	}
	return true;
}
vector<int> tttboard::getb_() const
{
	return b_;
}
int tttboard::getn_() const
{
	return n_;
}

//step 2
vector<tttboard> tttboard::possibleNextBoards(int turn) const
{
	vector<tttboard> child;
	for (int i=0;i<n_*n_;i++)
	{
		tttboard temp(n_,b_);
		if (b_[i] == 0)
		{
			temp.b_[i] = turn;
			child.push_back(temp);
		}
	}
	return child;
}
