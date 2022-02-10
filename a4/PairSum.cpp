#include <iostream>
#include <vector>
#include "Utility.h"
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
	if (argc!=3){
		cout << "usage: executable.o n board\n example of board:(\"{0,0,1,0,0,-1,1,0,0}\")";
		return 1;
	}
	
	vector<string> tokens;
	vector<int> V;
	Tokenize(argv[1], tokens, "{,}");
	for (int i=0; i<tokens.size(); i++){
		V.push_back(atoi(tokens[i].c_str()));
	}
	

	map<int,int> track;
	map<int,int>::iterator it;
	for (int i=0; i<V.size(); i++)
		{
			track.insert(pair<int,int>(V[i],i));          		
		}
	int sum = atoi(argv[2]);



	for (int i=0;i<V.size();i++)
	{
		int temp = sum - V[i];
		it = track.find(temp);
		if (it != track.end() && it->second != i)
		{
			cout << "answer: (" << i << "," << it->second << ")" << endl;
			return 0;
		}
	}
	cout << "answer: (-1,-1)" << endl;
}