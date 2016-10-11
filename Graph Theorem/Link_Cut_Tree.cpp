const int maxnode=3000000+5;
struct Node
{
    Node *ch[2],*fa;
    int val,Max,add;
    bool rev;
    Node() {}
    inline void clear();
    inline void push();
    inline void pull();
}mem[maxnode],*EMPTY=mem;
inline void Node::clear() {val=Max=add=rev=0;ch[0]=ch[1]=fa=EMPTY;}
inline void Node::push()
{
    val+=add;
    ch[0]->add+=add;ch[1]->add+=add;
    add=0;
    if(rev)
    {
        ch[1]->rev^=1;ch[0]->rev^=1;
        swap(ch[0],ch[1]);
        rev=0;
    }
}
inline void Node::pull()
{
    Max=max(val,max(ch[0]==EMPTY?0:(ch[0]->Max+ch[0]->add), ch[1]==EMPTY?0:(ch[1]->Max+ch[1]->add)));
}
inline bool isroot(Node* now) {return now->fa->ch[0]!=now && now->fa->ch[1]!=now;}
inline void rotate(Node* now,int d)
{
    Node* fa=now->fa,*gfa=fa->fa;
    fa->ch[d^1]=now->ch[d];
    if(now->ch[d]!=EMPTY) now->ch[d]->fa=fa;
    fa->fa=now;
    now->ch[d]=fa;
    
    now->fa=gfa;
    if(gfa->ch[0]==fa) gfa->ch[0]=now;
    else if(gfa->ch[1]==fa) gfa->ch[1]=now;
    fa->pull();now->pull();gfa->pull();
}
inline void splay(Node* now)
{
    now->push();
    for(Node *fa,*gfa;!isroot(now) && (fa=now->fa)!=EMPTY;)
        if(!isroot(fa) && (gfa = fa->fa)!=EMPTY)
        {
            gfa->push();fa->push();now->push();
            int d = (gfa->ch[0]==fa);
            if(fa->ch[d^1]==now) rotate(fa,d),rotate(now,d); // collinear
            else rotate(now,d^1),rotate(now,d);
        }
        else
        {
            fa->push();now->push();
            rotate(now,fa->ch[0]==now);
            break;
        }
    now->pull();
}
inline Node* access(Node* now)
{
    Node* last=EMPTY;
    for(;now!=EMPTY;now=now->fa)
    {
        splay(now);
        now->ch[1]=last;
        last->fa=now;
        (last=now)->pull();
    }
    return last;
}
inline Node* find_root(Node* now)
{
    for(now=access(now);now->push(),now->ch[0]!=EMPTY;now=now->ch[0]);
    return now;
}
inline void make_root(Node* now)
{
    access(now)->rev^=1;
    splay(now);
}
inline void link(Node* x,Node* y)
{
    make_root(y);
    y->fa=x;
    access(y);
}
inline void cut(Node* x,Node* y)
{
    make_root(x);
    access(y);splay(y);
    y->ch[0]->fa=EMPTY;
    y->ch[0]=EMPTY;
    y->pull();
}
inline void modify(Node* x,Node* y,int w)
{
    make_root(x);
    access(y);splay(y);
    y->add+=w;
}
inline int query(Node* x,Node* y)
{
    make_root(x);
    access(y);splay(y);
    return y->Max+y->add;
}
