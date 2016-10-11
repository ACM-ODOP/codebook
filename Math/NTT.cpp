class NTT
{
    private:
    LL epsilon[maxn],buffer[maxn],temp[maxn];
    static const LL P=(7LL<<50)+1;
    static const LL G=6;
    inline LL add(const LL& a,const LL b)
    {
        if(a+b>P) return a+b-P;
        else if(a+b<0) return a+b+P;
        return a+b;
    }
    inline LL mul(const LL& a,const LL b)
    {
        LL y=(LL)((double)a*b/P+0.5);
        LL r=(a*b-y*P)%P;
        return r<0?r+P:r;
    }
    LL fast_pow(LL x,LL a)
    {
        LL res=1;
        for(;a;a>>=1,x=mul(x,x)) if(a&1) res=mul(res,x);
        return res;
    }
    inline void init(LL n)
    {
        epsilon[0]=1;
        epsilon[1]=fast_pow(G,(P-1)/n);
        for(LL i=2;i<n;i++) epsilon[i]= mul(epsilon[1],epsilon[i-1]);
    }
    void fft(LL n,LL offset,LL step)
    {
        for(LL i=0,j=0;i<n;i++)
        {
            if(i>j) swap(buffer[i],buffer[j]);
            for(LL k=n>>1;(j^=k)<k;k>>=1);
        }
        for(LL i=2,m=1;i<=n;i<<=1,m<<=1)
            for(LL offset=0;offset<n;offset+=i)
                for(LL k=0;k<m;k++)
                {
                    LL rgt= mul(epsilon[n / i * k ] , buffer[offset + m + k ]);
                    buffer[offset + m + k] = add(buffer[offset + k], -rgt);
                    buffer[offset + k] = add(buffer[offset + k] , rgt);
                }
    }
    
    public:
    void dft(const vector<LL>& coef,LL n,vector<LL>& pv)
    {
        for(LL i=0;i<n;i++) buffer[i]= (i<(int)coef.size()?coef[i]:0);
        fft(n,0,1);
        
        pv.resize(n);
        for(LL i=0;i<n;i++) pv[i]=buffer[i];
    }
    void idft(const vector<LL>& pv,LL n,vector<LL>& coef)
    {
        for(LL i=0;i<n;i++) buffer[i]= (i<(int)pv.size()?pv[i]:0);
        fft(n,0,1);

        coef.resize(n);
        LL inv=fast_pow(n,P-2);
        coef[0]=mul(buffer[0],inv);
        for(LL i=1;i<n;i++) coef[i]=mul(buffer[n-i],inv);
    }
    void conv(const vector<LL>& fx,const vector<LL>& gx,vector<LL>& hx)
    {
        LL n;
        for(n=1;n<(int)fx.size()+(int)gx.size();n<<=1);
        

        vector<LL> pv[3];
        init(n);
        dft(fx,n,pv[0]);
        dft(gx,n,pv[1]);
        
        pv[2].resize(n);
        for(LL i=0;i<n;i++) pv[2][i]=mul(pv[0][i],pv[1][i]);
               
        idft(pv[2],n,hx);
    }
}ntt;
