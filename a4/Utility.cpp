#include <iostream>
#include <vector>
#include <algorithm>
#include "Utility.h"
using namespace std;

bool n_gram::operator==(const n_gram& ng) const
{
        if (n_ != ng.getN())
                return false;
        for (int i=0;i<words_.size();i++)
        {
             if (words_[i] != ng.getWords()[i])
                return false;
        }
        return true;

}
vector<string> n_gram::getWords() const
{
        return words_;
}
int n_gram::getN() const
{
        return n_;
}

ostream& operator<<(ostream& out, const n_gram& ng){
                out << "(";
                for (int i=0; i<ng.n_-1; i++)
                        out << ng.words_[i] << ",";
                out << ng.words_[ng.n_-1]<< ")";
                return out;
        }

void Tokenize(string line, vector<string> & tokens, string delimiters){
	string token = "";
        string OneCharString = " ";
        for (int i=0; i<line.size(); i++)
                if (find(delimiters.begin(), delimiters.end(), line[i])!=delimiters.end()) // line[i] is one of the delimiter characters
                {
                        if (token != "")
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

n_gram_hash::n_gram_hash()
{
        srand((unsigned)time(0));
        a_ = rand();
        while (a_==0)
                a_ = rand();
}
int p (int a, int b)
{
        int temp = 1;
        for (int i=1;i<=b;i++)
        {
                temp = temp * a;
        }
        return temp;
}
std::size_t n_gram_hash::operator () (const n_gram & ng) const{
        int s=0;
       
        for (int i=0;i<ng.getWords().size();i++)
        {
                for (int j=0;j<ng.getWords()[i].size();j++)
                {
                        s = s + ((int)ng.getWords()[i][j]*p(a_,ng.getWords()[i].size()-(i+1)));
                }
                
        }
        return s;
}