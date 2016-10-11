struct Edge
{
	int from,to,cap,flow,cost;
};
struct MCMF
{
	int n,s,t;
	vector<Edge> edges;
	vector<int> G[maxn];
	int d[maxn],p[maxn],a[maxn];
	bool inq[maxn];
	void init(int n)
	{
		this->n=n;
		for(int i=0;i<n;i++) G[i].clear();
		edges.clear();
	}
	void AddEdge(int from,int to,int cap,int cost)
	{
		edges.push_back((Edge){from,to,cap,0,cost});
		edges.push_back((Edge){to,from,0,0,-cost});
		int m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	bool bellmanford(int& flow,LL& cost)
	{
		for(int i=0;i<n;i++) d[i]=INF;
		memset(inq,0,sizeof(inq));
		d[s]=0;inq[s]=1;p[s]=0;a[s]=INF;

		queue<int> Q;
		Q.push(s);
		while(!Q.empty())
		{
			int now=Q.front();Q.pop();
			inq[now]=0;
			for(int i=0;i<G[now].size();i++)
			{
				Edge& e=edges[G[now][i]];
				if(e.cap>e.flow && d[e.to]>d[now]+e.cost)
				{
					d[e.to]=d[now]+e.cost;
					p[e.to]=G[now][i];
					a[e.to]=min(a[now],e.cap-e.flow);
					if(!inq[e.to]) {Q.push(e.to);inq[e.to]=1;}
				}
			}
		}
		if(d[t]==INF) return false;
		flow+=a[t];
		cost+=(LL)d[t]*(LL)a[t];
		int now=t;
		while(now!=s)
		{
			edges[p[now]].flow+=a[t];
			edges[p[now]^1].flow-=a[t];
			now=edges[p[now]].from;
		}
		return 1;
	}
	int Mincost(int s,int t,LL& cost)
	{
		int flow=0;
		this->s=s,this->t=t;
		while(bellmanford(flow,cost));
		return flow;
	}
};
