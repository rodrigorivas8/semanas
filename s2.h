#include <iostream>
using namespace std;

template <class type>
struct node{
    type val;
    node* next=nullptr;
    node()=default;
    explicit node(type v):val(v){}
    node(type v,node* n):val(v),next(n){}

    friend ostream& operator<<(ostream &os,node* head){
        auto aux=head;
        os<<'[';
        while(aux){
            os<<aux->val;
            aux=aux->next;
            if(aux) os<<',';
        }
        return os<<']';
    }
};

struct solution{
    int bin(node<int>* node){
        double s=0,n=1;
        while(node){
            n=n/2;
            s+=node->val*n;
            node=node->next;
        }
        return int(s/n);
    }

    node<int>* middle(node<int>* head){
        auto one=head,two=head;
        bool clk=true;
        while(one){
            clk=!clk;
            one=one->next;
            if(clk) two=two->next;
        }
        return two;
    }

    node<int>* reverse(node<int>* head){
        auto aux=head;
        head=nullptr;
        while(aux){
            auto t=aux;
            aux=aux->next;
            t->next=head;
            head=t;
        }
        return head;
    }

    node<int>* merge(node<int>* h1,node<int>* h2){
        auto head=new node<int>,aux=head;
        int v;
        while(h1 || h2){
            if(h1 && (h2 && (h1->val < h2->val) || !h2)){
                v=h1->val;
                h1=h1->next;
            } else{
                v=h2->val;
                h2=h2->next;
            }
            aux->next=new node<int>(v);
            aux=aux->next;
        }
        auto temp=head;
        head=head->next;
        delete temp;
        return head;
    }

    bool loop(node<int>* head){
        auto one=head,two=head;
        bool clk=true;
        while(one){
            one=one->next;
            clk=!clk;
            if(clk) two=two->next;
            if(one==two) return true;
        }
        return false;
    }

    node<int>* remove(node<int>* head,int val){
        if(!head) return nullptr;
        if(head->val==val){
            auto temp=head;
            head=head->next;
            delete temp;
            return remove(head,val);
        }
        head->next=remove(head->next,val);
        return head;
    }

    node<int>* expand(node<int>* head){
        auto aux=head;
        while(aux->next){
            auto t1=aux;
            aux=aux->next;
            auto t2=aux;

            int v1=t1->val,
                v2=t2->val,
                mcd=min(v1,v2)+1;

            while(mcd--)
                if(v1%mcd==0 && v2%mcd==0)
                    break;

            auto item=new node<int>(mcd,t2);
            t1->next=item;
        }
        return head;
    }

    node<int>* swap_pairs(node<int>* head){
        if(!head) return nullptr;
        if(!head->next) return head;

        auto aux=head->next;
        head->next=swap_pairs(aux->next);
        aux->next=head;

        return aux;
    }
};