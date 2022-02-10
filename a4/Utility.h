#ifndef STRING_UTILITY_H
#define STRING_UTILITY_H
#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <math.h>
using namespace std;

class n_gram{
public:
        n_gram(int n, const vector<string>& v):n_(n), words_(v){}
        vector<string> getWords() const;
        int getN() const;
        friend ostream& operator<<(ostream& out, const n_gram& ng);
        bool operator==(const n_gram& ng) const ;
private:
        int n_;
        vector<string> words_;

};

void Tokenize(string line, vector<string> & tokens, string delimiters = "\t ");
int p (int a, int b);

class n_gram_hash
{
private:
	int a_;
public:
	n_gram_hash();
	std::size_t operator () (const n_gram& ng) const;

};

#endif