/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>
using namespace std;

void computelps(string pattern,int lps[]){
    int m=pattern.length();
    lps[0]=0;
    int len=0;
    int i=1;
    while (i<m){
        if (pattern[len]==pattern[i]){
            len++;
            lps[i]=len;
            i++;
        }
        else{
            if(len!=0){
                len=lps[len-1];
            }
            else{
                lps[i]=0;
                i++;
            }
        }
    }
}
void KMP(string text,string pattern){
    int n=text.length();
    int m=pattern.length();
    int *lps=new int[m];
    int i=0;
    int j=0;
    while(i<n){
        if (text[i]==pattern[j]){
            i++;
            j++;
            
        }
        if (j==m){
            cout<<"Pattern found at :"<<i-j<<endl;
            j=lps[j-1];
            
            
        }
        else if(i<n && text[i]!=pattern[j]){
            if (j!=0){
                j=lps[j-1];
                
            }
            else{
                i++;
            }
        }
    }
    
    
}
int main()
{
    
    string T, P;

    cout << "Enter Text: ";
    getline(cin, T);

    cout << "Enter Pattern: ";
    getline(cin, P);

    KMP(T, P);

    return 0;
}