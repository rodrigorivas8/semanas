#include <iostream>
#include <utility>
using namespace std;

class BrowserHistory {
    struct page{
        string url;
        page* next=nullptr;
        page* prev=nullptr;
        explicit page(string s):url(std::move(s)){}
    };
    page* home=nullptr;

public:

    explicit BrowserHistory(string homepage) {
        home=new page(std::move(homepage));
    }
    void visit(string url) {
        auto temp=home->next;
        while(temp){
            auto aux=temp;
            temp=temp->next;
            delete aux;
        }
        home->next=new page(std::move(url));
        home->next->prev=home;
        home=home->next;
    }
    string back(int steps) {
        while(steps-- && home->prev){
            home=home->prev;
        }
        return home->url;
    }
    string forward(int steps) {
        while(steps-- && home->next){
            home=home->next;
        }
        return home->url;
    }
};

const int MAX=int(1e3);
class LRUCache {
    struct node{
        int key=0;
        int val=0;
        node* next=nullptr,
            * prev=nullptr;
        explicit node(int k,int v):key(k),val(v){}
    };
    node* head=nullptr;
    node* list[MAX]={};
    int cap=0;
public:
    LRUCache(int capacity) {
        cap=capacity;
        head=new node(0,0);
        head->next=head;
        head->prev=head;
    }

    int get(int key) {
        auto item=list[key];
        if(!item) return -1;
        remove(item);
        place(item);
        return item->val;
    }

    void put(int key, int value) {
        if(list[key]){
            list[key]->val=value;
            remove(list[key]);
            place(list[key]);
            return;
        }

        if(cap) cap--;
        else{
            auto temp=head->prev;
            list[temp->key]=nullptr;
            remove(temp);
            delete temp;
        }

        auto item=new node(key,value);
        list[key]=item;
        place(item);
    }

    void remove(node* item){
        item->next->prev=item->prev;
        item->prev->next=item->next;
    }

    void place(node* item){
        item->next=head->next;
        item->prev=head;
        head->next->prev=item;
        head->next=item;
    }
};

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

class Solution {
public:
    Node* flatten(Node* head) {
        auto aux=head;
        while(aux){
            auto child=aux->child;
            if(child){
                child=flatten(child);

                auto tail=child;
                while(tail->next)
                    tail=tail->next;

                tail->next=aux->next;
                aux->next->prev=tail;
                aux->next=child;
                child->prev=aux;

                aux->child=nullptr;
                aux=tail;
            }
            aux=aux->next;
        }
        return head;
    }
};

const int CAP=1e3;
class AllOne {
    struct level;
    struct node{
        string key;
        level* lvl=nullptr;
        node* next=nullptr,
            * prev=nullptr;
        explicit node(string k):key(std::move(k)){}
    };

    struct level{
        node* head=nullptr;
        level* prev=nullptr,
             * next=nullptr;

        explicit level(node* h):head(h){}

        void push_front(node* item){
            if(!head){
                head=item;
                return;
            }
            item->next=head;
            head->prev=item;
            head=item;
        }

        void remove(node* item){
            if(head==item)
                head=nullptr;
            if(item->next)
                item->next->prev=item->prev;
            if(item->prev)
                item->prev->next=item->next;
        }
    };

    level* max=nullptr,
         * min=nullptr;
    node* list[CAP]={};
    int cap=CAP;

    static int hash(const string& key){
        int h=0,s=1;
        for(char c:key)
            h+=c*(s++);
        return h%CAP;
    }

    void remove(level* lvl){
        if(max==lvl){
            max=nullptr;
        }
    }

public:
    AllOne()=default;
    void inc(string key){

        int id=hash(key);
        auto item=list[id];

        if(!item){
            item=new node(std::move(key));
            list[id]=item;

            if(!max){
                max=new level(item);
                min=max;
                item->lvl=min;
                return;
            }

            min->push_front(item);
            item->lvl=min;
            return;
        }

        auto next=item->lvl->next;
        item->lvl->remove(item);
        if(next)
            next->push_front(item);
        else{
            next=new level(item);
            item->lvl->next=next;
            max=next;
        }
    }

    void dec(const string& key){
        int id=hash(key);
        auto item=list[id];

        if(!item) return;
        auto prev=item->lvl->prev;
        item->lvl->remove(item);

        if(!max->head){
            auto temp=max;
            max=max->prev;
            if(max) max->next=nullptr;
            else min=nullptr;
            delete temp;
        }else if(!min->head){
            min=min->next;
        }

        if(!prev) delete item;
        else prev->push_front(item);
    }

    string getMaxKey(){
        return max->head->key;
    }

    string getMinKey(){
        return min->head->key;
    }
};

/*

int main(){
    /*
    auto browserHistory = new BrowserHistory("leetcode.com");
    browserHistory->visit("google.com");
    browserHistory->visit("facebook.com");
    browserHistory->visit("youtube.com");
    cout<<browserHistory->back(1)<<endl;
    cout<<browserHistory->back(1)<<endl;
    cout<<browserHistory->forward(1)<<endl;
    browserHistory->visit("linkedin.com");
    cout<<browserHistory->forward(2)<<endl;
    cout<<browserHistory->back(2)<<endl;
    cout<<browserHistory->back(7)<<endl;
    */

/*
Solution sol;
auto n1=new Node; n1->val=1;
auto n2=new Node; n2->val=2;
auto n3=new Node; n3->val=3;
auto n4=new Node; n4->val=4;
auto n5=new Node; n5->val=5;
auto n6=new Node; n6->val=6;
n1->next=n2; n2->next=n3; n3->next=n4; n4->next=n5; n5->next=n6;
n6->prev=n5; n5->prev=n4; n4->prev=n3; n3->prev=n2; n2->prev=n1;


auto n7=new Node; n7->val=7;
auto n8=new Node; n8->val=8;
auto n9=new Node; n9->val=9;
auto n10=new Node; n10->val=10;
n7->next=n8; n8->next=n9; n9->next=n10;
n10->prev=n9; n9->prev=n8; n8->prev=n7;

auto n11=new Node; n11->val=11;
auto n12=new Node; n12->val=12;
n11->next=n12;
n12->prev=n11;

n3->child=n7;
n8->child=n11;

auto n0=sol.flatten(n1);
while(n0){
    cout<<n0->val<<' ';
    n0=n0->next;
}
cout<<endl<<endl;
*/

/*
auto lRUCache = new LRUCache(2);
lRUCache->put(1,1);
lRUCache->put(2,2);
cout<<lRUCache->get(1)<<endl;
lRUCache->put(3,3);
cout<<lRUCache->get(2)<<endl;
lRUCache->put(4,4);
cout<<lRUCache->get(1)<<endl;
cout<<lRUCache->get(3)<<endl;
cout<<lRUCache->get(4)<<endl;
cout<<endl<<endl;
*/

/*
auto allOne=new AllOne();
allOne->inc("hello");
allOne->inc("hello");
cout<<allOne->getMaxKey()<<endl;
allOne->inc("leet");
cout<<allOne->getMaxKey()<<endl;
allOne->dec("hello");
cout<<allOne->getMaxKey()<<endl;
}
*/
