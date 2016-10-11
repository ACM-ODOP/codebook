#include<bits/stdc++.h>
using namespace std;
const int maxnode=100000;
const int sigma_size=26;
struct Trie
{
	int ch[maxnode][sigma_size];
	int val[maxnode];
	int sz; // number of nodes
	Trie() {sz=1;memset(ch[0],0,sizeof(ch[0]));}// only root
	int idx(char c){return c-'a';}

	// insert string s , information is v. v is not zero.
	void insert(char *s,int v)
	{
		int u=0,n=strlen(s);
		for(int i=0;i<n;i++)
		{
			int c=idx(s[i]);
			if(!ch[u][c])
			{
				memset(ch[sz],0,sizeof(ch[sz]));
				val[sz]=0; // intermediate nodes' information is zero(not exist)
				ch[u][c]=sz++; // new node
			}
			u = ch[u][c]; // keep going!!
		}
		val[u]=v; // val assigned to the last character
	}
};
int main()
{

}
