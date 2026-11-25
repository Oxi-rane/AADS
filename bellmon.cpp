/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <climits>
using namespace std;

struct Edge{
    int u,v,w;
};

void bellmon_ford(int n, int e,Edge edges[],int src){
    int *dist=new int[n];
    for (int i=0;i<n;i++){
        dist[i]=INT_MAX;
    }
    dist[src]=0;
    for (int i=0;i<n-1;i++){
        for (int j=0;j<e;j++){
            int u=edges[j].u;
            int v=edges[j].v;
            int w=edges[j].w;
            
            if (dist[u]!=INT_MAX && dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
            }
        }
    }   
    //Check negative cycle
    for (int j=0;j<e;j++){
        int u=edges[j].u;
        int v=edges[j].v;
        int w=edges[j].w;
            
        if (dist[u]!=INT_MAX && dist[u]+w<dist[v]){
                cout<<"Negative Weight Cycle Detected"<<endl;
                return;
            }
    }
    //Print SHortest DistANCE
    cout<<"SHortest Distance from Source  "<<src<<": \n";
    for (int i=0;i<n;i++){
        cout<<src<<" -> "<<i<<" = ";
        if (dist[i]==INT_MAX){
            cout<<"INF"<<endl;
        }
        else
            cout<<dist[i]<<endl;
    }       
}
int main()
{
    int n,e;
    cout<<"ENter vertices and edges: ";
    cin>>n>>e;
    Edge *edges=new Edge[e];
    for (int i=0;i<e;i++){
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
    }
    int src;
    cout<<"Source:";
    cin>>src;
    bellmon_ford(n,e,edges,src);
    return 0;
}