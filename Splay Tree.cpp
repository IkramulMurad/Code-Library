#include <bits/stdc++.h>
 
using namespace std;
const long long inf=1e17;
const long long mod=1e9+1;
long long s=0;
struct Node
{
    long long key;
    long long sum;
    Node* left;
    Node* right;
};
void swap(Node* a,Node* b)
{
    Node* temp;
    temp=a;
    a=b;
    b=temp;
}
void dfs_print(Node* root)
{
    if (root != NULL)
    {
        cout<<root->key<<" "<<root->sum<<endl;
        dfs_print(root->left);
        dfs_print(root->right);
    }
}
void dfs_delete(Node* root)
{
    if (root != NULL)
    {
        dfs_delete(root->left);
        dfs_delete(root->right);
        delete root;
    }
}
Node* newNode(long long key)
{
    Node* node=new Node;
    node->key=key;
    //sum added
    node->sum=key;
    node->left=node->right=NULL;
    return node;
}
Node* rightRotate(Node* x)
{
    Node* y=x->left;
    //sum
    x->sum=x->key;
    if(x->right)x->sum+=x->right->sum;
    if(y->right)x->sum+=y->right->sum;
    y->sum=y->key;
    if(y->left)y->sum+=y->left->sum;
    y->sum+=x->sum;
    //placing
    x->left=y->right;
    y->right=x;
    return y;
}
Node* leftRotate(Node* x)
{
    Node* y=x->right;
    //sum
    x->sum=x->key;
    if(x->left)x->sum+=x->left->sum;
    if(y->left)x->sum+=y->left->sum;
    y->sum=y->key;
    if(y->right)y->sum+=y->right->sum;
    y->sum+=x->sum;
    //placing
    x->right=y->left;
    y->left=x;
    return y;
}
Node* splay(Node* root,long long key)
{
    //empty tree or key at the root
    if(root==NULL || root->key==key) return root;
    //key may be in left side
    else if(root->key >key)
    {
        //if no left child
        if(root->left==NULL) return root;
        //if key in the left left(zig zig)
        else if(root->left->key >key)
        {
            //recursively bring key
            root->left->left=splay(root->left->left,key);
            root=rightRotate(root);
        }
        //if key in the left right(zig zag)
        else if(root->left->key <key)
        {
            root->left->right=splay(root->left->right,key);
            if(root->left->right !=NULL)
            {
                root->left = leftRotate(root->left);
            }
        }
 
        //returning
        if(root->left==NULL) return root;
        else return rightRotate(root);
    }
    //key may be in right side
    else if(root->key <key)
    {
        //if right side has no child
        if(root->right==NULL) return root;
        //if key in the right left(zag zig)
        else if(root->right->key >key)
        {
            root->right->left=splay(root->right->left,key);
            if(root->right->left !=NULL)
            {
                root->right =rightRotate(root->right);
            }
        }
        //if key in the right right(zag zag)
        else if(root->right->key <key)
        {
            root->right->right=splay(root->right->right,key);
            root=leftRotate(root);
        }
 
        //returning
        if(root->right==NULL) return root;
        else return leftRotate(root);
    }
    //unnecessary return to avoid warning
    return root;
}
 
Node* searchNode(Node* root, long long key)
{
    return splay(root, key);
}
 
