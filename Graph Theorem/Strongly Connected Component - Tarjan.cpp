int dfs_clock,scc_cnt,pre[maxn],sccno[maxn],lowlink[maxn];
stack<int> S;
void dfs(int now)
{
	lowlink[now]=pre[now]=++dfs_clock;
	S.push(now);
	for(int i=0;i<G[now].size();i++)
	{
		int to=G[now][i];
		if(!pre[to])
		{
			dfs(to);
			lowlink[now]=min(lowlink[to],lowlink[now]);
		}
		else if(!sccno[to]) lowlink[now]=min(lowlink[now],pre[to]);
	}

	if(lowlink[now]==pre[now])
	{
		scc_cnt++;
		while(1)
		{
			int x=S.top();S.pop();
			sccno[x]=scc_cnt;
			if(x==now) break;
		}
	}
}
void find_scc()
{
	memset(pre,0,sizeof(pre));
	memset(sccno,0,sizeof(sccno));
	memset(lowlink,0,sizeof(lowlink));
	scc_cnt=dfs_clock=0;
	for(int i=0;i<n;i++) if(!pre[i]) dfs(i);
}
