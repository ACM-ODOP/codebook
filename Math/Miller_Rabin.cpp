typedef long long LL;
inline LL mul(LL a,LL b,const LL& n)
{
    LL res=0;a%=n,b%=n;
    for(;b;b>>=1)
    {
        if(b&1) res = (res+a>=n?res+a-n:res+a);
        a = (a+a>=n? a+a-n : a+a );
    }
    return res;
}
inline LL fast_pow(LL a,LL x,const LL& n)
{
    LL res=1;
    for(;x;x>>=1,a=mul(a,a,n)) if(x&1) res=mul(res,a,n);
    return res;
}
inline bool miller_rabin(const LL& n,const LL& a)
{
    if(__gcd(a,n)==n) return 1;
    if(__gcd(a,n)!=1) return 0;
    LL u=n-1,t=0;
    while(!(u&1)) u>>=1,t++;
    
    LL x=fast_pow(a,u,n);
    if(x==1 || x==n-1) return 1;
    for(int i=0;i<t;i++)
    {
        x=mul(x,x,n);
        if(x==1) return 0;
        if(x==n-1) return 1;
    }
    return 0;
}
inline bool isprime(const LL& n)
{
    const static vector<LL> as={2,325,9375,28178,450775,9780504,1795265022};
    for(const LL& a:as) if(!miller_rabin(n,a)) return 0;
    return 1;
}
