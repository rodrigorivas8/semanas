#include "queue.h"
using namespace std;

class MyStack {
    queue<int>* main=nullptr,
              * aux=nullptr;
public:
    MyStack(){
        main=new queue<int>;
        aux=new queue<int>;
    }
    void push(int x){
        main->enqueue(x);
    }
    int pop(){
        int val;
        while(!main->empty()){
            val=main->dequeue();
            if(!main->empty())
                aux->enqueue(val);
        }
        auto temp=main;
        main=aux;
        aux=temp;
        return val;
    }
    int top(){
        int val;
        while(!main->empty()){
            val=main->dequeue();
            aux->enqueue(val);
        }
        auto temp=main;
        main=aux;
        aux=temp;
        return val;
    }
    bool empty() {
        return main->empty();
    }
};

class MyCircularDeque{
    int cap=0;
    int* list=nullptr,
       * front=nullptr,
       * rear=nullptr;
public:
    MyCircularDeque(int k) {
        cap=k+1;
        list=new int[cap];
        front=list;
        rear=list;
    }
    bool insertFront(int value) {
        if(isFull()) return false;
        int f=int(front-list);
        *front=value;
        front=list+(f+cap-1)%cap;
        return true;
    }
    bool insertLast(int value) {
        if(isFull()) return false;
        int r=int(rear-list);
        rear=list+(r+1)%cap;
        *rear=value;
        return true;
    }
    bool deleteFront() {
        if(isEmpty()) return false;
        int f=int(front-list);
        front=list+(f+1)%cap;
        return true;
    }
    bool deleteLast() {
        if(isEmpty()) return false;
        int r=int(rear-list);
        rear=list+(r+cap-1)%cap;
        return true;
    }
    int getFront() {
        if(isEmpty()) return -1;
        int f=int(front-list);
        return *(list+(f+1)%cap);
    }
    int getRear() {
        if(isEmpty()) return -1;
        return *rear;
    }
    bool isEmpty() {
        return front==rear;
    }
    bool isFull() {
        int f=int(front-list),
            r=int(rear-list);
        return f==(r+1)%cap;
    }
};

const int CAP=1e5;
class MinStack {
    struct pair{
        int val=0;
        int min=0;
        pair()=default;
        pair(int v):val(v),min(v){}
    };
    pair list[CAP];
    int tip=-1;

public:
    MinStack()=default;
    void push(int val) {
        if(tip==CAP-1) return;
        tip++;
        list[tip]=pair(val);
        if(tip==0) return;
        int min=list[tip-1].min;
        if(min<val) list[tip].min=min;
    }
    void pop() {
        if(tip+1) tip--;
    }
    int top() {
        return list[tip].val;
    }
    int getMin() {
        return list[tip].min;
    }
};

struct solution{
    int depth(string s){
        int d=0,x=0;
        for(char c:s){
            if(c=='(') x++;
            if(c==')') x--;
            d=max(d,x);
        }
        return d;
    }
};