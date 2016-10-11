int getCircleCircleIntersection(Circle C1,Circle C2,vector<Point>& sol)
{
	DB d=Length(C1.c-C2.c);
	if(dcmp(d)==0)
	{
		if(dcmp(C1.r-C2.r)==0) return -1; 
		return 0;
	}
	if(dcmp(C1.r+C2.r-d)<0) return 0;
	if(dcmp(fabs(C1.r-C2.r)-d)>0) return 0;

	DB a=angle(C2.c-C1.c);
	DB da= acos((C1.r*C1.r+d*d-C2.r*C2.r)/(2*C1.r*d));
	Point p1=C1.point(a-da),p2=C1.point(a+da);

	sol.push_back(p1);
	if(p1==p2) return 1;
	sol.push_back(p2);
	return 2;
}

int PointCircleTangents(Point p,Circle C,Vector* v)
{
	Vector u=C.c-p;
	DB dist=Length(u);
	if(dist<C.r) return 0;
	else if(dcmp(dist-C.r)==0)
	{
		v[0]=Rotate(u,PI/2);
		return 1;
	}
	else
	{
		DB ang=asin(C.r/dist);
		v[0]=Rotate(u,-ang);
		v[1]=Rotate(u,ang);
		return 2;
	}
}

int CircleCircleTangents(Circle A,Circle B,Point* a,Point *b)
{
	int cnt=0;
	if(A.r<B.r) {swap(A,B);swap(a,b);}
	int d2=(A.c.x-B.c.x)*(A.c.x-B.c.x) + (A.c.y-B.c.y)*(A.c.y-B.c.y);
	int rdiff=A.r-B.r;
	int rsum=A.r+B.r;
	if(d2<rdiff*rdiff) return 0;

	DB base=atan2(B.c.y-A.c.y,B.c.x-A.c.x);
	if(d2==0 && A.r==B.r) return -1;
	if(d2==rdiff*rdiff)
	{
		a[cnt]=A.point(base);b[cnt]=B.point(base);cnt++;
		return 1;
	}
	
    DB ang = acos((A.r-B.r)/sqrt(d2));
	a[cnt]=A.point(base+ang);b[cnt]=B.point(base+ang);cnt++;
	a[cnt]=A.point(base-ang);b[cnt]=B.point(base-ang);cnt++;
	if(d2==rsum*rsum) 
	{
		a[cnt]=A.point(base);b[cnt]=B.point(PI+base);cnt++;
	}
	else if(d2>rsum*rsum)
	{
		DB ang=acos((A.r+B.r)/sqrt(d2));
		a[cnt]=A.point(base+ang);b[cnt]=B.point(PI+base+ang);cnt++;
		a[cnt]=A.point(base-ang);b[cnt]=B.point(PI+base-ang);cnt++;
	}
	return cnt;
}

///x=rcos(theta)cos(phi)
///y=rcos(theta)sin(phi)
///z=rsin(theta)
DB torad(DB deg)
{
	return deg/180 * acos(-1);
}
void get_coord(DB R,DB lat,DB lng,DB &x,DB &y,DB &z)
{
	lat=torad(lat);
	lng=torad(lng);
	x=R*cos(lat)*cos(lng);
	y=R*cos(lat)*sin(lng);
	z=R*sin(lat);
}

typedef vector<Point> Polygon;
int isPointInPolygon(Point p,Polygon poly)
{
	int wn=0;
	int n=poly.size();
	for(int i=0;i<n;i++)
	{
		if(OnSegment(p,poly[i],poly[(i+1)%n])) return -1;
		int k=dcmp(Cross(poly[i]-p,poly[(i+1)%n]-p));
		int d1=dcmp(poly[i].y-p.y);
		int d2=dcmp(poly[(i+1)%n].y-p.y);
		if(k>0&&d1<=0 && d2>0) wn++;
		if(k<0&&d2<=0 && d1>0) wn--;
	}
	if(wn!=0) return 1;
	return 0;
}
int ConvexHull(Point* p,int n,Point* ch)
{
	sort(p,p+n);
	int m=0;
	for(int i=0;i<n;i++)
	{
		while(m>1 && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
		ch[m++]=p[i];
	}
	int k=m;
	for(int i=n-2;i>=0;i--)
	{
		while(m > k && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
		ch[m++]=p[i];
	}
	if(n>1) m--;
	return m;
}
