struct DLX
{
    int ansd,ans[maxr],n,sz,S[maxc];
    int row[maxnode],col[maxnode];
    int L[maxnode],R[maxnode],U[maxnode],D[maxnode];
    void init(int n,int m)
    {
        this->n=n;

        for(int i=1;i<=m;i++) column[i].clear();
        for(int i=0;i<=n;i++) U[i]=i,D[i]=i,L[i]=i-1,R[i]=i+1;
        L[0]=n,R[n]=0;
        sz=n+1;
        for(int i=0;i<=n;i++) S[i]=0;
    }
    void addRow(int r,vector<int>& column)
    {
        int first=sz;
        for(int i=0;i<column.size();i++)
        {
            int c=column[i];
            L[sz]=sz-1,R[sz]=sz+1;
            D[sz]=c,U[sz]=U[c];
            D[U[c]]=sz,U[c]=sz;
            row[sz]=r,col[sz]=c;
            S[c]++;sz++;
        }
        L[first]=sz-1,R[sz-1]=first;
    }
    #define FOR(i,A,st) for(int i=A[st];i!=st;i=A[i])
    void remove(int c)
    {
        L[R[c]]=L[c];
        R[L[c]]=R[c];
        FOR(i,D,c) FOR(j,R,i) {U[D[j]]=U[j];D[U[j]]=D[j];--S[col[j]];}
    }
    void restore(int c)
    {
        FOR(i,U,c) FOR(j,L,i) {U[D[j]]=j;D[U[j]]=j;++S[col[j]];}
        L[R[c]]=c;
        R[L[c]]=c;
    }
    bool dfs(int d)
    {
        if(R[0]==0)
        {
            ansd=d;
            return 1;
        }
        int c=R[0];
        FOR(i,R,0) if(S[i]<S[c]) c=i;
        
        remove(c);
        FOR(i,D,c)
        {
            ans[d]=row[i];
            FOR(j,R,i) remove(col[j]);
            if(dfs(d+1)) return 1;
            FOR(j,L,i) restore(col[j]);
        }
        restore(c);
	return 0;
    }
    bool solve()
    {
	if(!dfs(0)) return 0;
	return 1;
    }
}solver;
