struct Edge
{
	int from,to,cap,flow;
};
struct Dinic
{
	int n,s,t;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool vis[maxn];
	int d[maxn],cur[maxn];
	void init(int n)
	{
		this->n=n;
		for(int i=0;i<n;i++) G[i].clear();
		edges.clear();
	}
	void AddEdge(int from,int to,int cap)
	{
		edges.push_back((Edge){from,to,cap,0});
		edges.push_back((Edge){to,from,0,0});
		int m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	bool BFS()
	{
		memset(vis,0,sizeof(vis));
		queue<int> Q;
		Q.push(s);
		d[s]=0;
		vis[s]=1;
		while(!Q.empty())
		{
			int now=Q.front();Q.pop();
			for(int i=0;i<G[now].size();i++)
			{
				Edge& e=edges[G[now][i]];
				if(!vis[e.to] && e.cap>e.flow)
				{
					vis[e.to]=1;
					d[e.to]=d[now]+1;
					Q.push(e.to);
				}
			}
		}
		return vis[t];
	}

	int DFS(int now,int a)
	{
		if(now==t || a==0) return a;
		int flow=0,f;
		for(int& i=cur[now];i<G[now].size();i++)
		{
			Edge& e=edges[G[now][i]];
			if(d[now]+1==d[e.to] && (f=DFS(e.to,min(a,e.cap-e.flow)))>0)
			{
				e.flow+=f;
				edges[G[now][i]^1].flow-=f;
				flow+=f;
				a-=f;
				if(a==0) break;
			}
		}
		return flow;
	}
	int Maxflow(int s,int t)
	{
		this->s=s,this->t=t;
		int flow=0;
		while(BFS())
		{
			memset(cur,0,sizeof(cur));
			flow+=DFS(s,INF);
		}
		return flow;
	}
};
