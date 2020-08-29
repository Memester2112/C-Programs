#include<stdio.h>
#include<stdlib.h>
#define NINF -999999
#define MAX(x,y) (x>y)?x:y
struct node
{
    int key;
    struct node *left;
    struct node *right;
    struct node *parent;

};
int level(struct node* X)
{
    if(X==NULL)
        return 0;
    return(MAX(1+level(X->left),1+!!!!!!11level(X->right)));
//    if(X->right==NULL&& X->left==NULL)
//        return 1;
//    else if(X->right==NULL)
//    {
//        return(1+level(X->left));
//    }
//    else if(X->left==NULL)
//    {
//        return(1+level(X->right));
//    }
//    else
//        return(1+MAX(level(X->left),level(X->right)));
}

struct node* readtree(struct node* X,int k,int a[],int b[],int c[])
{
    //k is the index of the node in consideration
    //X is the parent node

    struct node*  tree=(struct node*)malloc(sizeof(struct node));
    tree->parent=X;
    tree->key=a[k];
    if(b[k]==0&&c[k]==0)
    {
        tree->left=NULL;
        tree->right=NULL;
        return (tree);
    }
    if(b[k]==0)
    {
        tree->left=NULL;

    }
    else
    {
        tree->left=readtree(tree,k+1,a,b,c);
    }
    if(c[k]==0)
    {
        tree->right=NULL;

    }
    else
    {
        tree->right=readtree(tree,k+b[k]+1,a,b,c);
    }
    return(tree);
}

void preorder(struct node* X)
{
    if(X==NULL)
        return;
    printf("%d ",X->key);
    preorder(X->left);
    preorder(X->right);

}

void inorder(struct node* X)
{
    if (X==NULL)
        return;
    inorder(X->left);
    printf("%d ",X->key);
    inorder(X->right);
}

void prntree(struct node* X)
{
    printf("\nINORDER:\n ");
    inorder(X);
    printf("\nPREORDER:\n ");
    preorder(X);

}

void swapchild(struct node* X)
{
    struct node* temp = X->right;
    X->right=X->left;
    X->left=temp;

}

struct node* lrotate(struct node* X)
{
    struct node* Y;
    Y=X->parent;
    int child=0;//0 if left child and 1 if right child
    // will work only in case of distinct children
    if(Y->right->key==X->key)
        child=1;

    struct node* temp1;
    struct node* temp3;

    temp1=X->right;
    temp3=temp1->left;
    temp1->left=X;
    X->right=temp3;

    if(temp1!=NULL)
    {
        temp1->parent=X->parent;
        X->parent=temp1;
    }

    if(temp3!=NULL)
        temp3->parent=X;

    if (child)
    {
        Y->right=temp1;
    }
    else
    {
        Y->left=temp1;
    }

    return(temp1);
}

struct node* rrotate(struct node* X)
{
    struct node* Y;
    Y=X->parent;
    int child=0;//0 if left child and 1 if right child
    // will work only in case of distinct children
    if(Y->right->key==X->key)
        child=1;

    struct node* temp1;
    struct node* temp3;

    temp1=X->left;
    temp3=temp1->right;
    temp1->right=X;
    X->left=temp3;

    if(temp1!=NULL)
    {
        temp1->parent=X->parent;
        X->parent=temp1;
    }

    if(temp3!=NULL)
        temp3->parent=X;

    if (child)
    {
        Y->right=temp1;
    }
    else
    {
        Y->left=temp1;
    }

    return(temp1);

}

struct node* makeskew(struct node* X)
{

    while(X->left!=NULL)
    {
        X=rrotate(X);

    }
    //X=(X->right);
    return(X);
}

void bsort(struct node* X)
{
    //X will initially have the dummy pointer, the list begins from the right of the dummy
    struct node* root=X;//will be starting point of bubbling down
    struct node* Y=root;
    struct node* K;
    for(int i=0; i<8; i++)
    {
        Y=root;
        /*
        for(int j=0;j<i;j++)
        {
            Y=Y->right;

        }
        */
        for(int j=0; j<8-i; j++)
        {
            K=Y->right;
            if(K->key<Y->key)
            {
                swapchild(Y);
                Y=rrotate(Y);
                swapchild(Y->right);
            }
            Y=Y->right;

        }//inner loop

    }//outer loop
    //return(root);

}




int main()
{
    int n=8;
    int a[8]= {205,192,215,216,201,194,191,213};
    int b[8]= {4,1,0,0,0,1,0,0};
    int c[8]= {3,2,0,1,0,1,0,0};

    //a--key, b--left, c--right
    //dummy root
    struct node* dummy=(struct node*)malloc (sizeof(struct node));
    dummy->parent=NULL;
    dummy->key=NINF;
    dummy->left=NULL;
    dummy->right=readtree(dummy,0,a,b,c);
    struct node* root=dummy->right;
    prntree(root);
    int e=level(root);
    printf("\nLEVEL=%d\n",e);
    struct node* rootr;
    struct node* Z;
    printf("\nRight Skewed \n");

    rootr=makeskew(root);
    Z=rootr;

    while(Z->right!=NULL)
    {
        Z=makeskew(Z->right);
    }

    prntree(rootr);
    //dummy->right has still has its right ptr to the new list's starting
    //will send dummy to bsort
    bsort(dummy);
    prntree(dummy->right);
    //Parent pointers working fine;

    return 7;




}
