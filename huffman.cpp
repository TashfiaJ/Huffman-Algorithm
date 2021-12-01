#include<bits/stdc++.h>
using namespace std;
#define ll long long

char str[1000];
map<char,ll>frequency;
set<char>character;
map<char,string>encode;

struct node{
          char ch;
          ll freq;
          struct node *left,*right;
};

struct node *pq[1000];

struct node* new_node(ll f, char a, struct node *left_child,struct node *right_child)
{
          struct node *temp=(struct node*)malloc(sizeof(struct node));
          temp->ch=a;
          temp->freq=f;
          temp->left=left_child;
          temp->right=right_child;
          return temp;
}

void encoding(string s, struct node *t)
{
          if(t->left==NULL&&t->right==NULL)
          {
                    encode[t->ch]=s;
                    cout<<t->ch<<":"<<s<<endl;
                    return;
          }
          encoding(t->left,s+"0");
          encoding(t->right,s+"1");
}

void decoding(string prefix,struct node *root)
{
          ll i;
          struct node *n=(struct node*)malloc(sizeof(struct node));
          n=root;
          for(i=0;prefix[i]!='\0';i++)
          {
                    if(prefix[i]=='1'&&n->right!=NULL)n=n->right;
                    else if(prefix[i]=='0'&&n->left!=NULL)n=n->left;
                    if(n->ch!='\0'){
                              cout<<n->ch;
                              n=root;
                    }
          }
}

void minHeapify(ll root, ll n)
{
          ll l=root*2+1,r=root*2+2,minimum=root;
          if(l<n&&pq[minimum]->freq>pq[l]->freq)minimum=l;
          if(r<n&&pq[minimum]->freq>pq[r]->freq)minimum=r;
          if(pq[minimum]->freq!=pq[root]->freq)
          {
                    swap(pq[minimum],pq[root]);
                    min_heapify(n,minimum);
          }
}

void insertHeap(ll d)
{
          while(d)
          {
                    ll p=(d-1)/2;
                    if(pq[p]->freq>pq[d]->freq){
                              swap(pq[p],pq[d]);
                              d=p;
                    }
                    else return;
          }
}

void huffman()
{
          set<char>::iterator itt;
          ll i=0,n=character.size();
          for(itt=character.begin();itt!=character.end();itt++)
          {
                    pq[i]=new_node(*itt,frequency[*itt],NULL,NULL);
                    i++;
          }
          for(ll k=i/2-1;k>=0;k--)
                    minHeapify(i,k);
          while(n>1)
          {
                    struct node *left_child=(struct node*)malloc(sizeof(struct node)),*right_child=(struct node*)malloc(sizeof(struct node));
                    left_child=pq[0];
                    swap(pq[0],pq[n-1]);n--;
                    minHeapify(n,0);
                    right_child=pq[0];
                    swap(pq[0],pq[n-1]);
                    minHeapify(n-1,0);
                    pq[n-1]=new_node('\0',left_child->freq+right_child->freq,left_child,right_child);
                    insertHeap(n-1);
          }
          struct node *root=NULL;
          root=pq[0];
          encoding(root,"");
          string pre_code;//prefix code
          cout<<"Encoded message is:"<<endl;
          for(i=0;str[i]!='\0';i++)
          {
                    cout<<encode[str[i]];
                    pre_code=pre_code+encode[str[i]];
          }
          cout<<endl;
          cout<<"length of the prefix code:"<<pre_code.size()<<endl;
          cout<<"Decoded message is:"<<endl;
          decoding(pre_code,root);
}
int main()
{
          FILE *f;
          f=fopen("Message.txt","r");
          char c;
          ll k=0;
          while((c=fgetc(f))!=EOF)
          {
                    str[k]=c;
                    frequency[c]++;
                    character.insert(c);
                    k++;
          }
          huffman();
          cout<<"\nActual message is:\n"<<str<<endl;
}
