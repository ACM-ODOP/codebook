struct Edge{int from,to,w;};
struct Chu_Liu
{
	int n,size;
	vector<Edge> edges;
	void init(int n)
	{
		this->n=n;
		edges.clear();
	}
	void AddEdge(int from,int to,int w)
	{
		edges.push_back((Edge){from,to,w});
	}
	int fa[maxn],no[maxn],v[maxn],in[maxn];
	bool removed[maxn];
	int MDST(int s)
	{
		int w1=0,w2=0;
		memset(removed,0,sizeof removed);
		size=edges.size();
		for(;;)
		{
			w1=0;
			memset(fa,-1,sizeof fa);
			memset(no,-1,sizeof no);
			memset(v,-1,sizeof v);
			for(int i=0;i<n;i++) in[i]=INF;
			for(int i=0;i<size;i++)
			{
				Edge& e=edges[i];
				if(e.from!=e.to && in[e.to]>e.w)
				{
					fa[e.to]=e.from;
					in[e.to]=e.w;
				}
			}

			bool loop=0;
			for(int i=0;i<n;i++)
			{
				if(removed[i]||i==s) continue;
				if(fa[i]==-1) return -1;
				else w1+=in[i];
				int now=i;
				while(now!=-1 && v[now]==-1) v[now]=i,now=fa[now];
				if(now!=-1 && v[now]==i)
				{
					loop=1;
					int j=now;
					for(;;)
					{
						no[j]=now,removed[j]=1,w2+=in[j];
						j=fa[j];
						if(j==now) break;
					}
					removed[now]=0;
				}
			}
			if(!loop) break;

			for(int i=0;i<size;i++)
			{
				Edge& e=edges[i];
				if(no[e.to]>=0) e.w-=in[e.to],e.to=no[e.to];
				if(no[e.from]>=0) e.from=no[e.from];
				if(e.from==e.to) edges[i--]=edges[--size];
			}
		}
		return w1+w2;
	}
};
