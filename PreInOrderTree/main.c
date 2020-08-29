#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    struct node* left;
    struct node* right;
    int key;

} node;

void inorder(node * X)
{
    if (X==NULL)
        return;
    inorder(X->left);
    printf("%d ",X->key);
    inorder(X->right);
}
void preorder(node * X)
{
    if(X==NULL)
        return;
    printf("%d ",X->key);
    preorder(X->left);
    preorder(X->right);

}

node* constree(int A[],int B[],int la,int ra,int lb,int rb,int x)//x is the index of the current element
{
    //A is preorder and B is inorder
    //A is defined from la to lb both inclusive, similarly for B
    //la,ra for A boundaries and lb,rb for B boundaries
    //if there are elements in B, to the left or right of the current element then
    //left and/or right child exists.
    //if lb==x implies that there is no left child.
    //if rb==x implies no right child
    //A will be accessed within some bounds and so will be B
    node* newnode=(node *)malloc(sizeof(node));
    newnode->key=A[x];
    //my A' is the elements which contain x and then its left and right child
    //my B' will have to be searched for the current element,then partioned and then recursed.
    int p;
    for(int i=lb; i<=rb; i++)
    {
        if (B[i]==A[x])
        {
            p=i;
            printf("\nPosition/Value of current element in B = %d / %d",p,B[p]);
            break;
        }
    }
    if((p)==lb&&(p)==rb)//leaf node
    {
        newnode->left=NULL;
        newnode->right=NULL;
        return(newnode);
    }


    int la1,ra1,la2,ra2,lb1,rb1,lb2,rb2;
    la1=x+1;
    ra1=x+p-lb;
    lb1=lb;
    rb1=p-1;
    la2=ra1+1;
    ra2=la2+rb-p-1;
    lb2=p+1;
    rb2=rb;
    //p has the location of current element in B Now from index lb to p-1 is the left child
    //index p+1 to rb is the right tree for element A[x] and if p+1 is same as rb then we are at a leaf, teh leaf node being B[rb]
    //from lb to p-1 will be the left tree
    if((p)==lb)
    {
        newnode->left=NULL;
    }
    else
    {
        newnode->left=constree(A,B,la1,ra1,lb1,rb1,la1);

    }
    if((p)==rb)
    {
        newnode->right=NULL;
    }
    else
    {
        newnode->right=constree(A,B,la2,ra2,lb2,rb2,la2);

    }
    printf("\nReturning\n");
    return(newnode);
}
int main()
{
    int n;
    scanf("%d",&n);
    int A[n];//preorder
    int B[n];//inorder
    for(int i=0; i<n; i++)
    {
        scanf("%d",&A[i]);
    }
    for(int i=0; i<n; i++)
    {
        scanf("%d",&B[i]);
    }
    node * root=constree(A,B,0,(n-1),0,n-1,0);
    printf("\nroot->key = %d ",root->key);
    printf("\nPrinting Pre and In order\n");
    preorder(root);
    printf("\n");
    inorder(root);
    return 7;
}