Node* insertNode(Node* root,long long key)
{
    if(root==NULL) return newNode(key);
    root=splay(root,key);
    if(root->key==key) return root;
    Node* node=newNode(key);
    if(root->key >key)
    {
        //sum
        node->sum=node->key+root->sum;
        if(root->left)root->sum-=root->left->sum;
        //placing
        node->right=root;
        node->left=root->left;
        root->left=NULL;
 
 
    }
    else if(root->key <key)
    {
        //sum
        node->sum=node->key+root->sum;
        if(root->right)root->sum-=root->right->sum;
        //placing
        node->left=root;
        node->right=root->right;
        root->right=NULL;
    }
    return node;
}
Node* deleteNode(Node* root, long long key)
{
    if(root==NULL) return root;
    root=splay(root,key);
    if(root->key!=key) return root;
    else if(root->key==key)
    {
        Node* node;
        if(root->left==NULL) node=root->right;
        else
        {
            //goto largest node of the left
            node=splay(root->left,key);
            //sum
            if(root->right)node->sum+=root->right->sum;
            //placing
            node->right=root->right;
        }
        delete root;
        return node;
    }
    //unnecessary return to avoid warning
    return root;
}
Node* split(Node* &root,Node* T1,Node* T2)
{
    if(T2==T1->left||T2==T1->right)
    {
        //sum
        if(T2)T1->sum-=T2->sum;
        //placing
        if(T2==T1->left)
        {
            T1->left=NULL;
        }
        else if(T2==T1->right)
        {
            T1->right=NULL;
        }
    }
    else
    {
        //sum
        if(T1)T2->sum-=T1->sum;
        //placing
        if(T1==T2->left)
        {
            T2->left=NULL;
        }
        else if(T1==T2->right)
        {
            T2->right=NULL;
        }
    }
    root=T1;
    return T2;
}
//join function works only when all node of T1 smaller than T2
Node* join(Node* T1,Node* T2)
{
    if(T1)
    {
        T1=searchNode(T1,inf);
    }
    else
    {
        delete T1;
        return T2;
    }
    if(T2)
    {
        T2=searchNode(T2,0);
    }
    else
    {
        delete T2;
        return T1;
    }
    if(T1)
    {
        if(T2)
        {
            //sum
            T1->sum+=T2->sum;
            //placing
            T1->right=T2;
        }
    }
    return T1;
}
long long sum(Node* &root,long long l,long long r)
{
    long long s=0;
    Node* T1=NULL;
    Node* T2=NULL;
    root=splay(root,l);
    //dfs_print(root);
    //cout<<endl;
    if(root)
    {
        if(root->key<l)
        {
            if(root->right)
            {
                T1=split(root,root->right,root);
            }
            else
            {
                T1=root;
                root=NULL;
            }
        }
        else if(root->key==l)
        {
            if(root->left)
            {
                T1=split(root,root,root->left);
            }
        }
        else if(root->key>l)
        {
            //sum
            if(root->left)root->sum-=root->left->sum;
            //placing
            T1=root->left;
            root->left=NULL;
        }
    }
    //dfs_print(root);
    //cout<<endl;
    root=splay(root,r);
    //dfs_print(root);
    //cout<<endl;
    if(root)
    {
        if(root->key>r)
        {
            if(root->left)
            {
                T2=split(root,root->left,root);
            }
            else
            {
                T2=root;
                root=NULL;
            }
        }
        else if(root->key==r)
        {
            if(root->right)
            {
                T2=split(root,root,root->right);
            }
        }
        else if(root->key<r)
        {
            //sum
            if(root->right)root->sum-=root->right->sum;
            //placing
            T2=root->right;
            root->right=NULL;
        }
    }
    //dfs_print(root);
    //cout<<endl;
    if(root)s=root->sum;
    root=join(T1,root);
    root=join(root,T2);
    //cout<<"after join:"<<endl;
    //dfs_print(root);
    //cout<<endl;
    return s;
}
 
int main()
{
    //freopen("test.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    long long n;
    char c;
    while(cin>>n)
    {
        Node* root=NULL;
        s=0;
        for(long long i=0; i<n; i++)
        {
            //cout<<i+2<<endl;
            cin>>c;
            if(c=='?')
            {
                long long x;
                cin>>x;
                x=(x+s)%mod;
                root=searchNode(root,x);
                if(root==NULL||root->key!=x)
                {
                    cout<<"Not found"<<endl;
                }
                else cout<<"Found"<<endl;
            }
            else if(c=='+')
            {
                long long x;
                cin>>x;
                x=(x+s)%mod;
                root=insertNode(root,x);
            }
            else if(c=='-')
            {
                long long x;
                cin>>x;
                x=(x+s)%mod;
                root=deleteNode(root,x);
            }
            else if(c=='s')
            {
                long long l,r;
                cin>>l>>r;
                l=(l+s)%mod;
                r=(r+s)%mod;
                //root=splay(root,0);
                if(r<l)swap(l,r);
                s=sum(root,l,r);
                cout<<s<<endl;
            }
            //dfs_print(root);
            //cout<<endl;
        }
        //root=searchNode(root,1);
        //dfs_print(root);
        dfs_delete(root);
    }
    return 0;
}
