/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>
using namespace std;

struct Node{
    Node* child[26];
    bool isEnd;
    Node(){
        for (int i=0;i<26;i++){
           child[i]=nullptr;
           
        }
        isEnd=false;
    }
};
class SuffixTrie{
    Node* root;
    void insert(string s){
        Node *curr =root;
        for (char ch: s){
            int index=ch-'a';
            if(curr->child[index]==nullptr)
                curr->child[index]=new Node();
            curr=curr->child[index];    
        }
        curr->isEnd=true;
    }

    
    public:
    
    SuffixTrie(string s){
        root=new Node();
        for (int i=0;i<s.length();i++){
            insert(s.substr(i));
        }
    }
    bool search(string word){
        Node *curr =root;
        for (char ch: word){
            int index=ch-'a';
            if (curr->child[index]==nullptr)
                return false;
           curr=curr->child[index];
        }
        return true;
    }
        
};

int main()
{
    string s;
    cout<<"Entet string: ";
    cin>>s;
    SuffixTrie st(s);
    string pattern;
    cout<<"enter pattern : ";
    cin>>pattern;
    if (st.search(pattern))
        cout<<"found"<<endl;
    else
        cout<<"not found "<<endl;
    
    return 0;
}