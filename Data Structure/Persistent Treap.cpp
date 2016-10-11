struct Node
{
	Node* ch[2];
	int v,s;
	Node(int v):v(v),s(1) {ch[0]=ch[1]=NULL;}
	Node(Node* a) {*this=*a;}
	#define size(x) ((x)?((x)->s):0)
	void maintain() {s=size(ch[0])+size(ch[1])+1;}
}*root[maxn];
inline bool randchoice(DB probability) {return (DB)rand() / RAND_MAX <= probability;}
Node* merge(Node *left,Node *right)
{
	if(!left) return left;
	if(!right) return right;
	Node* res;
	if(randchoice((DB)size(left)/(size(left)+size(right))))
	{
		res=new Node(left->v);
		res->ch[0]=left->ch[0];
		res->ch[1]=merge(left->ch[1],right);
	}
	else
	{
		res=new Node(right->v);
		res->ch[0]=merge(left,right->ch[0]);
		res->ch[1]=right->ch[1];
	}
	res->maintain();
	return res;
}

void split(Node* o,int k,Node* &left,Node* &right)
{
	if(!k) {left=right=NULL;return;}
	Node *p=new Node(k);
	if(size(o->ch[0])<k)
	{
		split(o->ch[1],k-size(o->ch[0])-1,left,right);
		p->ch[1]=left;
		p->maintain();
		left=p;
	}
	else
	{
		split(o->ch[0],k,left,right);
		p->ch[0]=right;
		p->maintain();
		right=p;
	}
}
