#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* find(int val,TreeNode* node){
        if(node->val==val) return node;
        if(node->left) return find(val,node->left);
        if(node->right) return find(val,node->right);
        return nullptr;
    }

    bool compare(TreeNode* a,TreeNode* b){
        if(!a && !b) return true;
        if(!a || !b) return false;
        if(a->val!=b->val) return false;
        auto cl=compare(a->left,b->left);
        auto cr=compare(a->right,b->right);
        return cl && cr;
    }

    bool isSubtree(TreeNode* root, TreeNode* subRoot){
        auto aux=find(subRoot->val,root);
        if(!aux) return false;
        return compare(aux,subRoot);
    }

    struct pair{
        TreeNode* node=nullptr;
        int depth=0;
        pair()=default;
        pair(TreeNode* n,int d):node(n),depth(d){}
    };

    struct tup{
        TreeNode* node=nullptr;
        bool found=false;
        bool flag=false;
    };

    pair deepest(TreeNode* node,TreeNode* pass,int depth){
        if(!node || node==pass) return {};
        auto pl=deepest(node->left,pass,depth+1),
             pr=deepest(node->right,pass,depth+1);
        auto aux=pair(node,depth);
        if(!node->left && !node->right)
            return aux;
        aux=pl;
        if(pr.depth>pl.depth) aux=pr;
        return aux;
    }

    tup ancestor(TreeNode* node,int v1,int v2){
        if(!node) return {};

        tup aux; aux.node=node;
        if(node->val==v1 || node->val==v2)
        {aux.found=true; return aux;}

        tup tl=ancestor(node->left,v1,v2),
            tr=ancestor(node->right,v1,v2);
        if(tl.flag) return tl;
        if(tr.flag) return tr;

        if(tl.found || tr.found) aux.found=true;
        if(tl.found && tr.found) aux.flag=true;
        return aux;
    }

    TreeNode* lcaDeepestLeaves(TreeNode* root){
        TreeNode* d1=deepest(root,nullptr,0).node,
                * d2=deepest(root,d1,0).node;
        auto t0=ancestor(root,d1->val,d2->val);
        return t0.node;
    }
};