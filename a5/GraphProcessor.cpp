#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

unordered_map<int,vector<int>> G;
map<int,vector<int>> com;
unordered_map<int,bool> visited;
unordered_map<int,int> parent;
map<pair<int,int>,int> weight;

void Tokenize(string line, vector<string> & tokens, string delimiters,int& num)
{
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
      num = (line.size()/2)+1;
}

void DFS_component(int v,vector<int>& ret)
{
	visited[v] = true;
	ret.push_back(v);
	if (G[v][0] == -1)
		return;
	for (int i=0; i< G[v].size(); i++)
	{
		if (!visited[G[v][i]])
		{
			parent[G[v][i]] = v;
			DFS_component(G[v][i], ret);

		}
	}	
}
bool find(int a,vector<int> temp)
{
	for (int i=0;i<temp.size();i++)
	{
		if (temp[i] == a)
			return true;
	}
	return false;
}
bool getCycles(int v,vector<int>& rek,int f,int c)
{
    visited[v] = true;
    rek.push_back(v);
    for (int i=0;i<G[v].size();i++)
    {
        if (!visited[G[v][i]])
        {	
        	parent[G[v][i]] = v;	
            if (getCycles(G[v][i],rek,f,++c))
            	return true;
        }
        else if (G[v][i] == f && c >2)
           return true;
    }
    return false;
}
void print_mini_edges(int v)
{
	visited[v] = true;
	int min,c;
	c =0;
	min = weight[pair<int,int>(v,G[v][0])];
	for (int i=0;i<G[v].size();i++)
	{
		if (!visited[G[v][i]])
		{
			if (min > weight[pair<int,int>(v,G[v][i])])
			{
				min = weight[pair<int,int>(v,G[v][i])];
				c = i;
			}
			if (weight[pair<int,int>(v,G[v][i])] == 1)
			{
				if (v > G[v][i])
					cout << G[v][i] << " " << v << endl;
				else
					cout << v << " " << G[v][i] << endl;
				parent[G[v][i]] = v;
				print_mini_edges(G[v][i]);
			}
		}
		
	}
	if (!visited[G[v][c]])
	{
		if (v > G[v][c])
			cout << G[v][c] << " " << v << endl;
		else
			cout << v << " " << G[v][c] << endl;
		parent[G[v][c]] = v;
		print_mini_edges(G[v][c]);
	}
}



int main (int argc,char** argv)
{
	vector<string> tokens;
	string line;
	ifstream fin;
	fin.open(argv[1]);
	int count = 0;
	while (getline(fin,line).good())
	{	
		Tokenize(line, tokens, " ",count);	
	}
	fin.close();

	int point,n,c;
	point = 0;
	n = 0;
	c = 0;

	for (int i=0;i<tokens.size();)
	{
		for (int j=0;j<count;j++)
		{
			if (tokens[i] != "0")
			{
				G[point].push_back(j);
				weight[pair<int,int>(point,j)] = atoi(tokens[i].c_str());
			}
			else
			{
				n++;
				if (n == count)
				{
					G[point].push_back(-1);
				}
			}
			i++;
		}
		n = 0;
		point++;
	}
	cout << "connected components:" << endl;
	vector<int> components;
	bool check;
	for (int i=0;i<count;i++)
	{
		for (int j=0;j<c;j++)
		{
			check = find(i,com[j]);
			if (check == true)
				break;
		}
		if (check == false)
		{
			DFS_component(i,components);
			sort(components.begin(),components.end());
			com[c] = components;
			c++;
			components.clear();
		}
	}
	for (auto it=com.begin();it!=com.end();it++)
	{
		cout << "{";
		for (int i=0;i<it->second.size();i++)
		{
			cout << it->second[i] << ",";
		}

		cout << "\b}" << endl;
	}

	visited.clear();
	parent.clear();
	components.clear();

	//step 2)
	check = false;
	for (int i=0;i<c;i++)
	{
		if (com[i].size() > 2)
		{
			for (int j=0;j<com[i].size();j++)
			{

				check = getCycles(com[i][j],components,com[i][j],0);
				if (check == true)
				{
					cout <<  "A cycle: ";
					for (int x=0;x<components.size();x++)
					{
						cout << components[x] << " ";
					}
					cout << endl;
					break;
				}
				components.clear();
			}
		}
	}
	if (check == false)
		cout << "No cycles" << endl;

	//step 3
	visited.clear();
	parent.clear();
	cout << "Edges in minimum spanning trees:" << endl;
	for (int i=0;i<c;i++)
	{
		if (com[i].size() > 1)
		{
			print_mini_edges(com[i][0]);
		}
	}
	return 0;
}