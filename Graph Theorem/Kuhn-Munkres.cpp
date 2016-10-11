struct Hungary
{
	int M,N;
	LL EDGE[500][500];
	LL WA[500],WB[500],LOW[500];
	int MATCH[500];
	bool VA[500],VB[500];
	bool Match(const int u)
	{
		if(VA[u])return false;
		VA[u]=true;
		for(int nxt=0;nxt<N;nxt++)
		{
			const LL &edge=EDGE[u][nxt];
			if(edge==WA[u]+WB[nxt])
			{
				VB[nxt]=true;
				if(MATCH[nxt]==-1||Match(MATCH[nxt]))
				{
					MATCH[nxt]=u;
					return true;
				}
			}
			else
			{
				assert(edge<WA[u]+WB[nxt]);
				getmin(LOW[nxt],WA[u]+WB[nxt]-edge);
			}
		}
		return false;
	}
	void Update()
	{
		LL low=INF;
		for(int i=0;i<N;i++)if(!VB[i])getmin(low,LOW[i]);
		assert(low!=INF);
		for(int i=0;i<M;i++)if(VA[i])WA[i]-=low;
		for(int i=0;i<N;i++)if(VB[i])WB[i]+=low;
	}
	void Solve()
	{
		for(int i=0;i<M;i++)
		{
			WA[i]=0;
			for(int j=0;j<N;j++)getmax(WA[i],EDGE[i][j]);
		}
		for(int i=0;i<N;i++)WB[i]=0,MATCH[i]=-1;
		for(int i=0;i<M;i++)
		{
			for(;;)
			{
				for(int j=0;j<M;j++)VA[j]=false;
				for(int j=0;j<N;j++)VB[j]=false,LOW[j]=INF;
				if(Match(i))break;
				else Update();
			}
		}
	}
}
