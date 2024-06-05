#include <vector>
#include <string>
using namespace std;

struct disjoint_set{
    int len;
    int* par;
    int* rank;
    int sets=0;
public:
    disjoint_set(){
        len=1e5;
        par=new int[len]();
        rank=new int[len]();
    }

    explicit disjoint_set(int n):len(n){
        par=new int[n]();
        rank=new int[n]();
    };

    void make(int n){
        if(par[n]) return;
        par[n]=n;
        rank[n]=0;
        sets++;
    }

    int find(int n){
        if(par[n]!=n)
            par[n]=find(par[n]);
        return par[n];
    }

    void join(int n,int m){
        n=find(n);
        m=find(m);
        if(rank[n]==rank[m])
            rank[n]++;
        if(rank[n]>rank[m])
            par[m]=n;
        else par[n]=m;
        if(n!=m) sets--;
    }
    int count(){return sets;}
};

struct Solution{
    int numIslands(vector<vector<char>>& grid){
        int n=(int) grid.size(),
            m=(int) grid[0].size();
        auto dis=new disjoint_set(n*m);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]=='0') continue;
                int k=i*m+j;
                dis->make(k);
                if(i>0 && grid[i-1][j]-'0')
                    dis->join(k,k-m);
                if(j>0 && grid[i][j-1]-'0')
                    dis->join(k,k-1);
            }
        }
        return dis->count();
    }
};

class trie{
    struct node{
        bool end=false;
        node* next[26]={};

        node()=default;

        void dot(){end=true;}
        bool cut(){
            bool aux=end;
            end=false;
            return aux;
        }
        auto& operator[](char c){
            return next[c-'a'];
        }
    };
    node* head=nullptr;

    void insert(string s,node* aux){
        if(!s[0]) return aux->dot();
        auto&nxt=(*aux)[s[0]];
        if(!nxt) nxt=new node;
        insert(s.substr(1),nxt);
    }

    bool remove(string s,node* aux){
        if(!aux) return false;
        if(!s[0]) return aux->cut();
        auto nxt=(*aux)[s[0]];
        auto rst=s.substr(1);
        if(!remove(rst,nxt))
            return false;
        for(auto x:aux->next)
            if(x) return false;
        delete nxt;
        (*aux)[s[0]]=nullptr;
        return true;
    }

    bool find(string s,node* aux){
        if(!s[0]) return aux->end;
        auto nxt=(*aux)[s[0]];
        if(!nxt) return false;
        return find(s.substr(1),nxt);
    }

public:
    trie():head(new node){}

    void insert(string word){
        insert(word,head);
    }

    bool find(string word){
        return find(word,head);
    }

    void remove(string word){
        remove(word,head);
    }
};

struct streamChecker{
    trie* dic=nullptr;
    string que;

    string reverse(string& word){
        int n=word.length();
        for(int i=0;i<n/2;i++){
            char aux=word[i];
            word[i]=word[n-i-1];
            word[n-i-1]=aux;
        }
        return word;
    }

    streamChecker(vector<string>& arr){
        dic=new trie();
        for(auto i:arr)
            dic->insert(reverse(i));
    }

    bool query(char c){
        que=c+que;
        int n=que.length();
        while(n--)
            if(dic->find(que.substr(0,n)))
                return true;
        return false;
    }
};