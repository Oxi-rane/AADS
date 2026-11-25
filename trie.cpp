/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
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
class Trie{
    Node* root;
    public:
    Trie(){
        root=new Node();
    }
    void insert(string word){
        Node *curr =root;
        for (char ch: word){
            int index=ch-'a';
            if(curr->child[index]==nullptr)
                curr->child[index]=new Node();
            curr=curr->child[index];    
        }
        curr->isEnd=true;
    }
    bool search(string word){
        Node *curr =root;
        for (char ch: word){
            int index=ch-'a';
            if (curr->child[index]==nullptr)
                return false;
           curr=curr->child[index];
        }
        return curr->isEnd;
    }
        
};

int main()
{
    Trie t;
    t.insert("apple");
    t.insert("app");
    t.insert("bat");
    t.insert("batsman");
    cout<<t.search("apple")<<endl;
    cout<<t.search("bats")<<endl;
    cout<<t.search("bat")<<endl;
    return 0;
}