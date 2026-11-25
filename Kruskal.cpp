/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <algorithm>
using namespace std;

struct Edge{
  int u,v,w;  
};

int find(int x, int parent[]){
     if (parent[x]!=x){
         parent[x]=find(parent[x],parent);
     }
     return parent[x];
}
void unite(int X,int Y,int parent[],int rankarr[]){
    int rootX=find(X,parent);
    int rootY=find(Y,parent);
    if (rootX==rootY)
        return;
    if (rankarr[rootX]>rankarr[rootY]){
        parent[rootY]=rootX;
    
    }
    else if(rankarr[rootY]>rankarr[rootX])
        parent[rootX]=rootY;
    else{
        parent[rootY]=rootX;
        rankarr[rootX]++;
    }
}
void Kruskal(Edge edges[],int V,int E){
    int *parent=new int[V];
    int *rankarr=new int[V];
    for (int i=0;i<V;i++){
        parent[i]=i;
        rankarr[i]=0;
    }
    sort(edges,edges+E,[](Edge a, Edge b)
        {
            return a.w<b.w;
        });

    int count=0;
    int totalweight=0;
    for (int i=0;i<E && count<V-1;i++){
        int u=edges[i].u;
        int v=edges[i].v;
        if (find(u,parent)!=find(v,parent)){
            cout<<u<<"-"<<"v"<<": "<<edges[i].w<<endl;
            unite(u,v,parent,rankarr);
            totalweight+=edges[i].w;
            count++;
            
        }
    }
    if (count!=V-1){
        cout<<"MST does not exist"<<endl;
        
    }
    else{
        cout<<"Total Weight: "<<totalweight<<endl;
    }
}
int main()
{
    int V,E;
    cout<<"Enter number of vertices and Edges: ";
    cin>>V>>E;
    Edge *edges=new Edge[E];
    cout<<"Enter Edges: "<<endl;
    for (int i=0;i<E;i++){
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
        
    }
    Kruskal(edges,V,E);
    
    return 0;
}