namespace DominatorTree
{
    int dfn[maxn], fa[maxn], id[maxn], dfs_clock;
    int semi[maxn], dsu[maxn], idom[maxn], best[maxn];
    int findset(int x)
    {
        if(x==dsu[x]) return x;
        int y=findset(dsu[x]);
        if(semi[best[x]] > semi[best[dsu[x]]]) best[x]=best[dsu[x]];
        return dsu[x]=y;
    }
    void dfs(int now, const vi* G)
    {
        id[dfs_clock]=now;
        dfn[now]=dfs_clock++;
        for (const auto &to:G[now]) if (dfn[to]==-1)
        {
            dfs(to,G);
            fa[dfn[to]] = dfn[now];
        }
    }
    void tarjan(const vi* pre,vi* dom)
    {
        for(int i=dfs_clock-1;i;i--)
        {
            int now=id[i];
            for(auto j:pre[now]) if(dfn[j]!=-1)
            {
                j=dfn[j];
                findset(j);
                getmin(semi[i],semi[best[j]]);
            }
            dom[semi[i]].PB(i);
            
            int x = dsu[i] = fa[i];
            for(const auto& z: dom[x])
            {
                findset(z);
                if(semi[best[z]] < x) idom[z] = best[z];
                else idom[z] = x;
            }
            dom[x].clear();
        }
        for(int i=1;i<dfs_clock;i++)
        {
            if(semi[i]!=idom[i]) idom[i]=idom[idom[i]];
            dom[idom[i]].PB(i);
        }
    }
    void build(int n, int s, const vi* const suc, const vi* const pre, vi* dom)
    {
        for(int i=0;i<n;i++)
        {
            dfn[i]=-1;
            dom[i].clear();
            dsu[i]=best[i]=semi[i]=i;
        }
        dfs_clock = 0;
        dfs(s, suc);
        tarjan(pre, dom);
    }
}
