#include <iostream>
enum Color{RED,Black};
using namespace std;
class rbtNode{
    public:
int key;
Color c;
rbtNode *left;
rbtNode *right;
rbtNode *parent;

rbtNode(int key,rbtNode* parent){
this->key=key;
left=right=NULL;
this->parent=parent;
c=RED;
}
};
rbtNode*rr;
rbtNode * rpsuccessor(rbtNode*node){
rbtNode *t=node->right;

if(node->left!=NULL && node->right!=NULL){
 while(t->left!=NULL){
    t=t->left;
}
return t;
}
else if (node->left==NULL && node->right==NULL){
    return NULL;
}
else if (node->left!=NULL && node->right==NULL){
    return node->left;
}
else if(node->left==NULL && node->right!=NULL){
    return node->right;
}
}
 rbtNode* searchh(rbtNode* root, int key)
{
    if (root == NULL || root->key == key)
       return root;
    if (root->key < key)
       return searchh(root->right, key);

       return searchh(root->left, key);
}

rbtNode *& insertt(int key,rbtNode*&root,rbtNode *parent=NULL){
   if (root==NULL)
    {
          root=new rbtNode(key,parent);
          rr=root;
        return root;
    }
    if(key < root->key)
        {
            return insertt(key,root->left,root);

        }
    else{
            return insertt(key,root->right,root);

        }
}
void RotateLeft(rbtNode *&head){
if(head->right==NULL)return;
rbtNode *p=head->parent;
rbtNode *A=head;
rbtNode *b=head->right->left;
rbtNode *B=head->right;
head=B;
B->parent=p;
A->parent=B;
A->right=b;
B->left=A;
if(b!=NULL)
    b->parent=A;

}
void RotateRight(rbtNode *&head){
if(head->left==NULL)return;
rbtNode *p=head->parent;
rbtNode *B=head;
rbtNode *b=head->left->right;
rbtNode *A=head->left;
head=A;
A->parent=p;
B->parent=A;
A->right=B;
B->left=b;
if(b!=NULL)
    b->parent=B;

}
void InsertRBT(int key, rbtNode*&node){
rbtNode *root=insertt(key,node);

while ((root!=node) &&(root->parent!=node)&& (root->parent->c==RED))
{
     rbtNode*parent=root->parent;
     if(parent==parent->parent->left){
        rbtNode * uncle =parent->parent->right;
         if(uncle!=NULL&&uncle->c==RED ){
                parent->c=Black;
                uncle->c=Black;
                parent->parent->c=RED;
                root=parent->parent;
         }
        else {

            if(root==parent->right){ // left-right case
                RotateLeft(parent->parent->left);
                root=parent;

            }
            else{
                rbtNode*gp=parent->parent;
                parent->c=Black;
                gp->c=RED;
                if(gp==node)
                    RotateRight(node);
                else
                {
                    if(gp=gp->parent->left)
                        RotateRight(gp->parent->left);
                    else
                        RotateRight(gp->parent->right);
                }
           // break;
            }

        }

     }
    else{
        rbtNode*uncle=parent->parent->left;
         if(uncle!=NULL && uncle->c==RED){
             parent->c=Black;
                uncle->c=Black;
                parent->parent->c=RED;
                root=parent->parent;
         }
        else{
            if(root==parent->left){ // left-right case
                RotateRight(parent->parent->right);
                root=parent;
            }
            else{
                rbtNode*gp=parent->parent;
                parent->c=Black;
                gp->c=RED;
                if(gp==node)
                    RotateLeft(node);
                else
                {
                    if(gp=gp->parent->left)
                        RotateLeft(gp->parent->left);
                    else
                        RotateLeft(gp->parent->right);
                }
           // break;
            }



        }




    }
}


node->c=Black;
}
void DeleteRbt(rbtNode *x)
{
rbtNode*sibling=NULL;
rbtNode *parent=x->parent;
if(x==x->parent->left){
  sibling=parent->right;
}
else {
   sibling=parent->left;
}
if(sibling==NULL && parent->c==Black){
    DeleteRbt(parent);
}
 else{
    if(sibling->c==RED){
        parent->c=RED;
        sibling->c=Black;
        if(sibling==parent->right){
            RotateLeft(parent);
        }
        else{
            RotateRight(parent);
        }
        DeleteRbt(x);
    }

    else{
          if(sibling->left->c==RED || sibling->right->c==RED) {
        if(sibling->left!=NULL && sibling->left->c==RED){

            if(sibling==parent->left){
                sibling->left->c=Black;
                swap(sibling->c,parent->c);
                RotateRight(parent);
            }
           else {
            swap(sibling->c,sibling->left->c);
            RotateRight(sibling);
            RotateLeft(parent);

           }

        }

        else {

              if(sibling==parent->left){
                swap(sibling->c,sibling->right->c);
                RotateLeft(sibling);
                RotateRight(parent);

              }
              else {
                sibling->right->c=Black;
                swap(sibling->c,parent->c);
                RotateLeft(parent);
              }
}


        parent->c=Black;


}
else{
        sibling->c=Black;
        if(parent->c==RED){
            parent->c=Black;
        }
        else
            DeleteRbt(parent);
}

    }
}
}
void delettt(rbtNode *x,rbtNode*root){
rbtNode *s=rpsuccessor(x);
rbtNode *p=x->parent;
rbtNode*sibling=NULL;
if(s!=NULL){
if(s==s->parent->left){
  sibling=s->parent->right;
}
else {
   sibling=s->parent->left;
}
}

if(s==NULL){
    if(x==root)
        root=NULL;
    else {
        if ((x == NULL /*s->c == Black*/) && (x->c == Black)) {
          DeleteRbt(x);
        }
        else {
          if (sibling != NULL)
            sibling->c=RED;
        }

        // delete v from the tree
        if (x==x->parent->left) {
          p->left = NULL;
        } else {
          p->right = NULL;
        }
      }
      delete x;
      return ;
}
if (x->left == NULL || x->right==NULL){
    if (x==root) {
        x->key=s->key;
        x->left = x->right = NULL;
        delete s;
        }
        else {

        if (x==x->parent->left) {
          p->left = s;
        } else {
          p->right = s;
        }
        delete x;
        s->parent = p;
        if ((s == NULL or s->c == Black) and (x->c == Black)) {
          DeleteRbt(s);
        } else {
          s->c=Black;
        }
      }
               return;
    }

    swap(s->key,x->key);
    delettt(s,root);
  }
 void printtreeInorder(rbtNode*root){

    if (root!=NULL){
printtreeInorder(root->left);
cout<<root->key<<" ";
printtreeInorder(root->right);
}
else {
    return;
}
}
void clearr(rbtNode*root,rbtNode*r){
if (root!=NULL){
clearr(root->left,r);
delettt(root,r);
clearr(root->right,r);

}}
int main()
{
   rbtNode *r=NULL;
   InsertRBT(8,r);
   InsertRBT(4,r);
   InsertRBT(5,r);
   InsertRBT(3,r);
  delettt(r->left->left,r);
   cout<<r->key<<endl;
   rbtNode *x=searchh(r,8);
   cout<<x->key;

}
