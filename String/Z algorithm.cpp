char s[maxs];
int Z[maxs];
void build_Z()
{
	int n=strlen(s);
	Z[0]=0;
	int L,R;
	L=R=0;
	for(int i=1;i<n;i++)
	{
		if(i>R) Z[i]=0;
		else
		{
			int ip=i-L;
			if(ip+Z[ip]<Z[L]) Z[i]=Z[ip];
			else Z[i]=R-i+1;
		}
		while(i+Z[i]<n && s[i+Z[i]]==s[Z[i]]) Z[i]++;

		if(i+Z[i]-1>R)
		{
			L=i;
			R=i+Z[i]-1;
		}
	}
}
