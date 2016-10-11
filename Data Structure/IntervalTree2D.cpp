struct SegmentTree2D
{
	int Max[maxn][maxn],Min[maxn][maxn],n,m;
	int xo,xleaf,x1,x2,y1,y2,x,y,v,vmax,vmin;
	void query1D(int o,int l,int r)
	{
		if(y1<=l && r<=y2) {vmax=max(Max[xo][o],vmax);vmin=min(Min[xo][o],vmin);return;}
		int mid=l+(r-l)/2;
		if(y1<=mid) query1D(o*2,l,mid);
		if(mid<y2) query1D(o*2+1,mid+1,r);
	}
	void query2D(int o,int l,int r)
	{
		if(x1<=l && r<=x2) {xo=o;query1D(1,1,m);return;}
		int mid=l+(r-l)/2;
		if(x1<=mid) query2D(o*2,l,mid);
		if(mid<x2) query2D(o*2+1,mid+1,r);
	}
	void modify1D(int o,int l,int r)
	{
		if(l==r)
		{
			if(xleaf) {Max[xo][o]=Min[xo][o]=v;return;}
			Max[xo][o]=max(Max[xo*2][o],Max[xo*2+1][o]);
			Min[xo][o]=min(Min[xo*2][o],Min[xo*2+1][o]);
			return;
		}
		int mid=l+(r-l)/2;
		if(y<=mid) modify1D(o*2,l,mid);
		else modify1D(o*2+1,mid+1,r);

		Max[xo][o]=max(Max[xo][o*2],Max[xo][o*2+1]);
		Min[xo][o]=min(Min[xo][o*2],Min[xo][o*2+1]);
	}
	void modify2D(int o,int l,int r)
	{
		if(l==r) {xo=o;xleaf=1;modify1D(1,1,m);return;}
		int mid=l+(r-l)/2;
		if(x<=mid) modify2D(o*2,l,mid);
		else modify2D(o*2+1,mid+1,r);
		xo=o;xleaf=0;modify1D(1,1,m);
	}
	void modify() {modfiy2D(1,1,n);}
	void query() {vmin=INF;vmax=-INF;query2D(1,1,n);}
};
