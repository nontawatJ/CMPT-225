#include "tttboard.h"
#include "gTree.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void Tokenize(string line, vector<string> & tokens, string delimiters = "\t "){
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
int getTurn(vector<int> b)
{
	int s = 0; 
	for (int i=0; i<b.size(); i++)
		s+=b[i];
	if (s==0)
		return 1;
	else 
		return -1;
}
//step 3
bool check_if_boardfull(vector<int> b)
{
	for (int i=0;i<b.size();i++)
	{
		if (b[i] == 0)
			return false;
	}
	return true;
}
void generate_hold_tree(gTNode<tttboard>* v)
{
	if (check_if_boardfull(v->getData().getb_()))
		return;
	int turn = getTurn(v->getData().getb_());
	vector<tttboard> possible_child = v->getData().possibleNextBoards(turn);
	for (int i=0;i<possible_child.size();i++)
	{
		v->addChild(possible_child[i]);
		vector<gTNode<tttboard>*> ch = v->getChildren(); 
        generate_hold_tree(ch[i]);   
	}
}
//step 4
int check_win_or_notSure(gTNode<tttboard>* v)
{
	vector<int> temp = v->getData().getb_();
	int n = v->getData().getn_();
	int count = 0;
	//horzontal
	for (int i=0;i<n*n;i+=n)
	{
		for (int j=i;j<i+n;j++)
		{
			count += temp[j];
		}
		if (count == n || count == -1*n)
			return 1;//win
		count = 0;
	}
	//vertical 
	for (int i=0;i<n;i++)
	{
		for (int j=i;j<=i+(n*(n-1));j+=n)
		{
			count += temp[j];
		}
		if (count == n || count == -1*n)
			return 1;//win
		count = 0;
	}
	//diagonal
	for (int i=0;i<n*n;i+=(n+1))
	{
		count += temp[i];
	}
	if (count == n || count == -1*n)
			return 1;//win
	count = 0;
	for (int i=n-1;i<n*n;i+=(n-1))
	{
		count += temp[i];
	}
	if (count == n || count == -1*n)
			return 1;//win
	return 0;//no win or not sure
}
int check_the_board(gTNode<tttboard>* v)
{
	/*if all child is 1 then return -1 ;
	if one child contain -1 then return 1;
	if one child contain 0 and the rest is 1 return 0;*/

	if (check_if_boardfull(v->getData().getb_()))
	{
		if (check_win_or_notSure(v) == 1)
			return -1;
		else
			return 0;
	}
	if (check_win_or_notSure(v) == 1)
		return -1;
	else
	{
		int count = 0;
		int turn = getTurn(v->getData().getb_());
		vector<tttboard> possible_child = v->getData().possibleNextBoards(turn);
		for (int i=0;i<possible_child.size();i++)
		{
			v->addChild(possible_child[i]);
			vector<gTNode<tttboard>*> ch = v->getChildren();
			int check = check_the_board(ch[i]);
			if (check == -1)
			{
				return 1; 
			}
			else if (check == 1)
				count++;
		}
		if (count == possible_child.size())
			return -1;
	}
}

int main (int argc,char** argv)
{
	if (argc == 2)
	{
		int n = atoi(argv[1]);
		tttboard root(n);
		gTree<tttboard> tttTree;
		tttTree.addNode(root,NULL);
		generate_hold_tree(tttTree.getRoot());
		cout << "preorder:\n";
		preorderPrint(tttTree.getRoot());
		cout <<"\npostorder:\n";
		postorderPrint(tttTree.getRoot());
		cout << "\nsize:" << size(tttTree.getRoot())<< endl;
	}
	
	else if (argc == 3)
	{
		int n = atoi(argv[1]);
		string str_board = argv[2];
		vector<string> tokens;
		Tokenize(str_board,tokens," {,}");
		vector<int> board;
		for (int i=0; i<tokens.size(); i++)
		{
			board.push_back(atoi(tokens[i].c_str()));
		}
		tttboard root(n,board);
		gTree<tttboard> tttTree;
		tttTree.addNode(root,NULL);
		int check = check_the_board(tttTree.getRoot());
		if (check == 1)
			cout << "winning board" << endl;
		else if (check == -1)
			cout << "losing board" << endl;
		else
			cout << "not sure" << endl;
	}
}