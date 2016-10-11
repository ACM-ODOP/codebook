struct FFT
{
    complex<DB> epsilon[maxn],buffer[maxn],temp[maxn];
    void fft(int n,int offset,int step)
    {
    	if(n == 1) return;
    	int m=n>>1;
    	
        fft(m,offset,step<<1);
    	fft(m,offset+step,step<<1);
    
    	for(int k=0;k<m;k++)
        {
    		int pos = 2 * step * k;
    		temp[k] = buffer[pos + offset] + epsilon[k * step] * buffer[pos + offset + step];
    		temp[k + m] = buffer[pos + offset] - epsilon[k * step] * buffer[pos + offset + step];
    	}
        for(int i=0;i<n;i++) buffer[i * step + offset] = temp[i];
    }
    inline void init_epsilon(const int& n)
    {
    	for(int i=0;i<n;i++) epsilon[i] = complex<DB>(cos(2.0 * pi * i / n), sin(2.0 * pi * i / n)); 
    }
    inline void dft(DB* coef,const int& n,complex<DB>* pv)
    {
        for(int i=0;i<n;i++) buffer[i]=complex<DB>(coef[i],0);
        fft(n,0,1);
        for(int i=0;i<n;i++) pv[i]=buffer[i];
    }
    inline void idft(complex<DB>* pv,const int& n,DB* coef)
    {
        for(int i=0;i<n;i++) buffer[i]=pv[i];
        fft(n,0,1);
        coef[0]=real(buffer[0])/n;
        for(int i=1;i<n;i++) coef[i]=real(buffer[n-i])/n;
    }
};
