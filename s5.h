#include <iostream>
#include <vector>
using namespace std;

const int cap=30;
class Solution {
public:

    struct table{
        int list[cap]={};
        int& operator[](char ch){
            int id=ch%cap;
            return list[id];
        }
    };

    struct decoder{
        char list[cap]={};
        char& operator[](char ch){
            int id=ch%cap;
            return list[id];
        }
    };

    int instances(string data){
        string word="balloon";
        table ref,aux;

        for(char ch:word) ref[ch]++;
        for(char ch:data) aux[ch]++;

        int freq=int(data.size());
        for(char ch:word){
            int f0=aux[ch]/ref[ch];
            if(f0<freq) freq=f0;
        }
        return freq;
    }

    static string decode(const string& s){
        string pass="the quick brown fox jumps over the lazy dog";
        decoder d0;
        char aux='a';
        for(char ch:pass){
            if(ch==' ' || d0[ch]) continue;
            d0[ch]=aux++;
        }

        d0[' ']=' ';
        string ans;
        for(char ch:s)
            ans+=d0[ch];
        return ans;
    }

    bool areOccurrencesEqual(string s) {
        table t0;
        for(char c:s) t0[c]++;
        int q=t0[s[0]];
        for(char c:s)
            if(t0[c]!=q)
                return false;
        return true;
    }

    int numOfPairs(vector<string>& nums, string target) {
        int s=target.size(),t=0;
        for(int i=0;i<s;i++)
            for(int j=0;j<s;j++){
                if(i==j) continue;
                if(nums[i]+nums[j]==target)
                    t++;
            }
        return t;
    }

    string minimizeStringValue(string s) {
        table count;
        for(char ch:s)
            count[ch]++;

        string rep;
        int num=count['?'];
        while(num--){
            char min='a';
            for(char ch='z';ch>='a';ch--)
                if(count[ch]<=count[min]) min=ch;
            rep+=min; count[min]++;
        }

        string ans;
        for(char ch:s){
            if(ch=='?'){
                ans+=rep[0];
                rep.erase(0,1);
            }else
                ans+=ch;
        }

        return ans;
    }
};