unsigned ran()
{
	static unsigned x=20150214;
	return x=x*0xdefaced+1;
}
struct Node
{
	static Node mem[N], *pmem;
	Node *l,*r;
	int pri,val,size,Max;
	Node() {}
	Node(int _val):l(NULL),r(NULL),pri(ran()),val(_val),size(1) {}
} Node::mem[N], *Node::pmem=Node::mem ;

int size(Node *t) {return t?t->size:0;}
int Max(Node *t){return t?t->Max:-INF;}
void pull(Node *t)
{
	t->size=size(t->l)+size(t->r)+1;
}
Node* merge(Node *a,Node *b)
{
	if(!a || !b) return a?a:b;
	else if(a->pri > b->pri)
	{
		a->r=merge(a->r,b);
		pull(a);
		return a;
	}
	else
	{
		b->l=merge(a,b->l);
		pull(b);
		return b;
	}
}

void split(Node *t,int k,Node* &a,Node* &b)
{
	if(!t) a=b=NULL;
	else if(t->val<=k)
	{
		a=t;
		split(t->r,k,a->r,b);
		pull(a);
	}
	else
	{
		b=t;
		split(t->l,k,a,b->l);
		pull(b);
	}
}

Node* insert(Node *t,int k)
{
	Node *a,*b;
	split(t,k,a,b);
	return merge(merge(a,new Node(k)),b);
}
Node* remove(Node *t,int k)
{
	Node *a,*b,*c;
	split(t,k-1,a,b);
	split(b,k,b,c);
	return merge(a,c);
}
int kth(Node *t,int k)
{
	if(k<=size(t->l)) return kth(t->l,k);
	else if(k==size(t->l)+1) return t->val;
	else return kth(t->r,k-size(t->l)-1);
}
