#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution{
    struct tup{
        bool bal;
        int h;
        tup(bool b,int h):bal(b),h(h){}
    };

    TreeNode* insert(int val,TreeNode* aux){
        if(!aux) return new TreeNode(val);
        if(val<aux->val) aux->left=insert(val,aux->left);
        else aux->right=insert(val,aux->right);
        return aux;
    }

    tup* isbal(TreeNode* root){
        if(!root) return new tup(true,0);
        tup *tl=isbal(root->left),
                *tr=isbal(root->right);
        int h=max(tl->h,tr->h)+1;
        bool bal=abs(tl->h-tr->h)<2;
        bal=bal && tl->bal && tr->bal;
        delete tl; delete tr;
        return new tup(bal,h);
    }

    bool isBalanced(TreeNode* root) {
        return isbal(root)->bal;
    }

    vector<int> bubbleSort(vector<int>& arr){
        for(int i = 0; i < arr.size(); i++)
            for(int j = 0; j < arr.size(); j++)
                if(arr[j] > arr[i]) swap(arr[j], arr[i]);
        return arr;
    }

    TreeNode* sortedArrayToAVL(vector<int>arr, int start, int end){
        if(start > end) return nullptr;
        int mid = (start+end)/2;
        TreeNode* root = new TreeNode(arr[mid]);
        root->right = sortedArrayToAVL(arr, mid+1, end);
        root-> left = sortedArrayToAVL(arr, start, mid-1);
        return root;
    }

    TreeNode* solve(vector<int> arr){
        bubbleSort(arr);
        return sortedArrayToAVL(arr, 0, arr.size()-1);
    }
};