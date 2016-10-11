struct Node
{
	Node* ch[2];
	int v;
	int s;
	int cmp(int k)
	{
		int d=k-ch[0]->s;
		if(d==1) return -1;
		return d<=0? 0:1;
	}
	void maintain()
	{
		s=1;
		if(ch[0]!=NULL) s+=ch[0]->s;
		if(ch[1]!=NULL) s+=ch[1]->s;
	}
};
void rotate(Node* &o,int d)
{
	Node* k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o;
	o->maintain(); k->maintain(); o = k;
}
void splay(Node* &o,int k)
{
	int d=o->cmp(k);
	if(d==1) k-=o->ch[0]->s+1;
	if(d!=-1)
	{
		Node* p=o->ch[d];
		int d2=p->cmp(k);
		int k2=(d2==0?k:k-p->ch[0]->s-1);
		if(d2!=-1)
		{
			splay(p->ch[d2],k2);
			if(d==d2) rotate(o,d^1);else rotate(o->ch[d],d);
		}
		rotate(o,d^1);
	}
}

Node* merge(Node* left,Node* right)
{
	splay(left,left->s);
	left->ch[1]=right;
	left->maintain();
	return left;
}

void split(Node* o,int k,Node* &left,Node* &right)
{
	splay(o,k);
	left=o;
	right=o->ch[1];
	o->ch[1]=NULL;
	left->maintain();
}
