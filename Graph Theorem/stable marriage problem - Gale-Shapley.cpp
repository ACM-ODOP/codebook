//Propose-and-reject algorithm
int pref[maxn][maxn],order[maxn][maxn],next[maxn];
int future_husband[maxn], future_wife[maxn];
queue<int> q;

void engage(int man,int woman)
{
	int m=future_husband[woman];
	if(m)
	{
		future_wife[m]=0;
	    q.push(m);
	}
	future_wife[man] = woman;
	future_husband[woman] = man;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);

		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
				scanf("%d",&pref[i][j]);
			next[i]=1;
			future_wife[i]=0;
			q.push(i);
		}

		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				int x;
				scanf("%d",&x);
				order[i][x]=j;
			}
			future_husband[i]=0;
		}

		while(!q.empty())
		{
			int man=q.front();q.pop();
			int woman = pref[man][next[man]++];
			if(!future_husband[woman])
				engage(man,woman);
			else if(order[woman][man] < order[woman][future_husband[woman]])
				engage(man,woman);
			else q.push(man);
		}
		while(!q.empty()) q.pop();

		for(int i=1;i<=n;i++) printf("%d\n",future_wife[i]);
		if(T) printf("\n");
	}
	return 0;
}
