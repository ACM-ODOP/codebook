/// to make sure every dfs gets one SCC
/// we want to traversal by the topological order of SCC
vector<int> G[maxn],G2[maxn];/// G2 is G1's transpose
vector<int> S;
int vis[maxn],sccno[maxn],scc_cnt;

void dfs1(int u)
{
	if(vis[u]) return;
	vis[u]=1;
	for(int i=0;i<G[u].size();i++) dfs(G[u][i]);
	S.push_back(u);
}

void dfs2(int u)
{
	if(sccno[u]) return;
	sccno[u] = scc_cnt;
	for(int i=0;i<G2[u].size();i++) dfs2(G2[u][i]);
}

void find_scc(int n)
{
	scc_cnt=0;
	S.clear();
	memset(sccno,0,sizeof(sccno));
	memset(vis,0,sizeof(vis));
	for(int i=0;i<n;i++) dfs1(i);
	for(int i=n-1;i>=0;i--)
		if(!sccno[S[i]]) {scc_cnt++;dfs2(S[i]);}
}
