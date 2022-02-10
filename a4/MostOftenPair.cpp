#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include "Utility.h"
using namespace std;

int main()
{

	unordered_map<n_gram,int,n_gram_hash> bigram_counts;
	map<string,string> track;
	map<string,string>::iterator it;

	ifstream inf("MostOftenPair_input.txt");
	string line;
	vector<string> tokens;
	while (getline(inf,line).good())
	{
		Tokenize(line, tokens, "\t");
	}		
		for (int i=0; i<tokens.size(); i+=2)
		{
			
			it = track.find(tokens[i+1]);
			if (it != track.end())
			{
				if (it->second == tokens[i])
				{
					n_gram x = n_gram(2,{tokens[i+1],tokens[i]});
					bigram_counts[x]++;
				}
				else
				{
					n_gram x = n_gram(2,{tokens[i],tokens[i+1]}); 
           			bigram_counts[x]++;	
           			track.insert(pair<string,string>(tokens[i],tokens[i+1]));
				}
			}
			else
			{
				n_gram x = n_gram(2,{tokens[i],tokens[i+1]}); 
           		bigram_counts[x]++;	
           		track.insert(pair<string,string>(tokens[i],tokens[i+1]));
			}	
		}
	

	for (auto itr2=bigram_counts.begin(); itr2!=bigram_counts.end(); itr2++)
	{
		cout << itr2->first << itr2->second << endl;
	}

	int highest = 0;
	unordered_map<n_gram,int,n_gram_hash>::iterator it2;
	it2 = bigram_counts.end();
	for (auto itr2=bigram_counts.begin(); itr2!=bigram_counts.end(); itr2++)
	{
		if (itr2->second > highest)
		{
			highest = itr2->second;
			it2 = itr2;
		}
	}
	if (it2 == bigram_counts.end())
		cout << "no pair to count for # of occurrence" << endl;
	else
		cout << it2->first.getWords()[0] << " and " << it2->first.getWords()[1] << " occurred together most often: #occurrence=" << it2->second << endl;        	 	
}