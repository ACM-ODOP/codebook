const int SIGMA_SIZE=26;
int fail[1000010],last[1000010];
int ch[1000010][26];
int val[1000010];
int idx(char c){return c-'a';}
void getfail()
{
	queue<int> q;
	fail[0]=0;
	for(int c=0;c<SIGMA_SIZE;c++)
	{
		int u=ch[0][c];
		if(u) {fail[u]=0;q.push(u);last[u]=0;}
	}
	while(!q.empty())
	{
		int r=q.front();q.pop();
		for(int c=0;c<SIGMA_SIZE;c++)
		{
			int u=ch[r][c];
			if(!u) continue;
			q.push(u);
			int v=fail[r];
			while(v && !ch[v][c]) v=fail[v];
			fail[u]= ch[v][c];
			last[u]=val[fail[u]]? fail[u]:last[fail[u]];
		}
	}
}
void find(char* T)
{
	int n=strlen(T);
	int j=0;
	for(int i=0;i<n;i++)
	{
		int c=idx(T[i]);
		while(j && !ch[j][c]) j=fail[j];
		j = ch[j][c];
		if(val[j]) print(j);
		else if(last[j]) print(last[j]);
	}
}
